/****************************************************************************
* Title                 :   RF Meter click HAL
* Filename              :   rf_meter_hw.h
* Author                :   MSV
* Origin Date           :   18/01/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  18/01/16         .1              MSV     Interface Created.
*
*****************************************************************************/
/**
 * @file rf_meter_hal.h
 * @brief Hal layer for MikroElektronika's RF Meter click board.
 *
 * @date 18 Jan 2016
 * @author Milos Vidojevic
 * @copyright GNU Public License
 *
 * @version .1 - Initial testing and verification
 *
 * @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    GPS Click
 *   SW:              ARM 4.5.2
 */
#ifndef RF_METER_HAL_H_
#define RF_METER_HAL_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stddef.h>
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Hal layer initialisation
 *
 * @return ( 0 - init success / 1 - init fail )
 */
int rf_meter_hal_init( void );

/**
 * @brief Read data from device through SPI port
 *
 * @param[out] reading - pointer to readed data
 *
 * @retval ( 0 - read success / 1 - read fail )
 */
int rf_meter_hal_read( uint16_t *reading );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* RF_METER_HAL_H_ */

/*** End of File **************************************************************/
