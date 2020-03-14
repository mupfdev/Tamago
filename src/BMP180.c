// SPDX-License-Identifier: Beerware
/**
 * @file      BMP180.c
 * @brief     Digital pressure sensor driver
 * @details   Bosch Sensortec BMP180 I²C digital pressure sensor
 * @ingroup   BMP180
 * @defgroup  BMP180 BMP180 I²C digital pressure sensor
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#ifdef USE_BMP180

#include <stdint.h>
#include "BMP180.h"
#include "MCAL.h"

/**
 * @enum  BMP180MemoryMap
 * @brief BMP180 Global memory map
 */
typedef enum
{
    E2PROM_AC1_MSB = 0xAA,
    E2PROM_AC1_LSB = 0xAB,
    E2PROM_AC2_MSB = 0xAC,
    E2PROM_AC2_LSB = 0xAD,
    E2PROM_AC3_MSB = 0xAE,
    E2PROM_AC3_LSB = 0xAF,
    E2PROM_AC4_MSB = 0xB0,
    E2PROM_AC4_LSB = 0xB1,
    E2PROM_AC5_MSB = 0xB2,
    E2PROM_AC5_LSB = 0xB3,
    E2PROM_AC6_MSB = 0xB4,
    E2PROM_AC6_LSB = 0xB5,
    E2PROM_B1_MSB  = 0xB6,
    E2PROM_B1_LSB  = 0xB7,
    E2PROM_B2_MSB  = 0xB8,
    E2PROM_B2_LSB  = 0xB9,
    E2PROM_MB_MSB  = 0xBA,
    E2PROM_MB_LSB  = 0xBB,
    E2PROM_MC_MSB  = 0xBC,
    E2PROM_MC_LSB  = 0xBD,
    E2PROM_MD_MSB  = 0xBE,
    E2PROM_MD_LSB  = 0xBF

} BMP180MemoryMap;

/**
 * @struct BMP180CalibCoefficients
 * @brief  BMP180 Calibration coefficients
 */
typedef struct
{
    int16_t  s16AC1; ///< Calibration coeff. AC1
    int16_t  s16AC2; ///< Calibration coeff. AC2
    int16_t  s16AC3; ///< Calibration coeff. AC3
    uint16_t u16AC4; ///< Calibration coeff. AC4
    uint16_t u16AC5; ///< Calibration coeff. AC5
    uint16_t u16AC6; ///< Calibration coeff. AC6
    int16_t  s16B1;  ///< Calibration coeff. B1
    int16_t  s16B2;  ///< Calibration coeff. B2
    int16_t  s16MB;  ///< Calibration coeff. MB
    int16_t  s16MC;  ///< Calibration coeff. MC
    int16_t  s16MD;  ///< Calibration coeff. MD

} BMP180CalibCoefficients;

/**
 * @struct BMP180Data
 * @brief  BMP180 driver data
 */
typedef struct
{
    BMP180CalibCoefficients stCalibData; ///< Calibration coefficients

} BMP180Data;

/**
 * @var   _stBMP180Data
 * @brief BMP180 driver private data
 */
static BMP180Data _stBMP180Data = { 0 };

/**
 * @brief  Initialise BMP180 driver
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int BMP180_Init(void)
{
    int nError;

    // Read calibration data from the E²PROM of the BMP180
    nError = I2C_Receive(BMP180_ADDRESS_READ, E2PROM_AC1_MSB, (uint8_t*)&_stBMP180Data.stCalibData, 22);
    if (0 != nError)
    {
        return -1;
    }

    return 0;
}

#endif // USE_BMP180
