#include "WS2812B.h"

u8 xdata red_color[3]		    = {	 0,	 6,	 0};
u8 xdata orange_color[3]		= {	 2,	 4,	 0};
u8 xdata yellow_color[3]		= {	 3,	 3,	 0};
u8 xdata green_color[3]		    = {	 6,	 0,	 0};
u8 xdata cyan_color[3]			= {	 4,	 0,	 2};
u8 xdata blue_color[3]			= {	 0,	 0,  6};
u8 xdata purple_color[3]		= {	 0,	 3,	 3};

u8* Color_select(u8 index){
    static u8 xdata color_buffer[3]; // 静态缓冲区存储颜色
    
    switch(index) {
        case 0: // 红色
            color_buffer[0] = red_color[0];
            color_buffer[1] = red_color[1]; 
            color_buffer[2] = red_color[2];
            break;
        case 1: // 橙色
            color_buffer[0] = orange_color[0];
            color_buffer[1] = orange_color[1]; 
            color_buffer[2] = orange_color[2];
            break;
        case 2: // 黄色
            color_buffer[0] = yellow_color[0];
            color_buffer[1] = yellow_color[1]; 
            color_buffer[2] = yellow_color[2];
            break;
        case 3: // 绿色
            color_buffer[0] = green_color[0];
            color_buffer[1] = green_color[1]; 
            color_buffer[2] = green_color[2];
            break;
        case 4: // 青色
            color_buffer[0] = cyan_color[0];
            color_buffer[1] = cyan_color[1]; 
            color_buffer[2] = cyan_color[2];
            break;
        case 5: // 蓝色
            color_buffer[0] = blue_color[0];
            color_buffer[1] = blue_color[1]; 
            color_buffer[2] = blue_color[2];
            break;
        case 6: // 紫色
            color_buffer[0] = purple_color[0];
            color_buffer[1] = purple_color[1]; 
            color_buffer[2] = purple_color[2];
            break;
        case 7: // null
            color_buffer[0] = 0;
            color_buffer[1] = 0; 
            color_buffer[2] = 0;
            break;				
        default: // 默认红色
            color_buffer[0] = red_color[0];
            color_buffer[1] = red_color[1]; 
            color_buffer[2] = red_color[2];
            break;
    }
    return color_buffer;
}

void Delay5us(void)	//@24.000MHz
{
	unsigned char data i;

	i = 38;
	while (--i);
}

