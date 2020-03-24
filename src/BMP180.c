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
 * @enum  BMP180_Register
 * @brief BMP180 register (global memory map)
 */
typedef enum
{
    E2PROM_AC1 = 0xAA, ///< Calibration coeff. AC1
    E2PROM_AC2 = 0xAC, ///< Calibration coeff. AC2
    E2PROM_AC3 = 0xAE, ///< Calibration coeff. AC3
    E2PROM_AC4 = 0xB0, ///< Calibration coeff. AC4
    E2PROM_AC5 = 0xB2, ///< Calibration coeff. AC5
    E2PROM_AC6 = 0xB4, ///< Calibration coeff. AC6
    E2PROM_B1  = 0xB6, ///< Calibration coeff. B1
    E2PROM_B2  = 0xB8, ///< Calibration coeff. BS
    E2PROM_MB  = 0xBA, ///< Calibration coeff. MB
    E2PROM_MC  = 0xBC, ///< Calibration coeff. MC
    E2PROM_MD  = 0xBE, ///< Calibration coeff. MD
    CHIP_ID    = 0xD0, ///< Chip-ID, can be checked against @ref BMP180_CHIP_ID
    SOFT_RESET = 0xE0, ///< Soft reset if set to 0xB6
    CTRL_MEAS  = 0xF4, ///< Measurement control
    OUT_MSB    = 0xF6, ///< ADC out LSB
    OUT_LSB    = 0xF7, ///< ADC out MSB
    OUT_XLSB   = 0xF8  ///< ADC out XLSB

} BMP180_Register;

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

static int _BMP180_ReadRegister(const BMP180_Register eReg, int16_t* ps16Value);

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
    _BMP180_ReadRegister(E2PROM_AC1, &_stBMP180Data.stCalibData.s16AC1);
    _BMP180_ReadRegister(E2PROM_AC2, &_stBMP180Data.stCalibData.s16AC2);
    _BMP180_ReadRegister(E2PROM_AC3, &_stBMP180Data.stCalibData.s16AC3);
    _BMP180_ReadRegister(E2PROM_AC4, (int16_t*)&_stBMP180Data.stCalibData.u16AC4);
    _BMP180_ReadRegister(E2PROM_AC5, (int16_t*)&_stBMP180Data.stCalibData.u16AC5);
    _BMP180_ReadRegister(E2PROM_AC6, (int16_t*)&_stBMP180Data.stCalibData.u16AC6);
    _BMP180_ReadRegister(E2PROM_B1,  &_stBMP180Data.stCalibData.s16B1);
    _BMP180_ReadRegister(E2PROM_B2,  &_stBMP180Data.stCalibData.s16B2);
    _BMP180_ReadRegister(E2PROM_MB,  &_stBMP180Data.stCalibData.s16MB);
    _BMP180_ReadRegister(E2PROM_MC,  &_stBMP180Data.stCalibData.s16MC);
    _BMP180_ReadRegister(E2PROM_MD,  &_stBMP180Data.stCalibData.s16MD);

    return 0;
}

/**
 * @brief  Read current temperature
 * @param  ps8Temp
 *         Temperature in 1°C
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int BMP180_ReadTemperature(int8_t* ps8Temp)
{
    int     nError;
    uint8_t u8RegValue = OSS_TEMPERATURE;
    int32_t s32UT      = 0U;
    float   fX1        = 0.f;
    float   fX2        = 0.f;
    float   fB5        = 0.f;
    float   fT         = 0.f;

    // Trigger temperature conversion
    nError = I2C_Transmit(BMP180_ADDRESS_WRITE, CTRL_MEAS, I2C_MEMSIZE_8BIT, &u8RegValue, 1);
    if (0 != nError)
    {
        return -1;
    }
    I2C_WaitUntilReady(BMP180_ADDRESS_READ);

    // Wait until conversion is complete
    MCAL_Sleep(5);

    // Read uncompensated temperature value
    nError = _BMP180_ReadRegister(OUT_MSB, (int16_t*)&s32UT);
    if (0 != nError)
    {
        return -1;
    }

    // Calculate true temperature
    fX1  = ((float)s32UT - (float)_stBMP180Data.stCalibData.u16AC6);
    fX1 *= ((float)_stBMP180Data.stCalibData.u16AC5 / 32768.f);

    fX2  = ((float)_stBMP180Data.stCalibData.s16MC * 2048.f);
    fX2 /= (fX1 + (float)_stBMP180Data.stCalibData.s16MD);

    fB5  = fX1 + fX2;

    fT   = (fB5 + 8.f);
    fT  /= 16.f;

    *ps8Temp = (int8_t)(fT / 10.f);

    return 0;
}

/**
 * @brief  Read register
 * @param  eReg
 *         BMP180 E²PROM register
 * @param  ps16Value
 *         Register value
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
static int _BMP180_ReadRegister(const BMP180_Register eReg, int16_t* ps16Value)
{
    int nError;

    if (OUT_LSB < eReg)
    {
        return -1;
    }

    nError = I2C_Receive(BMP180_ADDRESS_READ, eReg, I2C_MEMSIZE_8BIT, (uint8_t*)ps16Value, 2);
    if (0 != nError)
    {
        return -1;
    }
    I2C_WaitUntilReady(BMP180_ADDRESS_READ);

    *ps16Value = ((*ps16Value << 8) + (*ps16Value >> 8));

    return 0;
}

#endif // USE_BMP180
