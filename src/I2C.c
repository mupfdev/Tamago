// SPDX-License-Identifier: Beerware
/**
 * @example   I2C.c
 * @brief     I²C interface
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdint.h>
#include "STBrickLib.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

/**
 * @var   hi2c1
 * @brief I²C handle
 */
I2C_HandleTypeDef hi2c1;

/**
 * @brief  Receive an amount via I²C
 * @param  u16DevAddress
 *         Target device address
 * @param  u16MemAddress
 *         Internal memory address
 * @param  pu8RxBuffer
 *         Pointer to data buffer
 * @param  u16Size
 *         Amount of data to be sent
 * @return Status code
 */
StatusCode I2C_Receive(uint16_t u16DevAddress, uint16_t u16MemAddress, uint8_t* pu8RxBuffer, uint16_t u16Size)
{
    if (HAL_OK != HAL_I2C_Mem_Read(
            &hi2c1,
            u16DevAddress,
            u16MemAddress,
            I2C_MEMADD_SIZE_16BIT,
            pu8RxBuffer,
            u16Size,
            300))
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

/**
 * @brief  Transmit an amount via I²C
 * @param  u16DevAddress
 *         Target device address
 * @param  u16MemAddress
 *         Internal memory address
 * @param  pu8TxBuffer
 *         Pointer to data buffer
 * @param  u16Size
 *         Amount of data to be sent
 * @return Status code
 */
StatusCode I2C_Transmit(uint16_t u16DevAddress, uint16_t u16MemAddress, uint8_t* pu8TxBuffer, uint16_t u16Size)
{
    if (HAL_OK != HAL_I2C_Mem_Write(
        &hi2c1,
        u16DevAddress,
        u16MemAddress,
        I2C_MEMADD_SIZE_16BIT,
        pu8TxBuffer,
        u16Size,
        300))
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

/**
 * @brief   Wait for the end of the transfer
 * @details Before starting a new communication transfer, the CPU need
 *          to check the current state of the peripheral; if it's busy
 *          the CPU need to wait for the end of current transfer before
 *          starting a new one.
 * @param   u16DevAddress
 *          Target device address
 */
void I2C_WaitUntilReady(uint16_t u16DevAddress)
{
    while (HAL_I2C_STATE_READY != HAL_I2C_GetState(&hi2c1));

    while (HAL_TIMEOUT == HAL_I2C_IsDeviceReady(
               &hi2c1,
               u16DevAddress,
               100,
               300));

    while (HAL_I2C_STATE_READY != HAL_I2C_GetState(&hi2c1));
}
