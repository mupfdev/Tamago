// SPDX-License-Identifier: Beerware
/**
 * @file    M24FC256.h
 * @brief   24FC256 driver
 * @ingroup 24FC256
 */
#pragma once

#ifdef USE_M24FC256

#include <stdint.h>

#define M24FC256_ADDRESS  0xA0 ///< 4-bit control code for read- and write operations
#define M24FC256_PAGESIZE 0x40 ///< EEPROM page size

int M24FC256_Read(uint16_t u16Address, uint8_t *pu8TxBuffer, uint8_t u8Pages);
int M24FC256_Write(uint16_t u16Address, uint8_t *pu8TxBuffer, uint8_t u8Pages);

#endif // USE_M24FC256
