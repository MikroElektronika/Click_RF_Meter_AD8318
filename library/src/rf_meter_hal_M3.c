/*******************************************************************************
* Title                 :   RF Meter click HAL
* Filename              :   rf_meter_hal.c
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
 * @file rf_meter_hal.c
 * @brief This module contains the hal layer functions for MikroElektronika's
 * RF Meter Click Board.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "rf_meter_hal.h"
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
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )
static unsigned int ( *spi_read_p )( unsigned int buffer );

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )
static unsigned char ( *spi_read_p )( unsigned char dummy );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static unsigned long ( *spi_read_p )( unsigned long buffer );

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
static unsigned char ( *spi_read_p )( unsigned char dummy );
static void ( *read_bytes_spi_p )( unsigned char *buffer,
                                   unsigned int count );
#elif defined( __GNUC__ )
#define spi_read_p
#endif

#if   defined( __MIKROC_PRO_FOR_ARM__ )     || \
      defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_PIC32__ )   || \
      defined( __MIKROC_PRO_FOR_DSPIC__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )    || \
      defined( __MIKROC_PRO_FOR_FT90x__ )
extern sfr sbit RF_METER_CS;
#endif
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void cs_high()
{
#ifdef __GNUC__

#else
    RF_METER_CS = 1;
#endif
}

static void cs_low()
{
#ifdef __GNUC__

#else
    RF_METER_CS = 0;
#endif
}

int rf_meter_hal_init()
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )
    spi_read_p = SPI_Rd_Ptr;

#elif defined( __MIKROC_PRO_FOR_PIC__ )
    spi_read_p = SPI1_Read;

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
    spi_read_p = SPIM_Rd_Ptr;
    read_bytes_spi_p = SPIM_RdBytes_Ptr;

    if( spi_read_p == NULL )
        return -1;
#endif
    cs_high();

    return 0;
}

int rf_meter_hal_read( uint16_t *reading )
{
    cs_low();

#if defined( __GNUC__ )

#else
    // TODO: Add delay of 400ns
#endif
    *reading = spi_read_p( 0x00 );

    if( *reading & 0x20 )
        return -1;

    *reading &= 0x1F;
    *reading <<= 8;
    *reading |= spi_read_p( 0x00 );
    *reading >>= 1;

    cs_high();

    return 0;
}


/*************** END OF FUNCTIONS ***************************************************************************/
