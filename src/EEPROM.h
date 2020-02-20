// SPDX-License-Identifier: Beerware
/**
 * @file  EEPROM.h
 * @brief EEPROM data
 */
#pragma once

#include <assert.h>
#include <stdint.h>

/**
 * @enum  EEPROMData
 * @brief EEPROM data
 */
typedef struct
{
    uint8_t u8Pg000[64];
    uint8_t u8Pg001[64];

} EepromData;

static_assert(128 == sizeof(EepromData), "Invalid EEPROM data size");
