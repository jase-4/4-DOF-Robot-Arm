/*
 * arm_motion.h
 *
 *  Created on: May 22, 2026
 *      Author: texasjoe23
 */

#ifndef SRC_ARM_MOTION_H_
#define SRC_ARM_MOTION_H_


#include "main.h"
#include "arm_types.h"
#include "arm_protocol.h"

#include <stdbool.h>
#include <stdint.h>



void InitArm(void);

void UpdateAllServos(void);

void UpdateServo(Servo *s);

uint16_t AngleToPWM(float angle);

bool  ArmAtTarget(void);

extern RobotArm arm;


#endif /* SRC_ARM_MOTION_H_ */
