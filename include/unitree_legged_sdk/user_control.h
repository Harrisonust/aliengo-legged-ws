#pragma once
#include <iostream>

#include "comm.h"
#include "coord_XYThetaMath.h"
#include "coord_sys_inc.h"

#define func inline static

enum Mode { IDLE, FORCED_STAND, WALK, NUM_OF_MODE };

class HighLevelControlHandler {
   private:
    static UNITREE_LEGGED_SDK::HighCmd cmd;
    static XYTheta _apply_pos;
    static RTOmega _apply_vel;
    static RPYaw _apply_rpy;
    static Mode _sport_mode;

    func void constrain(double& value, const double& highend,
                        const double& lowend);

   public:
    HighLevelControlHandler() = default;

    func void debug();

    func void set_mode(Mode mode);

    func void set_pos(XYTheta pos);

    func void set_vel(RTOmega vel);

    func void set_rpy(RPYaw rpy);

    func void sport_apply();

    func UNITREE_LEGGED_SDK::HighCmd& get_cmd();
};

func std::ostream& operator<<(std::ostream& os, const XYTheta& xyt) {
    os << "apply_xyt: (" << xyt.x << ", " << xyt.y << ", " << xyt.theta << ")";
    return os;
}

func std::ostream& operator<<(std::ostream& os, const RTOmega& rto) {
    os << "apply_rto: (" << rto.r << ", " << rto.theta << ", " << rto.omega
       << ")";
    return os;
}

func std::ostream& operator<<(std::ostream& os, const RPYaw& rpy) {
    os << "apply_rpy: (" << rpy.roll << ", " << rpy.pitch << ", " << rpy.yaw
       << ")";
    return os;
}

void HighLevelControlHandler::debug() {
    std::cout << _apply_pos << std::endl;
    std::cout << _apply_vel << std::endl;
    std::cout << _apply_rpy << std::endl;
    std::cout << _sport_mode << std::endl;
}

// 0: idle, default stand
// 1: forced stand
// 2: walk continuously
void HighLevelControlHandler::set_mode(Mode mode) { _sport_mode = mode; }

void HighLevelControlHandler::set_pos(XYTheta pos) { _apply_pos = pos; }

void HighLevelControlHandler::constrain(double& value, const double& highend,
                                        const double& lowend) {
    if (value > highend) value = highend;
    if (value < lowend) value = lowend;
}

void HighLevelControlHandler::set_vel(RTOmega vel) {
    constrain(vel.r, 1, -1);
    constrain(vel.omega, 1, -1);
    _apply_vel = vel;
}

void HighLevelControlHandler::set_rpy(RPYaw rpy) {
    constrain(rpy.roll, 1, -1);
    constrain(rpy.pitch, 1, -1);
    constrain(rpy.yaw, 1, -1);
    _apply_rpy = rpy;
}

void HighLevelControlHandler::sport_apply() {
    cmd.mode = _sport_mode;
    cmd.bodyHeight = 0.0f;

    cmd.forwardSpeed = _apply_vel.r * sin(_apply_vel.theta);
    cmd.sideSpeed = _apply_vel.r * cos(_apply_vel.theta);
    cmd.rotateSpeed = _apply_vel.omega;

    cmd.roll = _apply_rpy.roll;
    cmd.pitch = _apply_rpy.pitch;
    cmd.yaw = _apply_rpy.yaw;
}

UNITREE_LEGGED_SDK::HighCmd& HighLevelControlHandler::get_cmd() { return cmd; }

#undef func