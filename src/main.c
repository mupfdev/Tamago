// SPDX-License-Identifier: Beerware
/**
 * @file      main.c
 * @brief     Tamago, a clone of the famous digital pet from 1996
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include <stdint.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "System.h"
#include "Tamago.h"
#include "cmsis_os.h"
#include "task.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    if (SYSTEM_OK != System_Init())
    {
        return EXIT_FAILURE;
    }

    if (! Tamago_Init())
    {
        return EXIT_FAILURE;
    }
    else
    {
        osKernelStart();
    }

    while(1);
    return EXIT_SUCCESS;
}
