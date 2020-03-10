// SPDX-License-Identifier: Beerware
/**
 * @file      Clock.c
 * @brief     Clock handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdbool.h>
#include <stdint.h>
#include "Clock.h"
#include "FreeRTOS.h"
#include "MCAL.h"
#include "cmsis_os.h"
#include "task.h"

static void _ClockThread(void* pArg);

/**
 * @struct ClockData
 * @brief  Clock handler data
 */
typedef struct
{
    uint8_t      u8Hours;       ///< Hours (0-23)
    uint8_t      u8Minutes;     ///< Minutes (0-59)
    uint8_t      u8Seconds;     ///< Seconds (0-59)
    bool         bIsRunning;    ///< Running state
    uint8_t      au8Buffer[64]; ///< Buffer for current clock-face
    TaskHandle_t hClockThread;  ///< Clock thread handle

} ClockData;

/**
 * @var   _stClock
 * @brief Clock handler private data
 */
static ClockData _stClock = { 0 };

/**
 * @var   _au8ClockFont
 * @brief 6x6 Clock font
 */
static const uint8_t _au8ClockFont[50] = {
    0b01111100, 0b00001000, 0b01111000, 0b01111100, 0b01000000, 0b01111100, 0b01111100, 0b01111100, 0b01111100, 0b01111100,
    0b01001100, 0b00011000, 0b00000100, 0b00000100, 0b01000000, 0b01000000, 0b01000000, 0b00000100, 0b01000100, 0b01000100,
    0b01010100, 0b00001000, 0b00111000, 0b01111000, 0b01010000, 0b01111000, 0b01111100, 0b00001000, 0b01111100, 0b01111100,
    0b01100100, 0b00001000, 0b01000000, 0b00000100, 0b01111100, 0b00000100, 0b01000100, 0b00010000, 0b01000100, 0b00000100,
    0b01111100, 0b00011100, 0b01111100, 0b01111100, 0b00010000, 0b01111000, 0b01111100, 0b00010000, 0b01111100, 0b01111100,
};

/**
 * @brief  Initialise clock handler
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int Clock_Init(void)
{
    BaseType_t nStatus = pdPASS;

    nStatus = xTaskCreate(
        _ClockThread,
        "ClockHandler",
        configMINIMAL_STACK_SIZE,
        NULL,
        osPriorityNormal,
        &_stClock.hClockThread);

    return (pdPASS != nStatus) ? (-1) : (0);
}

/**
 * @brief  Get address of image buffer
 * @return Pointer to image buffer
 */
uint8_t* Clock_GetBufferAddr(void)
{
    return (unsigned char*)&_stClock.au8Buffer;
}

/**
 * @brief Update clock-face buffer
 */
void Clock_Update(void)
{
    int8_t  s8Idx;
    uint8_t u8Temp;
    uint8_t u8Offset;
    uint8_t u8Digit[4] = { 0 };

    // Extract digits
    u8Temp = _stClock.u8Minutes;
    for (s8Idx = 3; s8Idx >= 2; s8Idx--)
    {
        u8Digit[s8Idx]  = u8Temp % 10;
        u8Temp         /= 10;
    }

    u8Temp = _stClock.u8Hours;
    for (s8Idx = 1; s8Idx >= 0; s8Idx--)
    {
        u8Digit[s8Idx]  = u8Temp % 10;
        u8Temp         /= 10;
    }

    // Write digits to clock-face buffer
    for (uint8_t u8Dig = 0; u8Dig < 4; u8Dig++)
    {
        u8Offset = u8Digit[u8Dig];
        for (uint8_t u8Idx = 20 + u8Dig; u8Idx <= 38 + u8Dig; u8Idx += 4)
        {
            _stClock.au8Buffer[u8Idx] = _au8ClockFont[u8Offset];
            u8Offset += 10;
        }
    }

    // Add clock-face divider
    _stClock.au8Buffer[25] |= 1 << 0;
    _stClock.au8Buffer[33] |= 1 << 0;
}

/**
 * @brief Clock thread
 * @param pArg: Unused
 */
static void _ClockThread(void* pArg)
{
    _stClock.bIsRunning = true;

    while (_stClock.bIsRunning)
    {
        RTC_GetTime(&_stClock.u8Hours, &_stClock.u8Minutes, &_stClock.u8Seconds);
        Clock_Update();
        osDelay(10);
    }
}
