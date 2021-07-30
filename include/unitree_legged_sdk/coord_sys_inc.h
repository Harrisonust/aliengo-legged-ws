#pragma once
#include "math.h"

#define func static 

struct Vec2
{
	float x;
	float y;
};

struct XYTheta
{
	float x;
	float y;
	float theta;
};

struct PolarVec
{
	float r;
	float theta;
};

struct RTOmega
{
	float r;
	float theta;
	float omega;
};

#define XYT(X, Y, T) ((XYTheta){.x = (X), .y = (Y), .theta = (T)})
#define RTO(R, T, O) ((RTOmega){.r = (R), .theta = (T), .omega = (O)})

struct RPYaw{
	float roll;
	float pitch;
	float yaw;
};

#undef func
