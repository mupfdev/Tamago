// SPDX-License-Identifier: Beerware
/**
 * @file  Tamago.h
 * @brief Tamago handler
 */
#pragma once

#include <stdint.h>

/**
 * @enum  Evolution
 * @brief Tamago evolutions
 */
typedef enum
{
    Egg = 0,
    Babytchi,
    Marutchi,
    Tamatchi,
    Kuchitamatchi,
    Mametchi,
    Ginjirotchi,
    Maskutchi,
    Kuchipatchi,
    Nyorotchi,
    Tarakotchi,
    Oyajitchi

} Evolution;

/**
 * @struct Stats
 * @brief  Pet statistics
 */
typedef struct
{
    uint8_t   u8Age;
    uint16_t  u16CareMistages;
    Evolution eEvolution;

} Stats;
