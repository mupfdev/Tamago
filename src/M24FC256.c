// SPDX-License-Identifier: Beerware
/**
 * @file      M24FC256.c
 * @brief     24FC256 driver
 * @details   256Kb I²C compatible 2-wire Serial EEPROM with 1MHz clock
 *            compatibility
 * @ingroup   24FC256
 * @defgroup  24FC256 24FC256 I²C compatible 2-wire Serial EEPROM
 * @remark    The driver does currently only support page-wise read and
 *            write operations.  For byte-wise operations the datasheet
 *            states as follows: When doing a write of less than 64
 *            bytes the data in the rest of the page is refreshed along
 *            with the data bytes being written.  This will force the
 *            entire page to endure a write cycle, for this reason
 *            endurance is specified per page.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#ifdef USE_M24FC256

#include <stddef.h>
#include <stdint.h>
#include "M24FC256.h"
#include "MCAL.h"

/**
 * @brief   Read data from 24FC256 EEPROM
 * @param   u16Address
 *          Address to specify where to read the data from
 * @param   pu8RxBuffer
 *          Pointer to receive buffer
 * @param   u8Pages
 *          Number of pages to read
 * @return  Error code
 * @retval   0: OK
 * @retval  -1: Error
 * @remark  The user has to ensure that the size of the buffer where he
 *          wants to store the requested EEPROM content is big enough to
 *          store the number of requested pages.  Or the CPU will crash.
 */
int M24FC256_Read(uint16_t u16Address, uint8_t *pu8RxBuffer, uint8_t u8Pages)
{
    int sRemainingBytes = u8Pages * M24FC256_PAGESIZE;
    int sMemoryAddress  = 0;

    if (NULL == pu8RxBuffer)
    {
        return -1;
    }

    I2C_WaitUntilReady(M24FC256_ADDRESS);

    while(sRemainingBytes > 0)
    {
        int nError = I2C_Receive(
            M24FC256_ADDRESS,
            u16Address  + sMemoryAddress,
            pu8RxBuffer + sMemoryAddress,
            M24FC256_PAGESIZE);

        if (0 != nError)
        {
            return nError;
        }

        I2C_WaitUntilReady(M24FC256_ADDRESS);

        sRemainingBytes -= M24FC256_PAGESIZE;
        sMemoryAddress  += M24FC256_PAGESIZE;
    }

    return 0;
}

/**
 * @brief  Write data to 24FC256 EEPROM
 * @param  u16Address
 *         Address to specify where to write the data
 * @param  pu8TxBuffer
 *         Pointer to transmit buffer
 * @param  u8Pages
 *         Number of pages to write
 * @return Error code
 * @retval  0: OK
 * @retval -1: Error
 */
int M24FC256_Write(uint16_t u16Address, uint8_t *pu8TxBuffer, uint8_t u8Pages)
{
    int sRemainingBytes = u8Pages * M24FC256_PAGESIZE;
    int sMemoryAddress  = 0;

    if (NULL == pu8TxBuffer)
    {
        return -1;
    }

    while(sRemainingBytes > 0)
    {
        int nError = I2C_Transmit(
            M24FC256_ADDRESS,
            u16Address + sMemoryAddress,
            pu8TxBuffer + sMemoryAddress,
            M24FC256_PAGESIZE);

        if (0 != nError)
        {
            return nError;
        }

        I2C_WaitUntilReady(M24FC256_ADDRESS);

        sRemainingBytes -= M24FC256_PAGESIZE;
        sMemoryAddress  += M24FC256_PAGESIZE;
    }

    return 0;
}

#endif // USE_M24FC256
