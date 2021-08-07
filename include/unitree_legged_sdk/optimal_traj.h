#pragma once
#include "coord_sys_inc.h"

void trap_optimal_traj(const XYTheta target, RTOmega& sport_apply);
void bezier_optimal_traj(const XYTheta target, RTOmega& sport_apply, const double scale);