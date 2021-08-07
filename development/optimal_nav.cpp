/************************************************************************
Copyright (c) 2020, Unitree Robotics.Co.Ltd. All rights reserved.
Use of this source code is governed by the MPL-2.0 license, see LICENSE.
************************************************************************/

#include <math.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "unitree_legged_sdk.h"
#include "optimal_traj.h"
using namespace UNITREE_LEGGED_SDK;

class Custom {
   public:
    Custom(uint8_t level) : safe(LeggedType::A1), udp(level) {
        udp.InitCmdData(HighLevelControlHandler::get_cmd());
    }
    void UDPRecv();
    void UDPSend();
    void RobotControl();

    Safety safe;
    UDP udp;
    HighState state = {0};
    int motiontime = 0;
    const float dt = 0.002;  // 0.001~0.01 sec
};

void Custom::UDPRecv() { udp.Recv(); }

void Custom::UDPSend() { udp.Send(); }

RTOmega apply_speed = {0};
void Custom::RobotControl() {
    HighLevelControlHandler::debug();
    HighLevelControlHandler::set_mode(FORCED_STAND);
    // HighLevelControlHandler::set_vel(RTO(-0.02, 90 * CONVERT_TO_RAD, 0));

    if (motiontime > 1000) {
        const XYTheta target_pos = {100, 100, 0};
        trap_optimal_traj(target_pos, apply_speed);
        HighLevelControlHandler::set_vel(apply_speed);
    }

    udp.GetRecv(state);
    udp.SetSend(HighLevelControlHandler::get_cmd());
    HighLevelControlHandler::sport_apply();

    motiontime += dt * SEC_TO_MSEC;
}

int main(void) {
    std::cout << "Communication level is set to HIGH-level." << std::endl
              << "WARNING: Make sure the robot is standing on the ground."
              << std::endl
              << "Press Enter to continue..." << std::endl;
    std::cin.ignore();

    Custom custom(HIGHLEVEL);
    // InitEnvironment();
    LoopFunc loop_control("control_loop", custom.dt,
                          boost::bind(&Custom::RobotControl, &custom));
    LoopFunc loop_udpSend("udp_send", custom.dt, 3,
                          boost::bind(&Custom::UDPSend, &custom));
    LoopFunc loop_udpRecv("udp_recv", custom.dt, 3,
                          boost::bind(&Custom::UDPRecv, &custom));

    loop_udpSend.start();
    loop_udpRecv.start();
    loop_control.start();

    while (1) {
        sleep(10);
    };

    return 0;
}
