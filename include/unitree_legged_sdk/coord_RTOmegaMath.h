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

func RTOmega XYT2RTO(const XYTheta xyt){
    return (RTOmega){   .r = sqrt( pow(xyt.x, 2) + pow(xyt.y, 2) ), 
                        .theta = atan(xyt.y/xyt.x), 
                        .omega = xyt.theta};
}

func XYTheta RTO2XYT(const RTOmega rto){
    return (XYTheta){   .x = rto.r * cos(rto.theta),
                        .y = rto.r * sin(rto.theta),
                        .theta = rto.omega};
}

#undef func
