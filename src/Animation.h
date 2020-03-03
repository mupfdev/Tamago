// SPDX-License-Identifier: Beerware
/**
 * @file  Animation.h
 * @brief Tamago animation handler
 */
#pragma once

#include <stdint.h>

/**
 * @page    DMD Dot Matrix Display
 * @section DMDHowTo How to connect
 * @code{.unparsed}
 *
 *      +-----+
 *      |     |           OE¹  ---> PB5
 * OE   | . . |  A        A    ---> PA1
 * GND  | . . |  B        B    ---> PA0
 * GND  | . . |  NC       CLK  ---> PA5 (SPI1_SCK)
 * GND    . . |  CLK      SCLK ---> PA3
 * GND    . . |  SCLK     R    ---> PA8 (SPI1_MOSI)
 * GND  | . . |  R
 * GND  | . . |  NC
 * GND  | . . |  NC
 *      |     |
 *      +-----+
 *
 * ¹ Setting OE low, lights all LEDs in the selected row.
 *   Or PWM for brightness control.
 *
 * @endcode
 */

#define DMD_OE_Pin         GPIO_PIN_5 ///< DMD OE pin
#define DMD_OE_GPIO_Port   GPIOB      ///< DMD OE GPIO port
#define DMD_SCLK_Pin       GPIO_PIN_3 ///< DMD SCLK pin
#define DMD_SCLK_GPIO_Port GPIOA      ///< DMD SCLK GPIO port
#define DMD_A_Pin          GPIO_PIN_1 ///< DMD A pin
#define DMD_A_GPIO_Port    GPIOA      ///< DMD A GPIO port
#define DMD_B_Pin          GPIO_PIN_0 ///< DMD B pin
#define DMD_B_GPIO_Port    GPIOA      ///< DMD B GPIO port

#define FRAME_SIZE             64     ///< Frame size in byte
#define NUM_OF_FRAMES         167     ///< Total number of frames

/**
 * @enum  AnimID
 * @brief Animation IDs
 */
typedef enum
{
    IDLE_EGG = 0,       ///< ID, Egg idle animation
    HATCH_EGG,          ///< ID, Babytchi idle animation
    IDLE_BABYTCHI,      ///< ID, Babytchi idle animation
    IDLE_MARUTCHI,      ///< ID, Marutchi idle animation
    IDLE_TAMATCHI,      ///< ID, Tamatchi idle animation
    IDLE_KUCHITAMATCHI, ///< ID, Kuchitamatchi idle animation
    IDLE_MAMETCHI,      ///< ID, Mametchi idle animation
    IDLE_GINJIROTCHI,   ///< ID, Ginjirotchi idle animation
    IDLE_MASKUTCHI,     ///< ID, Maskutchi idle animation
    IDLE_KUCHIPATCHI,   ///< ID, Kuchipatchi idle animation
    IDLE_NYOROTCHI,     ///< ID, Nyorotchi idle animation
    IDLE_TARAKOTCHI,    ///< ID, Tarakotchi idle animation
    IDLE_OYAJITCHI,     ///< ID, Oyajotchi idle animation
    IDLE_OBAKETCHI,     ///< ID, Obaketchi idle animation
    NUM_OF_ANIMATIONS   ///< Total number of animations

} AnimID;

/**
 * @struct Animation
 * @brief  Animation
 */
typedef struct
{
    uint16_t u16Offset; ///< Frame offset in byte
    uint8_t  u8Length;  ///< Animation length/number of frames

} Animation;

int  Animation_Init(void);
void Animation_Set(AnimID eID);
void Animation_SetRefreshRate(uint16_t u16RefreshRate);
void Animation_Update(void);
