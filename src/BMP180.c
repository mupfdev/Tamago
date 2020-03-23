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
 * @enum  BMP180_MemoryMap
 * @brief BMP180 Global memory map
 */
typedef enum
{
    E2PROM_AC1_MSB = 0xAA, ///< Calibration coeff. AC1 MSB
    E2PROM_AC1_LSB = 0xAB, ///< Calibration coeff. AC1 LSB
    E2PROM_AC2_MSB = 0xAC, ///< Calibration coeff. AC2 MSB
    E2PROM_AC2_LSB = 0xAD, ///< Calibration coeff. AC2 LSB
    E2PROM_AC3_MSB = 0xAE, ///< Calibration coeff. AC3 MSB
    E2PROM_AC3_LSB = 0xAF, ///< Calibration coeff. AC3 LSB
    E2PROM_AC4_MSB = 0xB0, ///< Calibration coeff. AC4 MSB
    E2PROM_AC4_LSB = 0xB1, ///< Calibration coeff. AC4 LSB
    E2PROM_AC5_MSB = 0xB2, ///< Calibration coeff. AC5 MSB
    E2PROM_AC5_LSB = 0xB3, ///< Calibration coeff. AC5 LSB
    E2PROM_AC6_MSB = 0xB4, ///< Calibration coeff. AC6 MSB
    E2PROM_AC6_LSB = 0xB5, ///< Calibration coeff. AC6 LSB
    E2PROM_B1_MSB  = 0xB6, ///< Calibration coeff. B1 MSB
    E2PROM_B1_LSB  = 0xB7, ///< Calibration coeff. B1 LSB
    E2PROM_B2_MSB  = 0xB8, ///< Calibration coeff. BS MSB
    E2PROM_B2_LSB  = 0xB9, ///< Calibration coeff. B2 LSB
    E2PROM_MB_MSB  = 0xBA, ///< Calibration coeff. MB MSB
    E2PROM_MB_LSB  = 0xBB, ///< Calibration coeff. MB LSB
    E2PROM_MC_MSB  = 0xBC, ///< Calibration coeff. MC MSB
    E2PROM_MC_LSB  = 0xBD, ///< Calibration coeff. MC LSB
    E2PROM_MD_MSB  = 0xBE, ///< Calibration coeff. MD MSB
    E2PROM_MD_LSB  = 0xBF, ///< Calibration coeff. MD LSB
    CHIP_ID        = 0xD0, ///< Chip-ID, can be checked against @ref BMP180_CHIP_ID
    SOFT_RESET     = 0xE0, ///< Soft reset if set to 0xB6
    CTRL_MEAS      = 0xF4, ///< Measurement control
    OUT_MSB        = 0xF6, ///< ADC out LSB
    OUT_LSB        = 0xF7, ///< ADC out MSB
    OUT_XLSB       = 0xF8  ///< ADC out XLSB

} BMP180_MemoryMap;

/**
 * @struct BMP180_CalibCoefficients
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

} BMP180_CalibCoefficients;

/**
 * @struct BMP180_Data
 * @brief  BMP180 driver data
 */
typedef struct
{
    uint8_t                  u8ChipID;    ///< Chip-ID
    BMP180_CalibCoefficients stCalibData; ///< Calibration coefficients

} BMP180_Data;

/**
 * @var   _stBMP180Data
 * @brief BMP180 driver private data
 */
static BMP180_Data _stBMP180Data = { 0 };

/**
 * @brief  Initialise BMP180 driver
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int BMP180_Init(void)
{
    int nError;

    // Check if communicaton is functioning
    nError = I2C_Receive(BMP180_ADDRESS_READ, CHIP_ID, I2C_MEMSIZE_8BIT, &_stBMP180Data.u8ChipID, 1);
    if (0 != nError)
    {
        return -1;
    }
    I2C_WaitUntilReady(BMP180_ADDRESS_READ);

    if (BMP180_CHIP_ID != _stBMP180Data.u8ChipID)
    {
        // Error: invalid chip-ID
        return -1;
    }

    // Read calibration data from E²PROM
    nError = I2C_Receive(BMP180_ADDRESS_READ, E2PROM_AC1_MSB, I2C_MEMSIZE_8BIT, (uint8_t*)&_stBMP180Data.stCalibData, 22);
    if (0 != nError)
    {
        return -1;
    }
    I2C_WaitUntilReady(BMP180_ADDRESS_READ);

    return 0;
}

#endif // USE_BMP180
