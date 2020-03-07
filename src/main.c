// SPDX-License-Identifier: Beerware
/**
 * @file      main.c
 * @brief     Tamago, a clone of the famous digital pet from 1996
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "Animation.h"
#include "DMD.h"
#include "FreeRTOS.h"
#include "LifeCycle.h"
#include "MCAL.h"
#include "System.h"
#include "cmsis_os.h"
#include "task.h"

static void _MainThread(void* pArg);

static TaskHandle_t _hMainThread; ///< Main thread handle

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    BaseType_t nStatus = pdPASS;

    System_Init();
    DMD_Init();
    Animation_Init();
    LifeCycle_Init();

    nStatus = xTaskCreate(
        _MainThread,
        "Main",
        configMINIMAL_STACK_SIZE,
        NULL,
        osPriorityNormal,
        &_hMainThread);

    if (pdPASS == nStatus)
    {
        osKernelStart();
    }

    while(1);
    return EXIT_SUCCESS;
}

/**
 * @brief Main application thread
 * @param pArg: Unused
 */
static void _MainThread(void* pArg)
{
    Animation_Set(IDLE_EGG);
    Animation_ShowIcon(ICON_POO, true);
    Animation_SetUpdateRate(500);
    DMD_SetBuffer(Animation_GetBufferAddr());

    while (1)
    {
        // Todo.
        osDelay(5);
    }
}
