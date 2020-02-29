// SPDX-License-Identifier: Beerware
/**
 * @file  Animation.h
 * @brief Tamago animation handler
 */
#pragma once

#include <stdint.h>

#define FRAME_SIZE             64 ///< Frame size in byte
#define NUM_OF_FRAMES         167 ///< Total number of frames
#define DEFAULT_RATE          500 ///< Default refresh rate in ms

#define LEN_IDLE_EGG            2 ///< Length, Egg idle animation
#define LEN_HATCH_EGG           1 ///< Length, Egg idle animation
#define LEN_IDLE_BABYTCHI      36 ///< Length, Babytchi idle animation
#define LEN_IDLE_MARUTCHI      28 ///< Length, Marutchi idle animation
#define LEN_IDLE_TAMATCHI       2 ///< Length, Tamatchi idle animation
#define LEN_IDLE_KUCHITAMATCHI 16 ///< Length, Kuchitamatchi idle animation
#define LEN_IDLE_MAMETCHI       2 ///< Length, Mametchi idle animation
#define LEN_IDLE_GINJIROTCHI   12 ///< Length, Ginjirotchi idle animation
#define LEN_IDLE_MASKUTCHI     12 ///< Length, Maskutchi idle animation
#define LEN_IDLE_KUCHIPATCHI   28 ///< Length, Kuchipatchi idle animation
#define LEN_IDLE_NYOROTCHI     16 ///< Length, Nyorotchi idle animation
#define LEN_IDLE_TARAKOTCHI     2 ///< Length, Tarakotchi idle animation
#define LEN_IDLE_OYAJITCHI      8 ///< Length, Oyajitchi idle animation
#define LEN_IDLE_OBAKETCHI      2 ///< Length, Obaketchi idle animation

/**
 * @enum  AnimIndex
 * @brief Animation indices
 */
typedef enum
{
    INDEX_IDLE_EGG = 0,       ///< Offset, Egg idle animation
    INDEX_HATCH_EGG,          ///< Offset, Babytchi idle animation
    INDEX_IDLE_BABYTCHI,      ///< Offset, Babytchi idle animation
    INDEX_IDLE_MARUTCHI,      ///< Offset, Marutchi idle animation
    INDEX_IDLE_TAMATCHI,      ///< Offset, Tamatchi idle animation
    INDEX_IDLE_KUCHITAMATCHI, ///< Offset, Kuchitamatchi idle animation
    INDEX_IDLE_MAMETCHI,      ///< Offset, Mametchi idle animation
    INDEX_IDLE_GINJIROTCHI,   ///< Offset, Ginjirotchi idle animation
    INDEX_IDLE_MASKUTCHI,     ///< Offset, Maskutchi idle animation
    INDEX_IDLE_KUCHIPATCHI,   ///< Offset, Kuchipatchi idle animation
    INDEX_IDLE_NYOROTCHI,     ///< Offset, Nyorotchi idle animation
    INDEX_IDLE_TARAKOTCHI,    ///< Offset, Tarakotchi idle animation
    INDEX_IDLE_OYAJITCHI,     ///< Offset, Oyajotchi idle animation
    INDEX_IDLE_OBAKETCHI,     ///< Offset, Obaketchi idle animation
    NUM_OF_ANIMATIONS         ///< Total number of animations

} AnimIndex;

/**
 * @enum  AnimOffset
 * @brief Animation offsets
 */
typedef enum
{
    OFFSET_IDLE_EGG           =     0, ///< Offset, Egg idle animation
    OFFSET_HATCH_EGG          =   128, ///< Offset, Babytchi idle animation
    OFFSET_IDLE_BABYTCHI      =   192, ///< Offset, Babytchi idle animation
    OFFSET_IDLE_MARUTCHI      =  2496, ///< Offset, Marutchi idle animation
    OFFSET_IDLE_TAMATCHI      =  4288, ///< Offset, Tamatchi idle animation
    OFFSET_IDLE_KUCHITAMATCHI =  4415, ///< Offset, Kuchitamatchi idle animation
    OFFSET_IDLE_MAMETCHI      =  5440, ///< Offset, Mametchi idle animation
    OFFSET_IDLE_GINJIROTCHI   =  5568, ///< Offset, Ginjirotchi idle animation
    OFFSET_IDLE_MASKUTCHI     =  6336, ///< Offset, Maskutchi idle animation
    OFFSET_IDLE_KUCHIPATCHI   =  7104, ///< Offset, Kuchipatchi idle animation
    OFFSET_IDLE_NYOROTCHI     =  8896, ///< Offset, Nyorotchi idle animation
    OFFSET_IDLE_TARAKOTCHI    =  9920, ///< Offset, Tarakotchi idle animation
    OFFSET_IDLE_OYAJITCHI     = 10048, ///< Offset, Oyajotchi idle animation
    OFFSET_IDLE_OBAKETCHI     = 10560  ///< Offset, Obaketchi idle animation

} AnimOffset;

/**
 * @struct AnimSet
 * @brief  Animation set
 */
typedef struct
{
    AnimOffset eOffset;  ///< Frame offset, animation start
    uint8_t    u8Length; ///< Animation length/number of frames
    uint16_t   u16Rate;  ///< Refresh rate in ms

} AnimSet;

int Animation_Init(void);
