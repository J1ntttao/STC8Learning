#ifndef __WS2812B_H__
#define __WS2812B_H__
#include "config.h"

#define	 SPI_0		0
#define	 SPI_1		1	
#define	 SPI_2		2
#define  SPI_3		3

#define ANS_NUM		28		//4*7 = 28盏 操作灯   ANS_NUM
#define TIP_NUM		7    //+7盏   	   指示灯	 TIP_NUM
#define MAIN_NUM (ANS_NUM + TIP_NUM)

#define POS_NUM		28		//4*7 = 28盏 位置灯	 POS_NUM
#define ACK_NUM		28    //4*7 = 28盏 校验灯	 ACK_NUM
#define OTHER_NUM (POS_NUM + ACK_NUM)

#define	MAIN_SPI_NUM		(MAIN_NUM*12)		//LED灯对应MAINSPI字节数
#define	OTHER_SPI_NUM		(OTHER_NUM*12)	//LED灯对应OTHERSPI字节数

//MAIN_NUM:					35
//4*7 = 28盏 操作灯  ANS_NUM
//+7盏   	   指示灯	 TIP_NUM
extern u8	xdata  main_led_RGB[MAIN_NUM][3];	

//OTHER_NUM:
//4*7 = 28盏 位置灯	  POS_NUM
//4*7 = 28盏 校验灯   ACK_NUM 
extern u8	xdata  other_led_RGB[OTHER_NUM][3];

extern u8	xdata  main_led_SPI[MAIN_SPI_NUM];			
extern u8	xdata  other_led_SPI[OTHER_SPI_NUM];		

enum LEDSWITCH{
		ANS = 0,
		TIP = 1,
		POS = 2,
		ACK = 3,
};

void  WS2812_initLED();

u8*   Color_select(u8 index);
void  SPI_Config(u8 SPI_io, u8 SPI_speed);

// 废弃的LightALLLED
// void  WS2812_LightALLLED(u8 SPI_io, u8 whichLed_index, u8 color_index);
void	LoadMainSPI(void);
void	LoadOtherSPI(void);

//================== 效率更高的方式 ================
void WS2812_WriteColor2Array(u8 whichLed_index, u8 whichpos, u8 color_index);
void WS2812_RefreshLEDColor(u8 SPI_io);
// ↑ 先把颜色写进颜色数组 再刷新灯带


//------------------------------------------------------------------------------
// 寄存器操作： 因为不知道WS2812用SPI发送具体用到哪些就全抄来了...
#define	Pin0		0x01	//IO引脚 Px.0
#define	Pin1		0x02	//IO引脚 Px.1
#define	Pin2		0x04	//IO引脚 Px.2
#define	Pin3		0x08	//IO引脚 Px.3
#define	Pin4		0x10	//IO引脚 Px.4
#define	Pin5		0x20	//IO引脚 Px.5
#define	Pin6		0x40	//IO引脚 Px.6
#define	Pin7		0x80	//IO引脚 Px.7
#define	PinAll		0xFF	//IO所有引脚

#define P0n_standard(bitn)			P0M1 &= ~(bitn),	P0M0 &= ~(bitn)	/* 00  */
#define P0n_push_pull(bitn)			P0M1 &= ~(bitn),	P0M0 |=  (bitn)	/* 01  */
#define P0n_pure_input(bitn)		P0M1 |=  (bitn),	P0M0 &= ~(bitn)	/* 10  */
#define P0n_open_drain(bitn)		P0M1 |=  (bitn),	P0M0 |=  (bitn)	/* 11  */

#define P1n_standard(bitn)			P1M1 &= ~(bitn),	P1M0 &= ~(bitn)
#define P1n_push_pull(bitn)			P1M1 &= ~(bitn),	P1M0 |=  (bitn)
#define P1n_pure_input(bitn)		P1M1 |=  (bitn),	P1M0 &= ~(bitn)
#define P1n_open_drain(bitn)		P1M1 |=  (bitn),	P1M0 |=  (bitn)

