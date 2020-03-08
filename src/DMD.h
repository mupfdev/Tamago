// SPDX-License-Identifier: Beerware
/**
 * @file  DMD.h
 * @brief Dot Matrix Display driver
 */
#pragma once

#include <stdint.h>
#include "MCAL.h"

#ifndef DMD_OE_Pin
    #define DMD_OE_Pin    GPIO_PIN_2  ///< DMD OE pin
#endif
#ifndef DMD_SCLK_Pin
    #define DMD_SCLK_Pin  GPIO_PIN_3  ///< DMD SCLK pin
#endif
#ifndef DMD_A_Pin
    #define DMD_A_Pin     GPIO_PIN_1  ///< DMD A pin
#endif
#ifndef DMD_B_Pin
    #define DMD_B_Pin     GPIO_PIN_0  ///< DMD B pin
#endif
#ifndef DMD_GPIO_Port
    #define DMD_GPIO_Port GPIO_PORT_A ///< DMD GPIO port
#endif

/**
 * @enum  DMDRows
 * @brief Dot Matrix Display rows
 */
typedef enum
{
    DMD_ROWS_1_5_9_13 = 0, ///< DMD rows 1, 5, 9 and 13
    DMD_ROWS_2_6_10_14,    ///< DMD rows 2, 6, 10 and 14
    DMD_ROWS_3_7_11_15,    ///< DMD rows 3, 7, 11 and 15
    DMD_ROWS_4_8_12_16     ///< DMD rows 4, 8, 12 and 16

} DMDRows;

int  DMD_Init(void);
void DMD_Latch(void);
void DMD_LightRows(DMDRows eRows);
void DMD_OE_RowsOff(void);
void DMD_OE_RowsOn(void);
void DMD_SetBuffer(uint8_t* pucBuffer);
