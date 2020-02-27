// SPDX-License-Identifier: Beerware
/**
 * @file      Tamago.c
 * @brief     Tamago game handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdbool.h>
#include "FreeRTOS.h"
#include "System.h"
#include "Tamago.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "task.h"

extern SPI_HandleTypeDef hspi1;
extern uint8_t           au8Sprite[];

static void DisplayThread(void* pArg);
static void LifeCycleThread(void* pArg);

/**
 * @struct GameHandler
 * @brief  Game handler data
 */
typedef struct
{
    Stats        stStats;          ///< Statistics
    Animation    stAnim;           ///< Current animation
    bool         bIsRunning;       ///< Is running state
    bool         bIsPaused;        ///< Pause status
    TaskHandle_t hLifeCycleThread; ///< Life cycle thread handle
    TaskHandle_t hDisplayThread;   ///< Display thread handle

} GameHandler;

/**
 * @var   stGameHandler
 * @brief Game handler private data
 */
static GameHandler stGameHandler = { 0 };

/**
 * @brief  Initialise Tamago
 * @return Error code
 * @retval 1: OK
 * @retval 0: Error
 */
int Tamago_Init(void)
{
    BaseType_t nStatus = pdPASS;

    stGameHandler.bIsRunning = true;

    nStatus = xTaskCreate(
        DisplayThread,
        "Display thread",
        configMINIMAL_STACK_SIZE,
        NULL,
        osPriorityNormal,
        &stGameHandler.hDisplayThread);

    nStatus = xTaskCreate(
        LifeCycleThread,
        "Life cycle thread",
        configMINIMAL_STACK_SIZE,
        NULL,
        osPriorityNormal,
        &stGameHandler.hLifeCycleThread);

    if (pdPASS != nStatus)
    {
        return 0;
    }

    return (pdPASS != nStatus) ? (0) : (1);
}

/**
 * @brief Display thread
 * @param pArg: Unused
 */
static void DisplayThread(void* pArg)
{
    while (stGameHandler.bIsRunning)
    {

        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        osDelay(REFRESH_RATE_IN_MS);
    }
}

/**
 * @brief Life cycle thread
 * @param pArg: Unused
 */
static void LifeCycleThread(void* pArg)
{
    while (stGameHandler.bIsRunning)
    {
        if (stGameHandler.bIsPaused)
        {
            osDelay(1);
            continue;
        }
        osDelay(1);
    }
}
