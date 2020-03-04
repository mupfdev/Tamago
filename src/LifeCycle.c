// SPDX-License-Identifier: Beerware
/**
 * @file      LifeCycle.c
 * @brief     Life cycle handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdbool.h>
#include "Animation.h"
#include "FreeRTOS.h"
#include "LifeCycle.h"
#include "System.h"
#include "cmsis_os.h"
#include "task.h"

static void LifeCycleThread(void* pArg);

/**
 * @struct LifeCycleData
 * @brief  Life cycle handler data
 */
typedef struct
{
    bool         bIsRunning;       ///< Is running state
    bool         bIsPaused;        ///< Pause status
    Stats        stStats;          ///< Statistics
    TaskHandle_t hLifeCycleThread; ///< Life cycle thread handle

} LifeCycleData;

/**
 * @var   stLifeCycle
 * @brief Life cycle handler private data
 */
static LifeCycleData stLifeCycle = { 0 };

/**
 * @brief  Initialise life cycle
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int LifeCycle_Init(void)
{
    BaseType_t nStatus = pdPASS;

    stLifeCycle.bIsRunning = true;

    nStatus = xTaskCreate(
        LifeCycleThread,
        "Life cycle",
        configMINIMAL_STACK_SIZE,
        NULL,
        osPriorityNormal,
        &stLifeCycle.hLifeCycleThread);

    if (pdPASS != nStatus)
    {
        return -1;
    }

    return (pdPASS != nStatus) ? (-1) : (0);
}

/**
 * @brief Life cycle thread
 * @param pArg: Unused
 */
static void LifeCycleThread(void* pArg)
{
    static uint16_t u16Seconds = 0;

    while (stLifeCycle.bIsRunning)
    {
        uint32_t* pu32Age = &stLifeCycle.stStats.u32AgeInSeconds;

        if (stLifeCycle.bIsPaused)
        {
            osDelay(1);
            continue;
        }

        // Demo cycle.
        if (300 >= *pu32Age)
        {
            Animation_SetRefreshRate(500);
            Animation_Set(IDLE_EGG);
        }
        else if (302 >= *pu32Age)
        {
            Animation_Set(HATCH_EGG);
        }
        else if (3900 >= *pu32Age)
        {
            Animation_Set(IDLE_BABYTCHI);
        }
        else if (7500 >= *pu32Age)
        {
            Animation_Set(IDLE_MARUTCHI);
        }
        else if (18300 >= *pu32Age)
        {
            Animation_Set(IDLE_KUCHITAMATCHI);
        }
        else if (25500 >= *pu32Age)
        {
            Animation_Set(IDLE_KUCHIPATCHI);
        }
        // Demo cycle end

        osDelay(1);

        u16Seconds++;
        if (u16Seconds == 1000)
        {
            stLifeCycle.stStats.u32AgeInSeconds++;
            u16Seconds = 0;
        }
    }
}
