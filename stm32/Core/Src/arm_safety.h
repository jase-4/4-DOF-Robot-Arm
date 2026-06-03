/*
 * arm_safety.h
 *
 *  Created on: May 22, 2026
 *      Author: texasjoe23
 */

#ifndef SRC_ARM_SAFETY_H_
#define SRC_ARM_SAFETY_H_

#include <stdbool.h>

#include "arm_types.h"
#include "arm_protocol.h"
#include "arm_motion.h"
PoseError ValidatePose(PoseCommand *pose);
bool ValidateGrip(GripCommand *grip);

#endif /* SRC_ARM_SAFETY_H_ */
