#pragma once
#include "math.h"

#define func static
#define CONVERT_TO_RAD 0.01744444444
#define CONVERT_TO_DEG 57.3248407643
#define M2MM 1000
#define MM2M 0.001

struct Vec2 {
    float x;
    float y;
};

struct XYTheta {
    float x;
    float y;
    float theta;
};

struct PolarVec {
    float r;
    float theta;
};

struct RTOmega {
    float r;
    float theta;
    float omega;
};

struct RPYaw {
    float roll;
    float pitch;
    float yaw;
};

#define XYT(X, Y, T) ((XYTheta){.x = (X), .y = (Y), .theta = (T)})
#define RTO(R, T, O) ((RTOmega){.r = (R), .theta = (T), .omega = (O)})
#define RPY(R, P, Y) ((RPYaw){.roll = (R), .pitch = (P), .yaw = (Y)})

#undef func