#define P2n_standard(bitn)			P2M1 &= ~(bitn),	P2M0 &= ~(bitn)
#define P2n_push_pull(bitn)			P2M1 &= ~(bitn),	P2M0 |=  (bitn)
#define P2n_pure_input(bitn)		P2M1 |=  (bitn),	P2M0 &= ~(bitn)
#define P2n_open_drain(bitn)		P2M1 |=  (bitn),	P2M0 |=  (bitn)

#define P3n_standard(bitn)			P3M1 &= ~(bitn),	P3M0 &= ~(bitn)
#define P3n_push_pull(bitn)			P3M1 &= ~(bitn),	P3M0 |=  (bitn)
#define P3n_pure_input(bitn)		P3M1 |=  (bitn),	P3M0 &= ~(bitn)
#define P3n_open_drain(bitn)		P3M1 |=  (bitn),	P3M0 |=  (bitn)

#define P4n_standard(bitn)			P4M1 &= ~(bitn),	P4M0 &= ~(bitn)
#define P4n_push_pull(bitn)			P4M1 &= ~(bitn),	P4M0 |=  (bitn)
#define P4n_pure_input(bitn)		P4M1 |=  (bitn),	P4M0 &= ~(bitn)
#define P4n_open_drain(bitn)		P4M1 |=  (bitn),	P4M0 |=  (bitn)

#define P5n_standard(bitn)			P5M1 &= ~(bitn),	P5M0 &= ~(bitn)
#define P5n_push_pull(bitn)			P5M1 &= ~(bitn),	P5M0 |=  (bitn)
#define P5n_pure_input(bitn)		P5M1 |=  (bitn),	P5M0 &= ~(bitn)
#define P5n_open_drain(bitn)		P5M1 |=  (bitn),	P5M0 |=  (bitn)

#define P6n_standard(bitn)			P6M1 &= ~(bitn),	P6M0 &= ~(bitn)
#define P6n_push_pull(bitn)			P6M1 &= ~(bitn),	P6M0 |=  (bitn)
#define P6n_pure_input(bitn)		P6M1 |=  (bitn),	P6M0 &= ~(bitn)
#define P6n_open_drain(bitn)		P6M1 |=  (bitn),	P6M0 |=  (bitn)

#define P7n_standard(bitn)			P7M1 &= ~(bitn),	P7M0 &= ~(bitn)
#define P7n_push_pull(bitn)			P7M1 &= ~(bitn),	P7M0 |=  (bitn)
#define P7n_pure_input(bitn)		P7M1 |=  (bitn),	P7M0 &= ~(bitn)
#define P7n_open_drain(bitn)		P7M1 |=  (bitn),	P7M0 |=  (bitn)

//sfr SPCTL   = 0x85;	SPI控制寄存器
//   7       6       5       4       3       2       1       0    	Reset Value
//	SSIG		SPEN		DORD		MSTR		CPOL		CPHA		SPR1		SPR0			0x00
#define	SSIG		1	//1: 忽略SS脚，由MSTR位决定主机还是从机		0: SS脚用于决定主从机。
#define	SPEN		1	//1: 允许SPI，								0：禁止SPI，所有SPI管脚均为普通IO
#define	DORD		0	//1：LSB先发，								0：MSB先发
#define	MSTR		1	//1：设为主机								0：设为从机
#define	CPOL		0	//1: 空闲时SCLK为高电平，					0：空闲时SCLK为低电平
#define	CPHA		1	//1: sample at the second edge,				0: sample at the first edge
#define	SPR1		0	//SPR1,SPR0   00: fosc/4,     01: fosc/8
#define	SPR0		0	//            10: fosc/16,    11: fosc/2

//sfr SPDAT  = 0xCF; //SPI Data Register                                                     0000,0000
//sfr SPSTAT  = 0xCD;	//SPI状态寄存器
//   7       6      5   4   3   2   1   0    	Reset Value
//	SPIF	WCOL	-	-	-	-	-	-
#define	SPIF	0x80		/* SPI传输完成标志。写入1清0。*/
#define	WCOL	0x40		/* SPI写冲突标志。写入1清0。  */

#endif
