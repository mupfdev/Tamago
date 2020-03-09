// SPDX-License-Identifier: Beerware
/**
 * @file      Tamago.c
 * @brief     Tamago main application handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "Animation.h"
#include "Clock.h"
#include "DMD.h"
#include "FreeRTOS.h"
#include "LifeCycle.h"
#include "Tamago.h"
#include "cmsis_os.h"
#include "task.h"

static void _TamagoThread(void* pArg);

static TaskHandle_t _hTamagoThread;                        ///< Tamago main thread handle
static void         _SetAnimationByStats(Stats* pstStats); ///< Set animation

/**
 * @brief  Initialise Tamago main application handler
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int Tamago_Init(void)
{
    BaseType_t nStatus = pdPASS;
    int        nError  = 0;

    nError = DMD_Init();
    if (0 != nError)
    {
        return -1;
    }

    nError = Animation_Init();
    if (0 != nError)
    {
        return -1;
    }

    nError = Clock_Init();
    if (0 != nError)
    {
        return -1;
    }

    nError = LifeCycle_Init();
    if (0 != nError)
    {
        return -1;
    }

    nStatus = xTaskCreate(
        _TamagoThread,
        "Tamago",
        configMINIMAL_STACK_SIZE,
        NULL,
        osPriorityNormal,
        &_hTamagoThread);

    if (pdPASS == nStatus)
    {
        osKernelStart();
    }
    else
    {
        return -1;
    }

    return 0;
}

/**
 * @brief Tamago main thread
 * @param pArg: Unused
 */
static void _TamagoThread(void* pArg)
{
    Stats* pstStats = LifeCycle_GetStats();

    DMD_SetBuffer(Animation_GetBufferAddr());
    //DMD_SetBuffer(Clock_GetBufferAddr());

    while (1)
    {
        _SetAnimationByStats(pstStats);
        osDelay(10);
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
