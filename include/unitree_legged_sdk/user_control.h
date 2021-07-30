#pragma once
#include "comm.h"
#include "coord_sys_inc.h"

extern XYTheta apply_pos;
extern RTOmega apply_vel;

class User_Control
{
private:
    UNITREE_LEGGED_SDK::HighCmd cmd;

public:
    void testing();
    void pos_set(XYTheta);
    void vel_set(RTOmega);
};

void User_Control::testing()
{
    return;
}

void User_Control::pos_set(XYTheta pos)
{
}

void User_Control::vel_set(RTOmega vel)
{
}
