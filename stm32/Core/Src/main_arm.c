/*
 * main_arm.c
 *
 *  Created on: May 14, 2026
 *      Author: texasjoe23
 */

#include "main_arm.h"
volatile bool controlTick = false;

void arm_main(void)
{
    InitArm();

    while (1)
    {
        if (controlTick)
        {
            controlTick = false;

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
}