//-----------------------------------------------------------------------
void WS2812_LightALLLED(u8 SPI_io, u8 whichLed_index, u8 color_index){
    u8 *selected_color; 
    u8  xdata  *px;        // 用于清零循环的指针
    u16 i, j, k;
    //u32 crt_ms;
    
    SPI_Config(SPI_io, 1); // SPI初始化函数
    
    px = (whichLed_index == 0) ? &main_led_RGB[0][0] :
				 (whichLed_index == 1) ? &main_led_RGB[ANS_NUM][0] : 
				 (whichLed_index == 2) ? &other_led_RGB[0][0] :
				 (whichLed_index == 3) ? &other_led_RGB[POS_NUM][0] : NULL;
    
    selected_color = Color_select(color_index);
    if(selected_color == NULL) {
        selected_color = red_color; // 默认颜色
    }
    
    if(whichLed_index == 0) // ANS - 操作灯组 (0-27)
    {
				px = &main_led_RGB[0][0];
        //for(i = 0; i < ANS_NUM * 3; i++, px++) {
        //    *px = 0; //只清除ANS组的颜色
        //}
				
        for(i = 0; i < ANS_NUM; i++) {
            main_led_RGB[i][0] = selected_color[0];  // G
            main_led_RGB[i][1] = selected_color[1];  // R  
            main_led_RGB[i][2] = selected_color[2];  // B
        }
    }
    else if(whichLed_index == 1) // TIP - 指示灯组 (28-34)
    {
				px = &main_led_RGB[ANS_NUM][0]; // 从ANS_NUM开始
        for(i = 0; i < TIP_NUM * 3; i++, px++) {
            *px = 0; //只清除TIP组的颜色
        }
				
        for(i = 0; i < TIP_NUM; i++) {
            main_led_RGB[ANS_NUM + i][0] = selected_color[0]; // G
            main_led_RGB[ANS_NUM + i][1] = selected_color[1]; // R
            main_led_RGB[ANS_NUM + i][2] = selected_color[2]; // B
        }
    }
    else if(whichLed_index == 2) // POS - 位置灯组 (0-27)
    {
				px = &other_led_RGB[0][0];
        for(i = 0; i < POS_NUM * 3; i++, px++) {
            *px = 0; //只清除POS组的颜色
        }
				
        for(i = 0; i < POS_NUM; i++) {
            other_led_RGB[i][0] = selected_color[0];   // G
            other_led_RGB[i][1] = selected_color[1];   // R
            other_led_RGB[i][2] = selected_color[2];   // B
        }
    }
    else if(whichLed_index == 3) // ACK - 校验灯组 (28-53)
    {
				px = &other_led_RGB[POS_NUM][0]; 
        for(i = 0; i < ACK_NUM * 3; i++, px++) {
            *px = 0; //只清除ACK组的颜色
        }
				
        for(i = 0; i < ACK_NUM; i++) {
            other_led_RGB[POS_NUM + i][0] = selected_color[0]; // G
            other_led_RGB[POS_NUM + i][1] = selected_color[1]; // R
            other_led_RGB[POS_NUM + i][2] = selected_color[2]; // B
        }
    }
    else { 
        return; 
    }    
    
    if(whichLed_index == 0 || whichLed_index == 1)
    {
        LoadMainSPI(); // 将颜色装载到MainSPI数据
    } else {
        LoadOtherSPI(); // 将颜色装载到OtherSPI数据
    }
    

    
    k = 0;
    j = k * 12; // 每次的开始地址不同
    
    if(whichLed_index == 0 || whichLed_index == 1) {
        for(i = 0; i < MAIN_SPI_NUM; i++) {
            SPDAT = main_led_SPI[j]; // 发送一个字节
            if(++j >= MAIN_SPI_NUM) j = 0;
            while((SPSTAT & SPIF) == 0); // 等待发送完成
            SPSTAT = SPIF + WCOL; // 清0 SPIF和WCOL标志
        }
    } else if(whichLed_index == 2 || whichLed_index == 3) {
        for(i = 0; i < OTHER_SPI_NUM; i++) {
            SPDAT = other_led_SPI[j]; // 发送一个字节
            if(++j >= OTHER_SPI_NUM) j = 0;
            while((SPSTAT & SPIF) == 0); // 等待发送完成
            SPSTAT = SPIF + WCOL; // 清0 SPIF和WCOL标志
        }
    }


}
/* 
  	功能说明	 

		请先别修改程序, 直接下载"SPI.hex"测试, 下载时选择主频24MHz或输入25.6MHz.

		使用SPI-MOSI输出直接驱动WS28123基色彩灯, DMA传输。本例驱动60个灯，接成环状。本例使用P1.3-MOSI输出驱动信号。

			每个灯3个字节，分别对应绿、红、蓝则，MSB先发.
		800KHz码率, 数据0(1/4占空比): H=0.3125us  L=0.9375us, 数据1(3/4占空比): H=0.9375us  L=0.3125us, RESET>=50us.
		高电平时间要精确控制在要求的范围内, 低电平时间不需要精确控制, 大于要求的最小值并小于RES的50us即可.

		WS2812S的标准时序如下:
		TH+TL = 1.25us±150ns, RES>50us
		T0H = 0.25us±150ns = 0.10us - 0.40us
		T0L = 1.00us±150ns = 0.85us - 1.15us
		T1H = 1.00us±150ns = 0.85us - 1.15us
		T1L = 0.25us±150ns = 0.10us - 0.40us
		两个位数据之间的间隔要小于RES的50us.

		SPI方案:
		由于SPI的一个字节输出完毕后P1.3-MOSI会恢复高电平，所有输出要反相，使用MCU自带的模拟比较器做反相，P3.7-CMP+接VCC/2，P3.6-CMP-接P1.3-MOSI，P3.4-CMPO输出信号控制WS2812.

		用SPI传输, 速度3.0~3.5MHz，以3.2MHz为最佳, MSB先发, 每个字节高4位和低4位分别对应一个位数据, 0111(反相后是1000)为数据0, 0001(反相后是1110)为数据1, 有DMA就使用DMA传输, 没有DMA就直接SPI发送.
		SPI数据位       D7 D6 D5 D4    D3 D2 D1 D0
		SPI数据         0  1  1  1     0  0  0  1
		比较器反相输出  1  0  0  0     1  1  1  0
									 WS2812数据0    WS2812数据1
		SPI数据高半字节对应的WS2812数据0-->0x07, 数据1-->0x10,
		SPI数据低半字节对应的WS2812数据0-->0x07, 数据1-->0x01,
		主频25.6MHz, SPI分频8 = 3.2MHz. 最佳.
		主频24.0MHz, SPI分频8 = 3.0MHz.
		主频12.8MHz, SPI分频4 = 3.2MHz. 最佳.
		主频12.0MHz, SPI分频4 = 3.0MHz.

*/

