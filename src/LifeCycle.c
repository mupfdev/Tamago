// SPDX-License-Identifier: Beerware
/**
 * @file      LifeCycle.c
 * @brief     Life cycle handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdbool.h>
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
    while (stLifeCycle.bIsRunning)
    {
        osDelay(1);
    }
}
