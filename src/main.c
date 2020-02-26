// SPDX-License-Identifier: Beerware
/**
 * @file      main.c
 * @brief     Tamago, a clone of the famous digital pet from 1996
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdint.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "System.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "task.h"

static TaskHandle_t      hMainThread = NULL;
extern SPI_HandleTypeDef hspi1;
extern uint8_t           au8Sprite[];

static void MainThread(void* pArg);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    static uint16_t u16Rate = 50;

    if (SYSTEM_OK != System_Init())
    {
        u16Rate = 50;
    }

    xTaskCreate(
        MainThread,
        "Main thread",
        configMINIMAL_STACK_SIZE,
        &u16Rate,
        osPriorityNormal,
        &hMainThread);

    osKernelStart();
    while(1);

    return EXIT_SUCCESS;
}

/**
 * @brief Main thread handler
 * @param pArg: Loop delay in ms
 */
static void MainThread(void* pArg)
{
    uint16_t u16Buf = 0xafaf;

    while(1)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        HAL_SPI_Transmit_IT(&hspi1, (uint8_t*)&u16Buf, 2);

        osDelay(*(uint16_t*)pArg);
    };
}
