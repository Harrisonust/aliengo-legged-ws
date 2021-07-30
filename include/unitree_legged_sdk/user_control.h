#pragma once
#include "comm.h"
#include "coord_sys_inc.h"
#include <iostream>
#define func inline 
#define CONVERT_TO_RAD 0.01744444444
#define CONVERT_TO_DEG 57.3248407643
enum Mode{
    IDLE,
    FORCED_STAND,
    WALK,
    NUM_OF_MODE
};

class HighLevelControllHandler{
private:
    UNITREE_LEGGED_SDK::HighCmd* cmd;
    XYTheta _apply_pos;
    RTOmega _apply_vel;
    RPYaw   _apply_rpy;
    Mode    _sport_mode;

    void constrain(float& value, const float& highend, const float& lowend);
public:
    HighLevelControllHandler( UNITREE_LEGGED_SDK::HighCmd* c):cmd(c) {};
    void debug(){
        std::cout << "Calling HighLevelControllHandler::debug()" << std::endl;
        return;
    }

    func void change_sport_mode(Mode mode){
        // 0:idle, default stand      
        // 1:forced stand     
        // 2:walk continuously
        _sport_mode = mode;
    }

    func void pos_set(XYTheta pos){
        _apply_pos = pos;
    }

    func void vel_set(RTOmega vel){
        constrain(vel.r, 1, -1);
        constrain(vel.omega, 1, -1);
        _apply_vel = vel;
    }

    func void rpy_set(RPYaw rpy){
        constrain(rpy.roll, 1, -1);
        constrain(rpy.pitch, 1, -1);
        constrain(rpy.yaw, 1, -1);
        _apply_rpy = rpy;
    }

    void sport_apply(){
        cmd->forwardSpeed = _apply_vel.r * sin(_apply_vel.theta);
        cmd->sideSpeed    = _apply_vel.r * cos(_apply_vel.theta);
        cmd->rotateSpeed  = _apply_vel.omega;
        cmd->bodyHeight   = 0.0f;

        cmd->mode  = _sport_mode;    
        cmd->roll  = _apply_rpy.roll;
        cmd->pitch = _apply_rpy.pitch;
        cmd->yaw   = _apply_rpy.yaw;
    }
};

void HighLevelControllHandler::constrain(float& value, const float& highend, const float& lowend){
    if(value > highend) value = highend;
    if(value < lowend) value = lowend;
    return;
}

#undef func