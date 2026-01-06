#include "task.h"
#include "WS2812B.h"

//MAIN_NUM:					35
//4*7 = 28盏 操作灯  ANS_NUM
//+7盏   	   指示灯	 TIP_NUM
u8	xdata  main_led_RGB[MAIN_NUM][3];	

//OTHER_NUM:
//4*7 = 28盏 位置灯
//4*7 = 28盏 校验灯
u8	xdata  other_led_RGB[OTHER_NUM][3];

u8	xdata  main_led_SPI[MAIN_SPI_NUM];			//LED灯对应SPI字节数
u8	xdata  other_led_SPI[OTHER_SPI_NUM];		//LED灯对应SPI字节数

void WS2812_initLED(){ 
    u16 i = 0;
		// 初始化全部灯
		// 初始化main_led_RGB (35个灯)
		for(i = 0; i < MAIN_NUM ; i++){
				main_led_RGB[i][0] = 0;
				main_led_RGB[i][1] = 0;
				main_led_RGB[i][2] = 0;
		}
		
		// 初始化other_led_RGB (56个灯)
		for(i = 0; i < OTHER_NUM ; i++){
				other_led_RGB[i][0] = 0;
				other_led_RGB[i][1] = 0;
				other_led_RGB[i][2] = 0;
		}    
        
		WS2812_RefreshLEDColor(0);
		WS2812_RefreshLEDColor(0);
		WS2812_RefreshLEDColor(1);
}