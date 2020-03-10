// SPDX-License-Identifier: Beerware
/**
 * @file  Clock.h
 * @brief Clock handler
 */
#pragma once

#include <stdint.h>

int      Clock_Init(void);
uint8_t* Clock_GetBufferAddr(void);
void     Clock_Update(void);
