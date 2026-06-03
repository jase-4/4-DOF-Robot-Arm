/*
 * main_arm.c
 *
 *  Created on: May 14, 2026
 *      Author: texasjoe23
 */

#include "main_arm.h"



void arm_main(){



	InitArm();


	while(1)
	{

		  if (checkCommandReady())
		        {

		            if (ProcessCommand(rxBuf))
		            {
		            	 armState = ARM_MOVING;
		            	  SendMessage("OK\n");
		           }
		            else
		           {
		            	 armState = ARM_ERROR;
		           }

		        }

	        UpdateAllServos();

	        if (armState == ARM_MOVING && ArmAtTarget())
	        {
	            SendMessage("DONE\n");
	            armState = ARM_IDLE;
	        }


	          }

	}




