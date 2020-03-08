// SPDX-License-Identifier: Beerware
/**
 * @file      main.c
 * @brief     Tamago, a clone of the famous digital pet from 1996
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdlib.h>
#include "System.h"
#include "Tamago.h"

/**
  * @brief  Main application, entry point.
  * @retval int
  */
int main(void)
{
    int nError = 0;

    nError = System_Init();
    if (0 != nError)
    {
        goto error;
    }

    nError = Tamago_Init();
    if (0 != nError)
    {
        goto error;
    }

    while(1);
    error:
    return EXIT_FAILURE;
}