void LoadMainSPI(){
    u8  xdata *px;
    u8  k;
    u8  dat;
    u16 i, j;
    
    for(i = 0; i < MAIN_SPI_NUM; i++) main_led_SPI[i] = 0;
    
    px = &main_led_RGB[0][0];

    for(i = 0, j = 0; i < (MAIN_NUM * 3); i++)
    {
        dat = *px;
        px++;
        for(k = 0; k < 4; k++)
        {
            if(dat & 0x80) main_led_SPI[j] = 0xE0; // 数据1
            else main_led_SPI[j] = 0x80; // 数据0
            if(dat & 0x40) main_led_SPI[j] |= 0x0E; // 数据1
            else main_led_SPI[j] |= 0x08; // 数据0
            dat <<= 2;
            j++;
        }
    }
}

void LoadOtherSPI(){
    u8  xdata *px;
    u8  k;
    u8  dat;
    u16 i, j;
    
    for(i = 0; i < OTHER_SPI_NUM; i++) other_led_SPI[i] = 0;
    
    px = &other_led_RGB[0][0];
    
    for(i = 0, j = 0; i < (OTHER_NUM * 3); i++)
    {
        dat = *px;
        px++;
        for(k = 0; k < 4; k++)
        {
            if(dat & 0x80) other_led_SPI[j] = 0xE0; // 数据1
            else other_led_SPI[j] = 0x80; // 数据0
            if(dat & 0x40) other_led_SPI[j] |= 0x0E; // 数据1
            else other_led_SPI[j] |= 0x08; // 数据0
            dat <<= 2;
            j++;
        }
    }
}
//========================================================================
// 函数: void  SPI_Config(u8 io, u8 speed)
// 描述: SPI初始化函数。								 MOSI接WS2812的DIN
// 参数: io: 切换到的IO,            SS  MOSI MISO SCLK
//                       0: 切换到 P1.2 P1.3 P1.4 P1.5
//                       1: 切换到 P2.2 P2.3 P2.4 P2.5
//                       2: 切换到 P5.4 P4.0 P4.1 P4.3
//                       3: 切换到 P3.5 P3.4 P3.3 P3.2
//       SPI_speed: SPI的速度, 0: fosc/4,  1: fosc/8,  2: fosc/16,  3: fosc/32
// 返回: none.
// 版本: VER1.0
// 日期: 2018-6-13
// 备注:
//========================================================================

void  SPI_Config(u8 SPI_io, u8 SPI_speed)
{
    // 先完全复位 SPI
    SPCTL = 0;               // 禁用 SPI
    SPDAT = 0;               // 清空数据寄存器
    SPSTAT = SPIF + WCOL;    // 清除所有标志
  Delay5us();
	
	P_SW2 |= 0x80;		//SFR enable
	SPCTL = (SSIG << 7) + (SPEN << 6) + (DORD << 5) + (MSTR << 4) + (CPOL << 3) + (CPHA << 2) + (SPI_speed & 3);	//配置SPI

	if(SPI_io == 1)
	{
		P_SW1 |=  (1<<2);		//切换到P2.2(SS) P2.3(MOSI) P2.4(MISO) P2.5(SCLK)
		P2n_standard(0x3C);		//设置为准双向口
		P24 = 0;				//MISO = 0, MOSI输出完毕保持低电平
		P2n_push_pull(Pin3);	//驱动WS2812将MOSI设置为推挽输出
	}
	else if(SPI_io == 2)
	{
		P_SW1 |=  (2<<2);		//切换到P5.4(SS) P4.0(MOSI) P4.1(MISO) P4.3(SCLK)
		P5n_standard(0x10);		//设置为准双向口
		P4n_standard(0x0B);		//设置为准双向口
		P41 = 0;				//MISO = 0, MOSI输出完毕保持低电平
		P4n_push_pull(Pin0);	//驱动WS2812将MOSI设置为推挽输出
	}
	else if(SPI_io == 3)
	{
		P_SW1 |=  (3<<2);		//切换到P3.5(SS) P3.4(MOSI) P3.3(MISO) P3.2(SCLK)
		P3n_standard(0x3C);		//设置为准双向口
		P33 = 0;				//MISO = 0, MOSI输出完毕保持低电平
		P3n_push_pull(Pin4);	//驱动WS2812将MOSI设置为推挽输出
	}
	else
	{
		P_SW1 &= ~(3<<2);		//切换到P1.2或P5.4(SS) P1.3(MOSI) P1.4(MISO) P1.5(SCLK)
		P1n_standard(0x3C);		//设置为准双向口
		P5n_standard(0x10);		//设置为准双向口
		P14 = 0;				//MISO = 0, MOSI输出完毕保持低电平
		P1n_push_pull(Pin3);	//驱动WS2812将MOSI设置为推挽输出
	}
}


