/*
 * arm_protocol.h
 *
 *  Created on: May 22, 2026
 *      Author: texasjoe23
 */

#ifndef SRC_ARM_PROTOCOL_H_
#define SRC_ARM_PROTOCOL_H_

#include "main.h"
#include "arm_types.h"

#include <stdbool.h>

#define RX_BUF_SIZE 64

extern bool commandReady;
extern volatile ArmState armState;
extern char rxBuf[];

void UART_START();

void SendMessage(char *msg);

bool checkCommandReady();

bool ProcessCommand(char *cmd);

bool ParsePoseCommand(char *cmd,
                      PoseCommand *pose);



#endif /* SRC_ARM_PROTOCOL_H_ */
