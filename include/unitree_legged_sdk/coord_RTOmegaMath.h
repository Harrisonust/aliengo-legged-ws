#pragma once
#include "coord_sys_inc.h"
#include "math.h"
#define func static inline

func RTOmega mul_rto(const RTOmega a, const PolarVec b) {
    return (RTOmega){
        .r = a.r * b.r,
        .theta = a.theta,
        .omega = a.omega * b.theta,
    };
}

#undef func
