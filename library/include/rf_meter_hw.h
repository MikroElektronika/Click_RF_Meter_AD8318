/****************************************************************************
* Title                 :   RF Meter click HW
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
 * @file rf_meter_hw.h
 * @brief Low level functions for MikroElektronika's RF Meter click board.
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

/**
 * @mainpage
 * @section General Description
 * @par
 * The AD8318 is a demodulating logarithmic amplifier, capable of accurately
 * converting an RF input signal to a corresponding decibel-scaled output
 * voltage. The AD8318 maintains accurate log conformance for signals of 1 MHz
 * to 6 GHz and provides useful operation to 8 GHz. The input range is
 * typically 60 dB (re: 50 Ω) with error less than ±1 dB.
 * The device provides unprecedented logarithmic intercept stability vs.
 * ambient temperature conditions. A 2 mV/°C slope temperature sensor output
 * is also provided for additional system monitoring. Current consumption is
 * typically 68 mA. Power consumption decreases to <1.5 mW when the device is
 * disabled.
 *
 * @section Features
 * @par
 * <ul>
 * <li> Wide bandwidth: 1 MHz to 8 GHz </li>
 * <li> High accuracy: ±1.0 dB over 55 dB range (f < 5.8 GHz) </li>
 * <li> Stability over temperature: ±0.5 dB </li>
 * <li> Pulse response time: 10 ns/12 ns (fall/rise) </li>
 * <li> Low noise measurement </li>
 * <li> Integrated temperature sensor </li>
 * <li> Small footprint LFCSP </li>
 * <li> Power-down feature: <1.5 mW at 5 V </li>
 * </ul>
 */
#ifndef RF_METER_HW_H_
#define RF_METER_HW_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include "rf_meter_hal.h"
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
 * @brief Device initialisation
 *
 * Sets default slope and intercept values, also executes initialisation of
 * HAL layer.
 *
 * @retval ( 0 - init success / 1 - init fail )
 */
int rf_meter_init( void );

/**
 * @brief Sets slope value
 *
 * Use for device calibration in order to improve signal strength
 * measurement. Default value is -0.025.
 *
 * @param[in] new slope value
 */
void rf_meter_set_slope( double slope );

/**
 * @brief Sets intercept value
 *
 * Use for device calibration in order to improve signal strength
 * measurement. Default value is 20.0.
 *
 * @param[in] new intercept value
 */
void rf_meter_set_intercept( double intercept );

/**
 * @brief Returns AD8318 voltage
 *
 * This measurement can be used for slope and intercept calculation.
 *
 * @return value in V
 */
double rf_meter_get_voltage( void );

/**
 * @brief Returns signal strength
 *
 * @return value in dBm
 */
double rf_meter_get_signal_strength( void );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* RF_METER_HW_H_ */

/*** End of File **************************************************************/
