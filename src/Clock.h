// SPDX-License-Identifier: Beerware
/**
 * @file  Clock.h
 * @brief Clock handler
 */
#pragma once

#include <stdint.h>

uint8_t* Clock_GetBufferAddr(void);
void     Clock_Update(void);

#ifdef USE_BMP180
void     Clock_SetTemperature(int8_t s8Temp);
#endif
