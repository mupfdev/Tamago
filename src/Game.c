// SPDX-License-Identifier: Beerware
/**
 * @file      Game.c
 * @brief     Tamago game handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdbool.h>
#include "FreeRTOS.h"
#include "Game.h"
#include "cmsis_os.h"
#include "task.h"

/**
 * @struct GameHandler
 * @brief  Game handler data
 */
typedef struct
{
    Stats        stStats;     ///< Statistics
    Animation    stAnim;      ///< Current animation
    bool         bIsRunning;  ///< Is running state
    TaskHandle_t hLifeCycle;  ///< Life cycle thread handler

} GameHandler;

/**
 * @var   stGameHandler
 * @brief Game handler private data
 */
static GameHandler stGameHandler;
