#pragma once
#include "math.h"
#include "coord_sys_inc.h"
#define func static inline

func XYTheta xyt_from_v2(Vec2 v, float a) { return (XYTheta){.x = v.x, .y = v.y, .theta = a}; }
func RTOmega rto_from_pv(PolarVec v, float a) { return (RTOmega){.r = v.r, .theta = v.theta, .omega = a}; }

func XYTheta from_cartesian_component(const Vec2 xy) {
	return (XYTheta){
		.x = xy.x,
		.y = xy.y,
		.theta = 0,
	};
}

func Vec2 to_cartesian_component(const XYTheta twist) {
	return (Vec2){
		.x = twist.x,
		.y = twist.y,
	};
}

func XYTheta add_xyt(const XYTheta a, const XYTheta b) {
	return (XYTheta){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.theta = a.theta + b.theta,
	};
}

func XYTheta mul_xyt(const XYTheta a, const XYTheta b) {
	return (XYTheta){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.theta = a.theta * b.theta,
	};
}

func XYTheta scale_xyt(const XYTheta a, const float k) {
	return (XYTheta){
		.x = a.x * k,
		.y = a.y * k,
		.theta = a.theta * k,
	};
}

func float dot_xyt(const XYTheta a, const XYTheta b) { 
    return a.x * b.x + a.y * b.y + a.theta * b.theta; 
}

func float wrap_angle_one(float err, float range) {
	if (err > (range / 2))
		return err - range;
	else if (err < -(range / 2))
		return err + range;
	else
		return err;
}

func float wrap_angle(float a, float range) { return wrap_angle_one(fmod(a, range), range); }

func XYTheta sub_xyt(const XYTheta a, const XYTheta b) {
	return (XYTheta){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.theta = wrap_angle(a.theta - b.theta, 2 * M_PI),
	};
}

func XYTheta neg_xyt(const XYTheta b) {
	return (XYTheta){
		.x = -b.x,
		.y = -b.y,
		.theta = -b.theta,
	};
}

#undef fun