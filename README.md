![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

![RF_Meter_click](http://www.mikroe.com/img/news/2016/01/rf_meter_click_banner_news.png)

---

###General Description
RF Meter click is a radio frequency power measurement device covering a frequency span from 1 MHz to 8 GHz over a 60 dB range (approximately). It enables monitoring and measuring frequency levels to ensure proper functioning and leak detection. An external antenna acquires the signal, which is then processed by the AD8318 logarithmic detector. The resulting voltage is fed into an MCP3201 ADC. For communicating with the target board MCU, the mikroBUS™ SPI interface is used (CS, SCK, MISO pins), with additional TEMP OUT pin.

---

###Example

#### Configuration
* MCU:             STM32F107VC
* Dev.Board:       EasyMx Pro v7
* Oscillator:      72 Mhz internal
* Ext. Modules:    SHT Click
* SW:              MikroC PRO for ARM 4.7.4

```
#include "rf_meter_hw.h"
#include "resources.h"

// TFT module connections
unsigned int TFT_DataPort at GPIOE_ODR;
sbit TFT_RST at GPIOE_ODR.B8;
sbit TFT_RS at GPIOE_ODR.B12;
sbit TFT_CS at GPIOE_ODR.B15;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_WR at GPIOE_ODR.B11;
sbit TFT_BLED at GPIOE_ODR.B9;

// RF METER chip select pin
sbit RF_METER_CS at GPIOD_ODR.B13;

// Example variables
int track;
int last_track;
double result;
char tmp_txt[15];

void system_init()
{
    SPI3_Init_Advanced( _SPI_FPCLK_DIV64, _SPI_MASTER | _SPI_8_BIT |
                        _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION |
                        _SPI_MSB_FIRST | _SPI_SS_DISABLE | _SPI_SSM_ENABLE | 
                        _SPI_SSI_1, &_GPIO_MODULE_SPI3_PC10_11_12 );

    GPIO_Digital_Output( &GPIOD_BASE, _GPIO_PINMASK_13 );
    Delay_ms( 500 );
    
    track = 0;
    last_track = 0;
}

void display_init()
{
    TFT_Init_ILI9341_8bit( 320, 240 );
    TFT_BLED = 1;
    TFT_Set_Pen( CL_WHITE, 1 );
    TFT_Set_Brush( 1,CL_WHITE,0,0,0,0 );
    TFT_Set_Font( TFT_defaultFont, CL_BLACK, FO_HORIZONTAL );
    TFT_Fill_Screen( CL_WHITE );
    TFT_Set_Pen( CL_BLACK, 1 );
    TFT_Line(  20,  46, 300,  46 );
    TFT_Line(  20,  70, 300,  70 );
    TFT_Line(  20, 196, 300, 196 );;
    TFT_Line(  20, 220, 300, 220 );
    TFT_Set_Pen( CL_WHITE, 1 );
    TFT_Set_Font( &HandelGothic_BT21x22_Regular, CL_RED, FO_HORIZONTAL );
    TFT_Write_Text( "RF Meter click", 95, 14 );
    TFT_Set_Font( &Tahoma15x16_Bold, CL_BLUE, FO_HORIZONTAL );
    TFT_Write_Text( "AD8318", 130, 50 );
    TFT_Set_Font( &Verdana12x13_Regular, CL_BLACK, FO_HORIZONTAL );
    TFT_Write_Text("EasyMx PRO v7 for STM32", 19, 223);
    TFT_Set_Font( &Verdana12x13_Regular, CL_RED, FO_HORIZONTAL );
    TFT_Write_Text( "www.mikroe.com", 200, 223 );
    TFT_Set_Font( &Tahoma15x16_Bold, CL_BLACK, FO_HORIZONTAL );
    TFT_Write_Text( "Current signal strength", 30, 200 );
    TFT_Set_Font( &HandelGothic_BT21x22_Regular, CL_BLACK, FO_HORIZONTAL );
    TFT_Image( 114, 100, signal_lo_bmp , 2 );
}

void main() 
{
    system_init();
    display_init();
    
    // Device initialisation
    // Must be done before usage
    rf_meter_init();
    Delay_ms( 200 );
    
    while( 1 )
    {
        // Signal strength measurement
        result = rf_meter_get_signal_strength();
        
        // Change the track value only in case of the signal strenght chaged 
        // scope to avoid the display refreshing on every single loop
        if ( result < -50.0 )
            track = 0;
        else if ( ( result < -35.0 ) && ( result >= -50.0 ) )
            track = 1;
        else if ( ( result < -20.0 ) && ( result >= -35 ) )
            track = 2;
        else
            track = 3;

        // If scope changed delete old picture and draw a new one
        if ( track != last_track )
        {
            TFT_Rectangle( 112, 98, 196, 166 );
            
            switch( track )
            {
                case 0 :
                    TFT_Image( 114, 100, signal_lo_bmp , 2 );
                    break;
                case 1 :
                    TFT_Image( 114, 100, signal_lo_m_bmp , 2 );
                    break;
                case 2 :
                    TFT_Image( 114, 100, signal_hi_m_bmp , 2 );
                    break;
                case 3 :
                    TFT_Image( 114, 100, signal_hi_bmp , 2 );
                    break;
            }
            // Replace old scope value with the new one
            last_track = track;
        }
        
        // Display signal strength
        sprintf( tmp_txt, "%5.1f    dBm", result );
        TFT_Rectangle( 198, 200, 288, 218 );
        TFT_Set_Font( &Tahoma15x16_Bold, CL_BLUE, FO_HORIZONTAL );
        TFT_Write_Text( tmp_txt, 205, 200 );
        Delay_ms( 500 );
    }
}
```
