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
#include "MCAL.h"

#ifdef USE_BMP180
#include <stdlib.h>
#include "BMP180.h"
#endif

/**
 * @struct ClockData
 * @brief  Clock handler data
 */
typedef struct
{
    uint8_t      u8Hours;       ///< Hours (0-23)
    uint8_t      u8Minutes;     ///< Minutes (0-59)
    uint8_t      u8Seconds;     ///< Seconds (0-59)

    #ifdef USE_BMP180
    int8_t       s8Temperature; ///< Temperature in 1°C
    #endif

    uint8_t      au8Buffer[64]; ///< Buffer for current clock-face

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
    uint8_t u8Digit[6] = { 0 };

    // Fetch current time from RTC
    RTC_GetTime(&_stClock.u8Hours, &_stClock.u8Minutes, &_stClock.u8Seconds);

    // Extract digits
    #ifdef USE_BMP180
    u8Temp = abs(_stClock.s8Temperature);
    for (s8Idx = 5; s8Idx >= 4; s8Idx--)
    {
        u8Digit[s8Idx]  = u8Temp % 10;
        u8Temp         /= 10;
    }
    #endif

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
        uint8_t u8IdxStart = 20;
        uint8_t u8IdxEnd   = 38;
        #ifdef USE_BMP180
        u8IdxStart =  8;
        u8IdxEnd   = 26;
        #endif

        u8Offset = u8Digit[u8Dig];

        for (uint8_t u8Idx = u8IdxStart + u8Dig; u8Idx <= u8IdxEnd + u8Dig; u8Idx += 4)
        {
            _stClock.au8Buffer[u8Idx] = _au8ClockFont[u8Offset];
            u8Offset += 10;
        }
    }

    #ifdef USE_BMP180
    for (uint8_t u8Dig = 4; u8Dig < 6; u8Dig++)
    {
        u8Offset = u8Digit[u8Dig];

        for (uint8_t u8Idx = 33 + u8Dig; u8Idx <= 51 + u8Dig; u8Idx += 4)
        {
            _stClock.au8Buffer[u8Idx] = _au8ClockFont[u8Offset];
            u8Offset += 10;
        }
    }
    #endif

    // Add clock-face divider
    #ifndef USE_BMP180
    _stClock.au8Buffer[25] |= 1 << 0;
    _stClock.au8Buffer[33] |= 1 << 0;
    #else
    _stClock.au8Buffer[13] |= 1 << 0;
    _stClock.au8Buffer[21] |= 1 << 0;

    // Add degree symbol
    _stClock.au8Buffer[34] |= 1 << 0;
    _stClock.au8Buffer[35] |= 1 << 7;
    _stClock.au8Buffer[38] |= 1 << 0;
    _stClock.au8Buffer[39] |= 1 << 7;

    // Add minus sign if temperature is below 0°C
    if (0 > _stClock.s8Temperature)
    {
        _stClock.au8Buffer[44] |= 1 << 0;
        _stClock.au8Buffer[44] |= 1 << 1;
    }
    #endif
}
