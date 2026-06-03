/*
 * arm_protocol.c
 *
 *  Created on: May 22, 2026
 *      Author: texasjoe23
 */

#include "arm_protocol.h"

#include "arm_motion.h"
#include "arm_safety.h"

#include <stdio.h>
#include <string.h>


extern UART_HandleTypeDef huart2;

char rxBuf[RX_BUF_SIZE];

static int rxIndex = 0;
static uint8_t rxChar = 0;

ArmState armState;
bool commandReady = false;

bool checkCommandReady(){
	if(commandReady){
		commandReady = false;
		return true;
	}
	return false;
}

void UART_START(){
	HAL_UART_Receive_IT(&huart2, &rxChar, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        if (rxChar != '\n' && rxIndex < RX_BUF_SIZE - 1)
        {
            rxBuf[rxIndex++] = rxChar;
        }
        else
        {
            rxBuf[rxIndex] = '\0';

            commandReady = true;

            rxIndex = 0;
        }

        HAL_UART_Receive_IT(&huart2, &rxChar, 1);
    }
}


bool ParsePoseCommand(char *cmd, PoseCommand *pose)
{
    return sscanf(cmd,
                  "POSE %f %f %f",
                  &pose->base,
                  &pose->elbow,
                  &pose->wrist ) == 3;
}
void ApplyPose( PoseCommand pose){
		arm.base.target_angle = pose.base;
		arm.elbow.target_angle = pose.elbow;
		arm.wrist.target_angle = pose.wrist;
}

bool ProcessPose(char *cmd)
{
    PoseCommand pose;

    if (!ParsePoseCommand(cmd, &pose))
        return false;

    if (ValidatePose(&pose) != POSE_OK)
        return false;

    ApplyPose(pose);
    return true;
}

bool ProcessVelo(char *cmd)
{
    if (sscanf(cmd,
               "VELO %f %f %f %f",
               &arm.base.velocity,
               &arm.elbow.velocity,
               &arm.wrist.velocity,
               &arm.gripper.velocity) != 4)
    {
        SendMessage("ERR:BAD_VELO\n");
        return false;
    }

    SendMessage("OK:VELO\n");
    return true;
}


bool ParseGripCommand(char *cmd, GripCommand *grip)
{
    return sscanf(cmd,
                  "GRIP %f %f",
                  &grip->target,
                  &grip->speed) == 2;
}

void ApplyGrip(GripCommand grip){
	arm.gripper.target_angle = grip.target;
}

bool ProcessGrip(char *cmd)
{
    GripCommand grip;

    if (!ParseGripCommand(cmd, &grip))
        return false;

    if(!ValidateGrip(&grip))
    	return false;

    ApplyGrip(grip);
    return true;
}



void SendMessage(char *msg)
{
	//Blocking but is low-rate
    HAL_UART_Transmit(&huart2,
                      (uint8_t*)msg,
                      strlen(msg),
                      HAL_MAX_DELAY);
}

CMDType GetCommandType(char *cmd)
{
    if (strncmp(cmd, "PING", 4) == 0) return CMD_PING;
    if (strncmp(cmd, "POSE", 4) == 0) return CMD_POSE;
    if (strncmp(cmd, "GRIP", 4) == 0) return CMD_GRIP;
    if (strncmp(cmd, "STOP", 4) == 0) return CMD_STOP;
    if (strncmp(cmd, "VELO", 4) == 0) return CMD_VELO;
    return CMD_NONE;
}

bool ProcessCommand(char *cmd)
{
	 switch (GetCommandType(cmd))
	    {
	        case CMD_PING:
	            SendMessage("READY\n");
	            return true;

	        case CMD_POSE:
	            return ProcessPose(cmd);

	        case CMD_GRIP:
	            return ProcessGrip(cmd);
	        case CMD_VELO:
	        	return ProcessVelo(cmd);

	        default:
	            SendMessage("ERR:UNKNOWN_CMD\n");
	            return false;
	    }




    return true;
}

void SendErrorMessage(PoseError err)
{
    const char *msg;

    switch (err)
    {
        case POSE_ERR_BASE_LIMIT:
            msg = "ERR:BASE_LIMIT\n";
            break;

        case POSE_ERR_GRIPPER_LIMIT:
            msg = "ERR:GRIPPER_LIMIT\n";
            break;

        case POSE_ERR_COLLISION_RISK:
            msg = "ERR:COLLISION_RISK\n";
            break;

        default:
            msg = "ERR:UNKNOWN\n";
            break;
    }

    SendMessage((char*)msg);
}

