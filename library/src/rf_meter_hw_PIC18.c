/******************************************************************************
* Title                 :   RF Meter click HW
* Filename              :   rf_meter_hw.c
* Author                :   MSV
* Origin Date           :   18/01/2016
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  18/01/16    XXXXXXXXXXX         MSV      Module Created.
*
*******************************************************************************/
/**
 * @file rf_meter_hw.c
 * @brief This module contains the low level functions for MikroElektronika's
 * RF Meter click board.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "rf_meter_hw.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static double temperature_compensation = 1;
static double _vref;
static double _slope;
static double _intercept;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
int rf_meter_init()
{
    if( rf_meter_hal_init() )
        return -1;

    _vref = 2.5;
    _slope = -0.025;
    _intercept = 20.0;

    return 0;
}

void rf_meter_set_slope( double slope )
{
    _slope = slope;
}

void rf_meter_set_intercept( double intercept )
{
    _intercept = intercept;
}

double rf_meter_get_voltage()
{
    double raw_reading;
    uint16_t reading;

    rf_meter_hal_read( &reading );
    raw_reading = ( double )( reading * _vref / 4096 );

    return raw_reading;
}

double rf_meter_get_signal_strength()
{
    double signal_strength;
    double raw_voltage;

    raw_voltage = rf_meter_get_voltage();

    if ( raw_voltage > 2.0 )
        signal_strength = ( 2.0 / _slope ) + _intercept;

    else if ( raw_voltage < 0.5 )
        signal_strength = ( 0.5 / _slope ) + _intercept;

    else
        signal_strength = ( raw_voltage / _slope ) + _intercept;

    return signal_strength;
}

/*************** END OF FUNCTIONS ******************************************/
