
#include <stm32l4xx_hal.h>
#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "u8g2/u8g2.h"
#include "bsp_modbus_master.h"
#include "bsp.h"

#include "display.h"


static u8g2_t u8g2;

#define header_font u8g2_font_6x12_tf
#define footer_font2 u8g2_font_6x10_tf
#define medium_font u8g2_font_6x13_tr
#define big_font u8g2_font_8x13B_tr
#define big_font2 u8g2_font_9x15B_tr
#define huge_font u8g2_font_9x18B_tn
#define huge_font2 u8g2_font_10x20_tn
#define test_font u8g2_font_inb16_mr


void Display_Init(void){
	extern uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
	  //extern uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
	  extern uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
	  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);
	  u8g2_InitDisplay(&u8g2);
	  u8g2_SetPowerSave(&u8g2, 0);

	u8g2_FirstPage(&u8g2);
	     do
	     {

	       u8g2_SetFont(&u8g2, medium_font);
	       u8g2_DrawStr(&u8g2, 0, 15, "BELT SCALE");
	       u8g2_DrawStr(&u8g2, 0, 30, "HQ PW-T1000");
	       u8g2_DrawStr(&u8g2, 0, 45, "VER 3.03");
	       //u8g2_DrawStr(&u8g2, 0, 60, "ABCDEFGHIJKLMNOPQRST");
	     } while (u8g2_NextPage(&u8g2));

}
uint16_t vars2[3];
uint16_t mdata[32];
void modbus_test(void)
{
	char display_out[20];
		float final;

	  uint32_t temp = 0;
uint8_t Error=0;

	 // bsp_rs485_enable_receive(false);
	 // bsp_rs485_enable_transmit(true);
	  if (bsp_modbus_master_read_holding_register(0x01, 0x000B, 0x0001) == 0x00)
	  {
	    mdata[0] = bsp_modbus_master_get_response_buffer(0);
	   // mdata[1] = bsp_modbus_master_get_response_buffer(1);
	   // mdata[2] = bsp_modbus_master_get_response_buffer(2);
	   // mdata[3] = bsp_modbus_master_get_response_buffer(3);
	   // mdata[4] = bsp_modbus_master_get_response_buffer(4);
	   // mdata[5] = bsp_modbus_master_get_response_buffer(5);
	   // mdata[6] = bsp_modbus_master_get_response_buffer(6);
	   // mdata[7] = bsp_modbus_master_get_response_buffer(7);
	  }
	  else
	  {
	    Error++;
	  }

	  vars2[0]=mdata[0];
	 //  vars2[1]= mdata[1];
	 //  vars2[2]=mdata[2];



	  /*
	  temp = data[1] | 0x00000000;
	  temp = data[0] | (temp << 16);
	  V1N = *(float *)&temp;



	  temp = data[5] | 0x00000000;
	  temp = data[4] | (temp << 16);
	  V3N = *(float *)&temp;

	  temp = data[7] | 0x00000000;
	  temp = data[6] | (temp << 16);
	  VAvg = *(float *)&temp;

	  sprintf(buffer, "V1N: %3.2f VAC - V2N: %3.2f VAC - V3N: %3.2f VAC - VAvg: %3.2f VAC - ResDelay: 200ms - Error: %d\r\n", V1N, V2N, V3N, VAvg, Error);
	  len = strlen(buffer);
	  HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, 100);
	  */


    	fflush(stdout);
       	sprintf(display_out,"%d",vars2[0]);

       	u8g2_ClearBuffer(&u8g2);



        u8g2_SetFont(&u8g2, huge_font2);
       	      u8g2_DrawStr(&u8g2, 10, 40, display_out);
       	   //u8g2_SetFont(&u8g2, huge_font2);
       	  	     //  u8g2_DrawStr(&u8g2, 0, 40, tot);
       	  	      // u8g2_DrawStr(&u8g2, 0, 62, tph);
       	  	      // u8g2_DrawStr(&u8g2, 70, 62, fpm);

       	  	       u8g2_SetFont(&u8g2, header_font);
       	  	     //  u8g2_DrawStr(&u8g2, 105, 40, "TONS");
       	  	     //  u8g2_DrawStr(&u8g2, 45, 62, "TPH");
       	  	     //  u8g2_DrawStr(&u8g2, 105, 62, "FPM");

       	  	    //   u8g2_DrawStr(&u8g2, 0, 40, "");
       	  	      // u8g2_DrawStr(&u8g2, 0, 37, "3 TOTAL 3");
       	  	      // u8g2_DrawStr(&u8g2, 0, 49, "4 TOTAL 4");
       	  	       u8g2_DrawHLine(&u8g2, 0, 16, 128);

       	  	       //u8g2_DrawHLine(&u8g2, 0, 51, 128);
       	  	       // u8g2_SetFont(&u8g2, header_font);
       	  	        // u8g2_DrawStr(&u8g2, 10, 63, "** LOAD CELL ERROR **");
       	  	         u8g2_DrawStr(&u8g2, 0, 12, "14:35  12/22/22  V3.03");





       	   u8g2_SendBuffer(&u8g2);

}

