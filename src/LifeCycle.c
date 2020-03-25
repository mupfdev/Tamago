// SPDX-License-Identifier: Beerware
/**
 * @file      LifeCycle.c
 * @brief     Life cycle handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdbool.h>
#include "LifeCycle.h"

static void _LifeCycleThread(void* pArg);

/**
 * @struct LifeCycleData
 * @brief  Life cycle handler data
 */
typedef struct
{
    Stats stStats; ///< Statistics

} LifeCycleData;

/**
 * @var   _stLifeCycle
 * @brief Life cycle handler private data
 */
static LifeCycleData _stLifeCycle = { 0 };

/**
 * @brief  Initialise life cycle
 */
void LifeCycle_Init(void)
{
    _stLifeCycle.stStats.eEvolution = EGG;
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
