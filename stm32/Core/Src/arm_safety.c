/*
 * arm_safety.c
 *
 *  Created on: May 22, 2026
 *      Author: texasjoe23
 */
#include "arm_safety.h"

PoseError ValidatePose(PoseCommand *pose)
{
    if (pose->base < 25 || pose->base > 155){
    	SendMessage("ERR:POSE_ERR_BASE_LIMIT\n");
        return POSE_ERR_BASE_LIMIT;
    }

    if (pose->wrist > 160 && pose->elbow < 55){
    	 SendMessage("ERR:POSE_ERR_COLLISION_RISK\n");
        return POSE_ERR_COLLISION_RISK;
    }

    return POSE_OK;
}

bool ValidateGrip(GripCommand *grip){
	if(grip->target < 0 || grip->target > 180){
		SendMessage(" POSE_ERR_GRIPPER_LIMIT\n");
		return false;
	}
	return true;
}

