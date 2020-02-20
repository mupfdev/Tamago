// SPDX-License-Identifier: Beerware
/**
 * @file      main.c
 * @brief     Tamago, a clone of the famous digital pet from 1996
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdint.h>
#include <stdlib.h>
#include "EEPROM.h"
#include "FreeRTOS.h"
#include "MCP24FC256.h"
#include "STBrickLib.h"
#include "System.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "task.h"

osThreadId hMainThread;

static void     MainThread(void const* pArg);
static uint16_t u16BlinkDelay = 1000;

extern EepromData EEPROMData;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    if (SYSTEM_OK != System_Init())
    {
        u16BlinkDelay = 100;
    }

    if (STATUS_OK != MCP24FC256_Write(0, (uint8_t*)&EEPROMData, 2))
    {
        u16BlinkDelay = 200;
    }

    osThreadDef(hMainThread, MainThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
    hMainThread = osThreadCreate(osThread(hMainThread), NULL);

    osKernelStart();
    while(1);

    return EXIT_SUCCESS;
}

/**
 * @brief Main thread handler
 * @param pArg: Unused
 */
static void MainThread(void const* pArg)
{
    while(1)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        osDelay(u16BlinkDelay);
    };
}
