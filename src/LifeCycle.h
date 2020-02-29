// SPDX-License-Identifier: Beerware
/**
 * @file  LifeCycle.h
 * @brief Tamago life cycle handler
 */
#pragma once

#include <stdint.h>

/**
 * @enum  Evolution
 * @brief Tamago evolutions
 */
typedef enum
{
    EGG = 0,       ///< Egg
    BABYTCHI,      ///< Baby, from Egg
    MARUTCHI,      ///< Child, from Babytchi
    TAMATCHI,      ///< Teen, good care from Marutchi
    KUCHITAMATCHI, ///< Teen, bad care from Marutchi
    MAMETCHI,      ///< Adult, perfect care from Tamatchi
    GINJIROTCHI,   ///< Adult, above average care from Tamatchi
    MASKUTCHI,     ///< Adult, average care from Tamatchi
    KUCHIPATCHI,   ///< Adult, below average care from Tamatchi, perfect care from Kuchitamatchi
    NYOROTCHI,     ///< Adult, bad care from Tamatchi, average care from Kuchitamatchi
    TARAKOTCHI,    ///< Adult, Horrible care from both
    OYAJITCHI,     ///< Special, no discipline until it evolves to Maskutchi, perfect care from Maskutchi
    OBAKETCHI      ///< Dead

} Evolution;

/**
 * @struct Stats
 * @brief  Pet statistics
 */
typedef struct
{
    uint8_t   u8Age;           ///< Age in days
    uint16_t  u16CareMistages; ///< Number of care mistakes
    Evolution eEvolution;      ///< Current evolution

} Stats;

int LifeCycle_Init(void);
