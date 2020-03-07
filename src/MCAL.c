// SPDX-License-Identifier: Beerware
/**
 * @file      MCAL.c
 * @brief     Microcontroller Abstraction Layer
 * @details   MCAL for STM32F1xx microcontroller
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdint.h>
#include "MCAL.h"
#include "System.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal_tim.h"

extern I2C_HandleTypeDef hi2c2;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim1;

static GPIO_TypeDef* _ConvertGPIOPort(GPIOPort ePort);

/**
 * @brief Microsecond delay (blocking)
 * @param u16Delay
 *        Delay in microseconds
 */
void MCAL_DelayUS(uint16_t u16Delay)
{
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (u16Delay > __HAL_TIM_GET_COUNTER(&htim1));
}

/**
 * @brief Pull output pin(s) low
 * @param ePort
 *        GPIO port
 * @param u16PinMask
 *        Pin mask
 */
void GPIO_PullDown(GPIOPort ePort, uint16_t u16PinMask)
{
    GPIO_TypeDef* phPort = _ConvertGPIOPort(ePort);
    HAL_GPIO_WritePin(phPort, u16PinMask, GPIO_PIN_RESET);
}

/**
 * @brief Raise output pin(s) high
 * @param ePort
 *        GPIO port
 * @param u16PinMask
 *        Pin mask
 */
void GPIO_RaiseHigh(GPIOPort ePort, uint16_t u16PinMask)
{
    GPIO_TypeDef* phPort = _ConvertGPIOPort(ePort);
    HAL_GPIO_WritePin(phPort, u16PinMask, GPIO_PIN_SET);
}

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
 * @return System status code
 */
SystemStatus I2C_Receive(uint16_t u16DevAddress, uint16_t u16MemAddress, uint8_t* pu8RxBuffer, uint16_t u16Size)
{
    if (HAL_OK != HAL_I2C_Mem_Read_IT(
            &hi2c2,
            u16DevAddress,
            u16MemAddress,
            I2C_MEMADD_SIZE_16BIT,
            pu8RxBuffer,
            u16Size))
    {
        return SYSTEM_I2C_ERROR;
    }

    return SYSTEM_OK;
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
 * @return System status code
 */
SystemStatus I2C_Transmit(uint16_t u16DevAddress, uint16_t u16MemAddress, uint8_t* pu8TxBuffer, uint16_t u16Size)
{
    if (HAL_OK != HAL_I2C_Mem_Write_IT(
            &hi2c2,
            u16DevAddress,
            u16MemAddress,
            I2C_MEMADD_SIZE_16BIT,
            pu8TxBuffer,
            u16Size))
    {
        return SYSTEM_I2C_ERROR;
    }

    return SYSTEM_OK;
}

/**
 * @brief  Transmit an amount via SPI
 * @param  pu8TxData
 *         Pointer to data buffer
 * @param  u16Size
 *         Amount of data to be sent
 * @return System status code
 */
SystemStatus SPI_Transmit(uint8_t* pu8TxData, uint16_t u16Size)
{
    if (HAL_OK != HAL_SPI_Transmit_IT(&hspi1, pu8TxData, u16Size))
    {
        return SYSTEM_SPI_ERROR;
    }

    return SYSTEM_OK;
}

/**
 * @brief  Receive an amount of data via SPI
 * @param  pu8RxData
 *         Pointer to data buffer
 * @param  u16Size
 *         Amount of data to be sent
 * @return System status code
 */
SystemStatus SPI_Receive(uint8_t* pu8RxData, uint16_t u16Size)
{
    if (HAL_OK != HAL_SPI_Receive_IT(&hspi1, pu8RxData, u16Size))
    {
        return SYSTEM_SPI_ERROR;
    }

    return SYSTEM_OK;
}

/**
 * @brief  Transmit and Receive an amount of data via SPI
 * @param  pu8TxData
 *         Pointer to transmission data buffer
 * @param  pu8RxData
 *         Pointer to reception data buffer
 * @param  u16Size
 *         Amount of data to be sent and received
 * @return System status code
 */
SystemStatus SPI_TransmitReceive(uint8_t* pu8TxData, uint8_t* pu8RxData, uint16_t u16Size)
{
    if (HAL_OK != HAL_SPI_TransmitReceive_IT(&hspi1, pu8TxData, pu8RxData, u16Size))
    {
        return SYSTEM_SPI_ERROR;
    }

    return SYSTEM_OK;
}

static GPIO_TypeDef* _ConvertGPIOPort(GPIOPort ePort)
{
    GPIO_TypeDef* phPort = GPIOA;

    switch (ePort)
    {
        case GPIO_PORT_A:
            phPort = GPIOA;
            break;
        case GPIO_PORT_B:
            phPort = GPIOB;
            break;
        case GPIO_PORT_C:
            phPort = GPIOC;
            break;
        case GPIO_PORT_D:
            phPort = GPIOD;
            break;
    }

    return phPort;
}