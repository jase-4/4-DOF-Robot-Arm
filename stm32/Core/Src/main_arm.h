/*
 * main_arm.h
 *
 *  Created on: May 14, 2026
 *      Author: texasjoe23
 */

#ifndef SRC_MAIN_ARM_H_
#define SRC_MAIN_ARM_H_

#include "main.h"
#include "arm_motion.h"
#include "arm_protocol.h"


void arm_main();

extern TIM_HandleTypeDef htim2;

#endif /* SRC_MAIN_ARM_H_ */


//MX_GPIO_Init();
//MX_USART2_UART_Init();
//MX_TIM2_Init();
//MX_TIM3_Init();
//
//HAL_UART_Receive_IT(&huart2, &rxChar, 1);
//
//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
//HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

//
//void SetServoPosition(uint8_t pos, uint32_t chan)
//	{
//	    uint16_t pulse = 1500; // default 90°
//	    switch(pos)
//	    {
//	        case 1: pulse = 500; break;  // 45°
//	        case 2: pulse = 1500; break;  // 90°
//	        case 3: pulse = 1750; break;  // 135°
//	        case 4: pulse = 2250; break;  // 180°
//	        default: pulse = 1500; break; // fallback to 90°
//	    }
//	    __HAL_TIM_SET_COMPARE(&htim3, chan, pulse);
//	}

