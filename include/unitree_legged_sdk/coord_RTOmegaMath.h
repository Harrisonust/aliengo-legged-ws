#pragma once
#include "math.h"
#include "coord_sys_inc.h"
#define func static 


func RTOmega mul_rto(const RTOmega a, const PolarVec b){
	return (RTOmega){
		.r = a.r * b.r,
		.theta = a.theta,
		.omega = a.omega * b.theta,
	};
}


#undef func
