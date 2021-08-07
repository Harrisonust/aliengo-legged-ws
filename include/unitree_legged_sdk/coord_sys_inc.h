#pragma once
#include "math.h"

#define func static

struct Vec2 {
    double x;
    double y;
};

struct XYTheta {
    double x;
    double y;
    double theta;
};

struct PolarVec {
    double r;
    double theta;
};

struct RTOmega {
    double r;
    double theta;
    double omega;
};

struct RPYaw {
    double roll;
    double pitch;
    double yaw;
};

#define XYT(X, Y, T) ((XYTheta){.x = (X), .y = (Y), .theta = (T)})
#define RTO(R, T, O) ((RTOmega){.r = (R), .theta = (T), .omega = (O)})
#define RPY(R, P, Y) ((RPYaw){.roll = (R), .pitch = (P), .yaw = (Y)})

#undef func
