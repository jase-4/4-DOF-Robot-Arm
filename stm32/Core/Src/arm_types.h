/*
 * arm_types.h
 *
 *  Created on: May 22, 2026
 *      Author: texasjoe23
 */

#ifndef SRC_ARM_TYPES_H_
#define SRC_ARM_TYPES_H_

typedef struct
{
    float current_angle;
    float target_angle;
    float min_angle;
    float max_angle;
    float velocity;
} Servo;

typedef struct
{
    Servo base;
    Servo elbow;
    Servo wrist;
    Servo gripper;
} RobotArm;

typedef struct
{
    float base;
    float elbow;
    float wrist;
} PoseCommand;

typedef struct
{
    float target;
    float speed;
} GripCommand;

typedef struct {
    PoseCommand arm;
    GripCommand gripper;
} RobotCommand;

typedef enum {
    POSE_OK = 0,
    POSE_ERR_BASE_LIMIT,
    POSE_ERR_GRIPPER_LIMIT,
    POSE_ERR_COLLISION_RISK
} PoseError;

typedef enum {
    ARM_IDLE,
    ARM_RECEIVING,
    ARM_MOVING,
    ARM_DONE,
    ARM_ERROR
} ArmState;

typedef enum {
	CMD_NONE,
	CMD_PING,
	CMD_POSE,
	CMD_STOP,
	CMD_RESET,
	CMD_GRIP,
	CMD_VELO
}CMDType;

#endif /* SRC_ARM_TYPES_H_ */
