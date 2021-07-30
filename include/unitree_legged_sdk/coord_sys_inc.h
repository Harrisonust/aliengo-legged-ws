#pragma once
#include "math.h"

#define func static __forceinline __pure

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

func XYTheta add_xyt(const XYTheta a, const XYTheta b)
{
	return (XYTheta){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.theta = a.theta + b.theta,
	};
}

func RTOmega add_rto(const RTOmega a, const RTOmega b)
{
	return (RTOmega){
		.v = polar_add(a.v, b.v),
		.omega = a.omega + b.omega,
	};
}

func RTOmega sub_rto(const RTOmega a, const RTOmega b)
{
	return (RTOmega){
		.v = polar_add(a.v, PV(b.r, PI + b.theta)),
		.omega = a.omega - b.omega,
	};
}

func XYTheta mul_xyt(const XYTheta a, const XYTheta b)
{
	return (XYTheta){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.theta = a.theta * b.theta,
	};
}

func XYTheta scale_xyt(const XYTheta a, const num_t k)
{
	return (XYTheta){
		.x = a.x * k,
		.y = a.y * k,
		.theta = a.theta * k,
	};
}

func num_t dot_xyt(const XYTheta a, const XYTheta b) { return a.x * b.x + a.y * b.y + a.theta * b.theta; }

func RTOmega mul_rto(const RTOmega a, const PolarVec b)
{
	return (RTOmega){
		.r = a.r * b.r,
		.theta = a.theta,
		.omega = a.omega * b.theta,
	};
}

func XYTheta sub_xyt(const XYTheta a, const XYTheta b)
{
	return (XYTheta){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.theta = wrap_angle(a.theta - b.theta, 2 * PI),
	};
}

func XYTheta neg_xyt(const XYTheta b)
{
	return (XYTheta){
		.x = -b.x,
		.y = -b.y,
		.theta = -b.theta,
	};
}

func XYTheta rotate_xyt(const XYTheta orig, const num_t theta)
{
	Vec2 xy = rotatev2(orig.v, theta);
	return (XYTheta){
		.x = xy.x,
		.y = xy.y,
		.theta = orig.theta,
	};
}

func RTOmega xyt_to_polar(XYTheta v)
{
	return (RTOmega){
		.v = vec2polar(v.v),
		.omega = v.theta,
	};
}

func XYTheta polar_to_xyt(RTOmega v)
{
	return (XYTheta){
		.v = polar2vec(v.v),
		.theta = v.omega,
	};
}

#undef func
