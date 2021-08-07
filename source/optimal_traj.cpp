#include "optimal_traj.h"
#include "coord_Math.h"
#include "robot.h"

bool reach_slow_down(const double delta, const double apply, const double acc_limit){
    double target_vel = 2 * acc_limit * delta;
    if(apply > target_vel)
        return true;
    return false;
}

void trap_optimal_trajLinear(const double delta, double& apply, const double vel_limit, const double acc_limit){
    if(wb_getCurrentVel().r > vel_limit) return;
    if(reach_slow_down(delta, apply, acc_limit)) {
        apply -= acc_limit;
        return;
    }
    apply += acc_limit;
    return;
}

void trap_optimal_trajRotation(const double delta, double& apply, const double rot_limit, const double acc_limit){
    if(wb_getCurrentVel().omega > rot_limit) return;
    if(reach_slow_down(delta, apply, acc_limit)) {
        apply -= acc_limit; 
        return;
    }
    apply += acc_limit;
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
    trap_optimal_trajLinear(deltax, xyt.x, y_vel_limit, y_acc_limit);
    trap_optimal_trajLinear(deltay, xyt.y, SIDEWARD_SPEED_LIMIT, SIDEWARD_ACC_LIMIT);
    trap_optimal_trajRotation(deltatheta, xyt.theta, ROTATE_SPEED_LIMIT, ROTATE_ACC_LIMIT);
    
    sport_apply = XYT2RTO(xyt);
}


void bezier_optimal_traj(const XYTheta target, RTOmega& sport_apply, const double scale){

}