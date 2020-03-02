// SPDX-License-Identifier: Beerware
/**
 * @file  Animation.h
 * @brief Tamago animation handler
 */
#pragma once

#include <stdint.h>

#define Latch_Pin       GPIO_PIN_3 ///< Latch pin
#define Latch_GPIO_Port GPIOA      ///< Latch GPIO port

#define FRAME_SIZE             64  ///< Frame size in byte
#define NUM_OF_FRAMES         167  ///< Total number of frames

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
void Animation_Update(void);
