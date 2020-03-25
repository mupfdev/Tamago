// SPDX-License-Identifier: Beerware
/**
 * @file      Tamago.c
 * @brief     Tamago main application handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 * @page    Schematics Schematics
 * @section SchSTM STM32F103C8xx
 * @code{.unparsed}
 *
 * Todo.
 *
 * @endcode
 * @section SchDMD Dot Matrix Display
 * @code{.unparsed}
 *
 * RGB variant:
 *
 * Todo.
 *
 * Monochrome variant:
 *
 *      +-----+
 *      |     |           OE        ---> PA2
 * OE   | . . |  A        A         ---> PA1
 * GND  | . . |  B        B         ---> PA0
 * GND  | . . |  NC       CLK       ---> PA5 (SPI1_SCK)
 * GND    . . |  CLK      SCLK      ---> PA3
 * GND    . . |  SCLK     R/[G]/[B] ---> PA8 (SPI1_MOSI)
 * GND  | . . |  R
 * GND  | . . |  [G]
 * GND  | . . |  [B]
 *      |     |
 *      +-----+
 *
 * @endcode
 */

#include "Animation.h"
#include "BMP180.h"
#include "Clock.h"
#include "DMD.h"
#include "FreeRTOS.h"
#include "LifeCycle.h"
#include "M24FC256.h"
#include "Tamago.h"
#include "cmsis_os.h"
#include "task.h"

static TaskHandle_t _hUpdateThread; ///< Update thread handle

static void _SetAnimationByStats(Stats* pstStats);
static void _UpdateThread(void* pArg);

/**
 * @brief  Initialise Tamago main application handler
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int Tamago_Init(void)
{
    int        nError  = 0;
    BaseType_t nStatus = pdPASS;

    #ifdef USE_BMP180
    nError = BMP180_Init();
    if (0 != nError)
    {
        return -1;
    }
    #endif

    Animation_Init();
    LifeCycle_Init();

    nStatus = xTaskCreate(
        _UpdateThread,
        "Update",
        configMINIMAL_STACK_SIZE,
        NULL,
        osPriorityNormal,
        &_hUpdateThread);

    if (pdPASS == nStatus)
    {
        osKernelStart();
    }
    else
    {
        return -1;
    }

    return 0;
}

/**
 * @brief Update thread
 * @param pArg: Unused
 */
static void _UpdateThread(void* pArg)
{
    Stats*   pstStats = LifeCycle_GetStats();
    uint16_t u16Cnt   = 0;

    DMD_SetBuffer(Clock_GetBufferAddr());
    //DMD_SetBuffer(Animation_GetBufferAddr());

    while (1)
    {
        _SetAnimationByStats(pstStats);

        if (500 <= u16Cnt)
        {
            // These operations are executed approx. every 500ms
            #ifdef USE_BMP180
            int8_t s8Temp = 0;
            BMP180_ReadTemperature(&s8Temp);
            Clock_SetTemperature(s8Temp);
            #endif

            Animation_Update();
            u16Cnt = 0;
        }

        Clock_Update();
        DMD_Update();

        osDelay(1);
        u16Cnt++;
    }
}

/**
 * @brief Set animation by pet statistics
 * @param pstStats
 *        Pointer to pet statistics
 */
static void _SetAnimationByStats(Stats* pstStats)
{
    switch (pstStats->eEvolution)
    {
        case EGG:
            Animation_Set(IDLE_EGG);
            break;
        case BABYTCHI:
            Animation_Set(IDLE_BABYTCHI);
            break;
        case MARUTCHI:
            Animation_Set(IDLE_MARUTCHI);
            break;
        case TAMATCHI:
            Animation_Set(IDLE_TAMATCHI);
            break;
        case KUCHITAMATCHI:
            Animation_Set(IDLE_KUCHITAMATCHI);
            break;
        case MAMETCHI:
            Animation_Set(IDLE_MAMETCHI);
            break;
        case GINJIROTCHI:
            Animation_Set(IDLE_GINJIROTCHI);
            break;
        case MASKUTCHI:
            Animation_Set(IDLE_MASKUTCHI);
            break;
        case KUCHIPATCHI:
            Animation_Set(IDLE_KUCHIPATCHI);
            break;
        case NYOROTCHI:
            Animation_Set(IDLE_NYOROTCHI);
            break;
        case TARAKOTCHI:
            Animation_Set(IDLE_TARAKOTCHI);
            break;
        case OYAJITCHI:
            Animation_Set(IDLE_OYAJITCHI);
            break;
        case OBAKETCHI:
            Animation_Set(IDLE_OBAKETCHI);
            break;
    }

    if (LifeCycle_IsFlagSet(HAS_POOPED))
    {
        Animation_ShowIcon(ICON_POO, true);
    }
    else
    {
        Animation_ShowIcon(ICON_POO, false);
    }

    if (LifeCycle_IsFlagSet(IS_SICK))
    {
        Animation_ShowIcon(ICON_SKULL, true);
    }
    else
    {
        Animation_ShowIcon(ICON_SKULL, false);
    }

    if (LifeCycle_IsFlagSet(IS_SLEEPING))
    {
        Animation_ShowIcon(ICON_SLEEP, true);
    }
    else
    {
        Animation_ShowIcon(ICON_SLEEP, false);
    }
}
