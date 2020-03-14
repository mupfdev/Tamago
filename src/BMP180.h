// SPDX-License-Identifier: Beerware
/**
 * @file    BMP180.h
 * @brief   Digital pressure sensor driver
 * @ingroup BMP180
 */
#pragma once

#ifdef USE_BMP180

#define BMP180_ADDRESS_READ  0xef ///< Device address for read operations
#define BMP180_ADDRESS_WRITE 0xee ///< Device address for write operations

#include <stdint.h>

/**
 * @brief   Hardware pressure sampling accuracy modes
 * @details Control registers values for different internal
 *          oversampling_setting (oss)
 */
typedef enum
{
    OSS_TEMPERATURE             = 0x2E, ///< Temperature, max conversion time 4.5ms
    OSS_PRESSURE_ULTRA_LOW_PWR  = 0x34, ///< Ultra low power, max. conversion time 4.5ms, 3uA
    OSS_PRESSURE_DEFAULT        = 0x74, ///< Standard, max. conversion time 7.5ms, 5uA
    OSS_PRESSURE_HIGH_RES       = 0xB4, ///< High resolution, max. conversion time 13.5ms, 7uA
    OSS_PRESSURE_ULTRA_HIGH_RES = 0xF4  ///< Ultra-high resolution, max conversion time 25.5ms, 12uA

} ControlRegValue;

int BMP180_Init(void);

#endif // USE_BMP180
