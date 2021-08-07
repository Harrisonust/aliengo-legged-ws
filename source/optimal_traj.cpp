#include "optimal_traj.h"
#include "coord_XYThetaMath.h"
#include "coord_RTOmegaMath.h"
#include "robot.h"
#include "coord_sys_inc.h"

void trap_optimal_traj1D(const double delta, double& apply, const double vel_limit, const double acc_limit){
    return;
}

void trap_optimal_traj(const XYTheta target, RTOmega& sport_apply){
    const XYTheta currPos = wb_getCurrentPos();
    const double deltax = target.x - currPos.x;
    const double deltay = target.y - currPos.y;
    const double deltatheta = target.theta - currPos.theta;

    XYTheta xyt = {0};
    double y_vel_limit = (deltax > 0)?FORWARD_SPEED_LIMIT:BACKWARD_SPEED_LIMIT;
    double y_acc_limit = (deltax > 0)?FORWARD_ACC_LIMIT:BACKWARD_ACC_LIMIT;
    trap_optimal_traj1D(deltax, xyt.x, y_vel_limit, y_acc_limit);
    trap_optimal_traj1D(deltay, xyt.y, SIDEWARD_SPEED_LIMIT, SIDEWARD_ACC_LIMIT);
    trap_optimal_traj1D(deltatheta, xyt.theta, ROTATE_SPEED_LIMIT, ROTATE_ACC_LIMIT);
    
    sport_apply = XYT2RTO(xyt);
}


void bezier_optimal_traj(const XYTheta target, RTOmega& sport_apply, const double scale){

}