/************************************************************************
Copyright (c) 2020, Unitree Robotics.Co.Ltd. All rights reserved.
Use of this source code is governed by the MPL-2.0 license, see LICENSE.
************************************************************************/

#include <math.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "unitree_legged_sdk.h"

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
    HighCmd cmd = {0};
    HighState state = {0};
    int motiontime = 0;
    float dt = 0.002;  // 0.001~0.01
};

void Custom::UDPRecv() { udp.Recv(); }

void Custom::UDPSend() { udp.Send(); }

void Custom::RobotControl() {
    HighLevelControlHandler::debug();
    HighLevelControlHandler::change_sport_mode(WALK);
    HighLevelControlHandler::vel_set(RTO(-0.02, 90 * CONVERT_TO_RAD, 0));

    motiontime += 2;
    udp.GetRecv(state);
    // printf("%d   %f\n", motiontime, state.imu.quaternion[2]);
    if (motiontime > 1000) {
        HighLevelControlHandler::pos_set(XYT(87, 66, 12));
        HighLevelControlHandler::vel_set(RTO(87, 66, 12));
        HighLevelControlHandler::rpy_set(RPY(87, 66, 12));
    }

    udp.SetSend(cmd);
    HighLevelControlHandler::sport_apply();
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