void WS2812_WriteColor2Array(u8 whichLed_index, u8 whichpos, u8 color_index){
    u8 *selected_color;      
  
    selected_color = Color_select(color_index);
    if(selected_color == NULL) {
        selected_color = red_color; // 默认颜色
    }
		
    if(whichLed_index == 0) // ANS - 操作灯组 (0-27)
    {
        if(whichpos >= ANS_NUM) return; // 越界保护
        // 只设置单个灯
        main_led_RGB[whichpos][0] = selected_color[0];  // G
        main_led_RGB[whichpos][1] = selected_color[1];  // R  
        main_led_RGB[whichpos][2] = selected_color[2];  // B
    }
    else if(whichLed_index == 1) // TIP - 指示灯组 (28-34)
    {
        if(whichpos >= TIP_NUM) return;
        main_led_RGB[ANS_NUM + whichpos][0] = selected_color[0]; // G
        main_led_RGB[ANS_NUM + whichpos][1] = selected_color[1]; // R
        main_led_RGB[ANS_NUM + whichpos][2] = selected_color[2]; // B
    }
    else if(whichLed_index == 2) // POS - 位置灯组 (0-27)
    {
        if(whichpos >= POS_NUM) return;
        other_led_RGB[whichpos][0] = selected_color[0];   // G
        other_led_RGB[whichpos][1] = selected_color[1];   // R
        other_led_RGB[whichpos][2] = selected_color[2];   // B
    }
    else if(whichLed_index == 3) // ACK - 校验灯组 (28-53)
    {
        if(whichpos >= ACK_NUM) return;
        other_led_RGB[POS_NUM + whichpos][0] = selected_color[0]; // G
        other_led_RGB[POS_NUM + whichpos][1] = selected_color[1]; // R
        other_led_RGB[POS_NUM + whichpos][2] = selected_color[2]; // B
    }
    else { 
        return; 
    }    
}

void WS2812_RefreshLEDColor(u8 SPI_io){
		u16 i, j;
		//u32 crt_ms;
		SPI_Config(SPI_io, 1); 		
    if(SPI_io == 0){
        LoadMainSPI(); // 将颜色装载到MainSPI数据
    }else if(SPI_io == 1){
        LoadOtherSPI(); // 将颜色装载到OtherSPI数据
    }
    

    //crt_ms = sys_ms;
    //while(sys_ms - crt_ms < 1);
    
		j = 0;

    if(SPI_io == 0){
        for(i = 0; i < MAIN_SPI_NUM; i++) {
            SPDAT = main_led_SPI[j]; // 发送一个字节
            j++;
            while((SPSTAT & SPIF) == 0); // 等待发送完成
            SPSTAT = SPIF + WCOL; // 清0 SPIF和WCOL标志
        }
    }else if(SPI_io == 1){
        for(i = 0; i < OTHER_SPI_NUM; i++) {
            SPDAT = other_led_SPI[j]; // 发送一个字节
            j++;
            while((SPSTAT & SPIF) == 0); // 等待发送完成
            SPSTAT = SPIF + WCOL; // 清0 SPIF和WCOL标志
        }
    }
		
		//crt_ms = sys_ms;
    //while(sys_ms - crt_ms < 1);
}