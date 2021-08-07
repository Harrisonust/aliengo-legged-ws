#include "user_control.h"

UNITREE_LEGGED_SDK::HighCmd HighLevelControlHandler::cmd = {0};
XYTheta HighLevelControlHandler::_apply_pos = {0};
RTOmega HighLevelControlHandler::_apply_vel = {0};
RPYaw HighLevelControlHandler::_apply_rpy = {0};
Mode HighLevelControlHandler::_sport_mode = IDLE;
