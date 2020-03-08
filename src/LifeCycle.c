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
#include "cmsis_os.h"
#include "task.h"

static void _LifeCycleThread(void* pArg);

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
 * @var   _stLifeCycle
 * @brief Life cycle handler private data
 */
static LifeCycleData _stLifeCycle = { 0 };

/**
 * @brief  Initialise life cycle
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int LifeCycle_Init(void)
{
    BaseType_t nStatus = pdPASS;

    _stLifeCycle.stStats.eEvolution = EGG;
    _stLifeCycle.bIsRunning         = true;

    nStatus = xTaskCreate(
        _LifeCycleThread,
        "Life cycle",
        configMINIMAL_STACK_SIZE,
        NULL,
        osPriorityNormal,
        &_stLifeCycle.hLifeCycleThread);

    if (pdPASS != nStatus)
    {
        return -1;
    }

    return (pdPASS != nStatus) ? (-1) : (0);
}

/**
 * @brief  Get pet statistics
 * @return Pointer to stats
 */
Stats* LifeCycle_GetStats(void)
{
    return &_stLifeCycle.stStats;
}

/**
 * @brief  Check if status flag is set
 * @param  eFlag
 *         Status flag
 * @return Flag state
 * @retval true: Status flag is set
 * @retval false: Status flag is not set
 */
bool LifeCycle_IsFlagSet(StatusFlag eFlag)
{
    if ((_stLifeCycle.stStats.u16Flags >> eFlag) & 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Clear status flag
 * @param eFlag
 *        Status flag
 */
void LifeCycle_ClearFlat(StatusFlag eFlag)
{
    _stLifeCycle.stStats.u16Flags &= ~(1 << eFlag);
}

/**
 * @brief Set status flag
 * @param eFlag
 *        Status flag
 */
void LifeCycle_SetFlag(StatusFlag eFlag)
{
    _stLifeCycle.stStats.u16Flags |= 1 << eFlag;
}

/**
 * @brief Life cycle thread
 * @param pArg: Unused
 */
static void _LifeCycleThread(void* pArg)
{
    while (_stLifeCycle.bIsRunning)
    {
        osDelay(1);
    }
}