void Display_Home_S1(char *tot,char *tph, char *fpm){

	u8g2_ClearDisplay(&u8g2);
	u8g2_FirstPage(&u8g2);
	     do
	     {
	      // u8g2_SetFont(&u8g2, u8g2_font_7x13_tf );
	    	 //u8g2_SetFont(&u8g2, u8g2_font_6x13_tf);
	    	 u8g2_SetFont(&u8g2, huge_font2);
	       u8g2_DrawStr(&u8g2, 0, 40, tot);
	       u8g2_DrawStr(&u8g2, 0, 62, tph);
	       u8g2_DrawStr(&u8g2, 70, 62, fpm);

	       u8g2_SetFont(&u8g2, header_font);
	       u8g2_DrawStr(&u8g2, 105, 40, "TONS");
	       u8g2_DrawStr(&u8g2, 45, 62, "TPH");
	       u8g2_DrawStr(&u8g2, 105, 62, "FPM");

	    //   u8g2_DrawStr(&u8g2, 0, 40, "");
	      // u8g2_DrawStr(&u8g2, 0, 37, "3 TOTAL 3");
	      // u8g2_DrawStr(&u8g2, 0, 49, "4 TOTAL 4");
	       u8g2_DrawHLine(&u8g2, 0, 16, 128);

	       //u8g2_DrawHLine(&u8g2, 0, 51, 128);
	       // u8g2_SetFont(&u8g2, header_font);
	        // u8g2_DrawStr(&u8g2, 10, 63, "** LOAD CELL ERROR **");
	         u8g2_DrawStr(&u8g2, 0, 12, "14:35  12/22/22  V3.03");
	       // u8g2_SetFont(&u8g2,u8g2_font_siji_t_6x10);
	       //u8g2_DrawGlyph(&u8g2,35, 64, 0xe061);

	     } while (u8g2_NextPage(&u8g2));

}



void Display_Cal_S10(void){

	u8g2_ClearDisplay(&u8g2);
	    u8g2_FirstPage(&u8g2);
	     do
	     {
    	 u8g2_SetFont(&u8g2, medium_font);
	       u8g2_DrawStr(&u8g2, 0, 13, "1  BELT LENGTH CALIBRATION");
	       u8g2_DrawStr(&u8g2, 0, 26, "2  LOAD CELL CAL");
	       u8g2_DrawStr(&u8g2, 0, 39, "3  MATERIAL TEST");
	       u8g2_DrawStr(&u8g2, 0, 52, "4  TEST WEIGHT CAL");
	       u8g2_DrawHLine(&u8g2, 0, 54, 128);
	        u8g2_SetFont(&u8g2, u8g2_font_5x8_mr);
	          	 u8g2_DrawStr(&u8g2, 8, 63, "PRESS   TO SCROLL MENU");
	        u8g2_SetFont(&u8g2,u8g2_font_siji_t_6x10);
	       u8g2_DrawGlyph(&u8g2,35, 64, 0xe061);


	     } while (u8g2_NextPage(&u8g2));
}

void Display_Total_S3(void){

	u8g2_ClearDisplay(&u8g2);
	u8g2_FirstPage(&u8g2);
	     do
	     {
	      // u8g2_SetFont(&u8g2, u8g2_font_7x13_tf );
	    	 //u8g2_SetFont(&u8g2, u8g2_font_6x13_tf);
	    	 u8g2_SetFont(&u8g2, u8g2_font_6x12_tr);
	       u8g2_DrawStr(&u8g2, 0, 13, "1 TOTAL 1");
	       u8g2_DrawStr(&u8g2, 0, 25, "2 TOTAL 2");
	       u8g2_DrawStr(&u8g2, 0, 37, "3 TOTAL 3");
	       u8g2_DrawStr(&u8g2, 0, 49, "4 TOTAL 4");
	       u8g2_DrawHLine(&u8g2, 0, 53, 128);
	        u8g2_SetFont(&u8g2, u8g2_font_5x8_mr);
	         u8g2_DrawStr(&u8g2, 8, 63, "PRESS   TO SCROLL MENU");
	        u8g2_SetFont(&u8g2,u8g2_font_siji_t_6x10);
	       u8g2_DrawGlyph(&u8g2,35, 64, 0xe061);

	     } while (u8g2_NextPage(&u8g2));

}

//*****   footer with left right arrow and page #
	    	     	// u8g2_DrawHLine(&u8g2, 0, 53, 128);
	    	     	// u8g2_SetFont(&u8g2, u8g2_font_5x8_mr);
	    	     	  //   	 u8g2_DrawStr(&u8g2, 35, 63, "PAGE 10 / 17");
	    	     	 // u8g2_SetFont(&u8g2,u8g2_font_siji_t_6x10);

	    	     	// u8g2_DrawGlyph(&u8g2,3, 64, 0xe063);
	    	 		// u8g2_DrawGlyph(&u8g2,110, 64, 0xe062);
	    	 //********** end footer

