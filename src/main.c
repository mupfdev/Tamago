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

static TaskHandle_t _hMainThread;                          ///< Main thread handle
static void         _SetAnimationByStats(Stats* pstStats); ///< Set animation

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
    Stats* pstStats = LifeCycle_GetStats();

    DMD_SetBuffer(Animation_GetBufferAddr());

    while (1)
    {
        _SetAnimationByStats(pstStats);
        osDelay(5);
    }
}

/**
 * @brief Set animation by pet statistics
 * @param pstStats
 *        Pointer to pet statistics
 */
static void _SetAnimationByStats(Stats* pstStats)
{
    Animation_SetUpdateRate(500);

    switch (pstStats->eEvolution)
    {
        case EGG:
            Animation_Set(IDLE_EGG);
            break;
        case BABYTCHI:
            Animation_Set(IDLE_BABYTCHI);
            break;
        case MARUTCHI:
            Animation_Set(IDLE_MARUTCHI);
            break;
        case TAMATCHI:
            Animation_Set(IDLE_TAMATCHI);
            break;
        case KUCHITAMATCHI:
            Animation_Set(IDLE_KUCHITAMATCHI);
            break;
        case MAMETCHI:
            Animation_Set(IDLE_MAMETCHI);
            break;
        case GINJIROTCHI:
            Animation_Set(IDLE_GINJIROTCHI);
            break;
        case MASKUTCHI:
            Animation_Set(IDLE_MASKUTCHI);
            break;
        case KUCHIPATCHI:
            Animation_Set(IDLE_KUCHIPATCHI);
            break;
        case NYOROTCHI:
            Animation_Set(IDLE_NYOROTCHI);
            break;
        case TARAKOTCHI:
            Animation_Set(IDLE_TARAKOTCHI);
            break;
        case OYAJITCHI:
            Animation_Set(IDLE_OYAJITCHI);
            break;
        case OBAKETCHI:
            Animation_SetUpdateRate(750);
            Animation_Set(IDLE_OBAKETCHI);
            break;
    }

    if (LifeCycle_IsFlagSet(HAS_POOPED))
    {
        Animation_ShowIcon(ICON_POO, true);
    }
    else
    {
        Animation_ShowIcon(ICON_POO, false);
    }

    if (LifeCycle_IsFlagSet(IS_SICK))
    {
        Animation_ShowIcon(ICON_SKULL, true);
    }
    else
    {
        Animation_ShowIcon(ICON_SKULL, false);
    }

    if (LifeCycle_IsFlagSet(IS_SLEEPING))
    {
        Animation_ShowIcon(ICON_SLEEP, true);
    }
    else
    {
        Animation_ShowIcon(ICON_SLEEP, false);
    }
}
