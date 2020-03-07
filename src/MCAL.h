// SPDX-License-Identifier: Beerware
/**
 * @file    MCAL.h
 * @brief   Microcontroller Abstraction Layer
 * @details MCAL for STM32F1xx microcontroller
 */
#pragma once

#include <stdint.h>
#include "System.h"

/**
 * @enum  GPIOPort
 * @brief GPIO ports
 */
typedef enum
{
    GPIO_PORT_A = 0, ///< GPIO port A
    GPIO_PORT_B,     ///< GPIO port B
    GPIO_PORT_C,     ///< GPIO port C
    GPIO_PORT_D      ///< GPIO port D

} GPIOPort;

void         MCAL_DelayUS(uint16_t u16Delay);
void         GPIO_PullDown(GPIOPort ePort, uint16_t u16PinMask);
void         GPIO_RaiseHigh(GPIOPort ePort, uint16_t u16PinMask);
SystemStatus I2C_Receive(uint16_t u16DevAddress, uint16_t u16MemAddress, uint8_t* pu8RxBuffer, uint16_t u16Size);
SystemStatus I2C_Transmit(uint16_t u16DevAddress, uint16_t u16MemAddress, uint8_t* pu8TxBuffer, uint16_t u16Size);
SystemStatus SPI_Transmit(uint8_t* pu8TxData, uint16_t u16Size);
SystemStatus SPI_Receive(uint8_t* pu8RxData, uint16_t u16Size);
SystemStatus SPI_TransmitReceive(uint8_t* pu8TxData, uint8_t* pu8RxData, uint16_t u16Size);
