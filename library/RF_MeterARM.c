#include "rf_meter.h"
#include "resources.h"
#include <built_in.h>
#include <stdint.h>
#include <stdbool.h>

char TFT_DataPort at GPIO_PORT_32_39;
sbit TFT_RST at GPIO_PIN42_bit;
sbit TFT_RS at GPIO_PIN40_bit;
sbit TFT_CS at GPIO_PIN41_bit;
sbit TFT_RD at GPIO_PIN46_bit;
sbit TFT_WR at GPIO_PIN47_bit;
sbit TFT_BLED at GPIO_PIN58_bit;

sbit RF_CS_PIN at GPIO_PIN28_bit;
static volatile bool update_time;

static void auxiliary_code( void );
static void set_index( unsigned short index );
static void write_command( unsigned short cmd );
static void write_data( unsigned int _data );
static void tft_update( void );
static void init_timer_a( void );
static void display_init( void );
void system_init( void );

static void auxiliary_code()
{
  TFT_WR = 0;
  asm nop;
  TFT_WR = 1;
}

static void set_index( unsigned short index )
{
  TFT_RS = 0;
  asm nop;
  TFT_DataPort = index;
  asm nop; asm nop;
  auxiliary_code();
}

static void write_command( unsigned short cmd ) 
{
  TFT_RS = 1;
  asm nop;
  TFT_DataPort = cmd;
  asm nop; asm nop;
  auxiliary_code();
}

static void write_data( unsigned int _data )
{
  TFT_RS = 1;
  asm nop;
  TFT_DataPort = Hi(_data);
  asm nop; asm nop;
  auxiliary_code();
  asm nop;
  TFT_DataPort = Lo(_data);
  asm nop; asm nop;
  auxiliary_code();
}

void tft_update()
{
   char tmp_txt[20];
   static uint16_t last_frequency;
   static double last_temp;
   uint16_t frequency;
   double temp;

   TFT_Set_Font( &HandelGothic_BT21x22_Regular, CL_WHITE, FO_HORIZONTAL );
   sprinti( tmp_txt, "%d - Hz Freq", last_frequency );
   TFT_Write_Text( tmp_txt, 115, 130 );
   sprintf( tmp_txt, "%3.1f - TEMP", last_temp );
   TFT_Write_Text( tmp_txt, 110, 150 );
   TFT_Set_Font( &HandelGothic_BT21x22_Regular, CL_BLACK, FO_HORIZONTAL );
   frequency = rf_meter_get_frequency();
   sprinti( tmp_txt, "%d - Hz Freq", frequency );
   TFT_Write_Text( tmp_txt, 115, 130 );
   temp = ADC_Get_Sample( 4 );
   #define VREF 3300

   temp = ( ( VREF / 1023 ) * temp ) / 22.2222f;
   
   sprintf( tmp_txt, "%3.1f - TEMP", temp );
   TFT_Write_Text( tmp_txt, 110, 150 );
   last_frequency = frequency;
   last_temp = temp;

   update_time = false;
}

static void init_timer_a()
{
    TIMER_CONTROL_0 = 2;
    TIMER_SELECT = 0;
    TIMER_PRESC_LS = 36;
    TIMER_PRESC_MS = 244;
    TIMER_WRITE_LS = 63;
    TIMER_WRITE_MS = 6;
    TIMER_CONTROL_3 = 0;
    TIMER_CONTROL_4 |= 17;
    TIMER_CONTROL_2 |= 16;
    TIMER_INT |= 2;
    TIMER_CONTROL_1 |= 1;
}

static void display_init()
{
    TFT_Set_Active(Set_Index, Write_Command, Write_Data);
    TFT_Init_ILI9341_8bit(320, 240);
    TFT_BLED = 1;
    
    TFT_Set_Pen( CL_WHITE, 1 );
    TFT_Set_Brush( 1, CL_WHITE, 0, 0, 0, 0 );
    TFT_Set_Font( TFT_defaultFont, CL_BLACK, FO_HORIZONTAL );

    TFT_Fill_Screen( CL_WHITE );
    TFT_Set_Pen( CL_Black, 1 );
    TFT_Line( 20, 220, 300, 220 );
    TFT_LIne( 20,  46, 300,  46 );
    TFT_Set_Font( &HandelGothic_BT21x22_Regular, CL_RED, FO_HORIZONTAL );
    TFT_Write_Text( "RF Meter click", 100, 14 );
    TFT_Set_Font( &Verdana12x13_Regular, CL_BLACK, FO_HORIZONTAL );
    TFT_Write_Text( "EasyMx PRO v7 for STM32", 19, 223 );
    TFT_Set_Font( &Verdana12x13_Regular, CL_RED, FO_HORIZONTAL );
    TFT_Write_Text( "www.mikroe.com", 200, 223 );
    TFT_Set_Font( &HandelGothic_BT21x22_Regular, CL_RED, FO_HORIZONTAL );
    TFT_Write_Text( "Frequency", 110, 100 );
}

void system_init()
{
    // SPI
    SPIM1_Init_Advanced( _SPI_MASTER_CLK_RATIO_64, _SPI_CFG_PHASE_CAPTURE_RISING |
                         _SPI_CFG_POLARITY_IDLE_LOW | _SPI_CFG_SS_AUTO_DISABLE |
                         _SPI_CFG_FIFO_DISABLE, _SPI_SS_LINE_NONE );
                         
    GPIO_Digital_Output( &GPIO_PORT_24_31, _GPIO_PINMASK_4 );
    rf_meter_init();
    
    init_timer_a();
    
    display_init();
    ADC_Init();
    ADC_Set_Input_Channel( _ADC_CHANNEL_4 );
    
    GLOBAL_INTERRUPT_MASK_bit = 0;  // Enable all interrupts
}

void main() 
{
    system_init();
    
    while( 1 )
    {
        if( update_time )
           tft_update();
    }
}


void timer_interrupt() iv IVT_TIMERS_IRQ{
  update_time = true;
  
  if (TIMER_INT_A_bit){
    TIMER_INT = (TIMER_INT & 0xAA) | (1 << 0);
  }
}