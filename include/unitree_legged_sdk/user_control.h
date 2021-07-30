#pragma once
#include "comm.h"
#include "coord_sys_inc.h"
enum Mode{
    IDLE,
    FORCED_STAND,
    WALK,
    NUM_OF_MODE
};

class User_Control{
private:
    static UNITREE_LEGGED_SDK::HighCmd cmd;
    static XYTheta _apply_pos;
    static RTOmega _apply_vel;
    static RPYaw   _apply_rpy;
    static Mode    _sport_mode;
public:
    
    static void testing(){ return; }
    static void change_sport_mode(Mode mode){
        _sport_mode = mode;
    }
    static void pos_set(XYTheta pos){
        _apply_pos = pos;
    }
    static void vel_set(RTOmega vel){
        _apply_vel = vel;
    }
    static void rpy_set(RPYaw rpy){
        _apply_rpy = rpy;
    }
    static void sport_apply(){
        cmd.forwardSpeed = _apply_vel.r * sin(_apply_vel.theta);
        cmd.sideSpeed    = _apply_vel.r * cos(_apply_vel.theta);
        cmd.rotateSpeed  = _apply_vel.omega;
        cmd.bodyHeight   = 0.0f;

        cmd.mode  = _sport_mode;      // 0:idle, default stand      1:forced stand     2:walk continuously
        cmd.roll  = _apply_rpy.roll;
        cmd.pitch = _apply_rpy.pitch;
        cmd.yaw   = _apply_rpy.yaw;
    }
};

