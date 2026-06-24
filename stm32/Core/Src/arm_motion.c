/*
 * arm_motion.c
 *
 *  Created on: May 22, 2026
 *      Author: texasjoe23
 */

#include "arm_motion.h"
#include <math.h>


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

RobotArm arm;
float max_step = 2.0f;





void InitArm()
{
	arm.base.current_angle = 90;
	arm.base.target_angle = 90;
	arm.base.velocity = 100.0f;

	arm.elbow.current_angle = 25;
	arm.elbow.target_angle = 25;
	arm.elbow.velocity = 100.0f;

	arm.wrist.current_angle = 90;
    arm.wrist.target_angle = 90;
    arm.wrist.velocity = 100.0f;

    arm.gripper.current_angle = 45;
    arm.gripper.target_angle = 45;
    arm.gripper.velocity = 100.0f;

    armState = ARM_IDLE;
}

uint16_t AngleToPWM(float angle)
{
    return 500 + (angle / 180.0f) * 2250;
}

void UpdateServo(Servo *s)
{
    float error = s->target_angle - s->current_angle;

    if (fabsf(error) < 0.5f)
    {
        s->current_angle = s->target_angle;
        return;
    }

    float step = s->velocity * CONTROL_DT;

    // prevent overshoot ONLY
    if (step > fabsf(error))
        step = fabsf(error);

    s->current_angle += (error > 0 ? step : -step);

}

void UpdateAllServos()
{
    UpdateServo(&arm.base);
    UpdateServo(&arm.elbow);
    UpdateServo(&arm.wrist);
    UpdateServo(&arm.gripper);

    __HAL_TIM_SET_COMPARE(&htim2,
                          TIM_CHANNEL_1,
                          AngleToPWM(arm.base.current_angle));

    __HAL_TIM_SET_COMPARE(&htim2,
                          TIM_CHANNEL_2,
                          AngleToPWM(arm.elbow.current_angle));

    __HAL_TIM_SET_COMPARE(&htim3,
                          TIM_CHANNEL_1,
                          AngleToPWM(arm.wrist.current_angle));

    __HAL_TIM_SET_COMPARE(&htim3,
                          TIM_CHANNEL_2,
                          AngleToPWM(arm.gripper.current_angle));
}

bool ArmAtTarget()
{
    return
        fabsf(arm.base.target_angle   - arm.base.current_angle)   < 1.5f &&
        fabsf(arm.elbow.target_angle  - arm.elbow.current_angle)  < 1.5f &&
        fabsf(arm.wrist.target_angle  - arm.wrist.current_angle)  < 1.5f &&
        fabsf(arm.gripper.target_angle- arm.gripper.current_angle)< 1.5f;
}


