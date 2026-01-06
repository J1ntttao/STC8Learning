#include "switch.h"
#include "Exti.h"
#include "GPIO.h"
#include "UART.h"
#include "NVIC.h"
#include "Timer.h"
#include "Soft_I2C.h"
#include "App.h"
#include "task.h"

static void GPIO_config(void) {
		//I2C P32 P33 OD
		P3_MODE_OUT_OD(GPIO_Pin_2);
    P3_MODE_OUT_OD(GPIO_Pin_3);
		// 板载LED
		P5_MODE_OUT_PP(GPIO_Pin_3);
}

static void UART_config(void) {
	// >>> 记得添加 NVIC.c, UART.c, UART_Isr.c <<<
    COMx_InitDefine		COMx_InitStructure;					//结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4

  	NVIC_UART1_Init(ENABLE,Priority_3);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);		// 引脚选择, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}


static void Timer_config(void){
		TIM_InitTypeDef		TIM_InitStructure;						//结构定义
		//定时器0做16位自动重装, 中断频率为1000HZ
		TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
		TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
		TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
		TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);		//初值,
		TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
		Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
		NVIC_Timer0_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}


u32 sys_ms = 0; // 全局 时间计数
void Timer0_ISR_Handler (void) interrupt TMR0_VECTOR	//进中断时已经清除标志
{		// 1ms
		// 任务切换函数(中断里调用)
		Task_switch_handler();
		sys_ms++;
}

#if EC11    // 不用旋钮中断
void INT2_ISR_Handler (void) interrupt INT2_VECTOR		//进中断时已经清除标志
{
		EC11_Knob();// INT2 中断服务函数（P3.6）		
}

void INT3_ISR_Handler (void) interrupt INT3_VECTOR		//进中断时已经清除标志
{
		EC11_Knob();// INT3 中断服务函数（P3.7）
}
#endif

int main(){
        EAXSFR();		/* 扩展寄存器访问使能 */
		GPIO_config();
		UART_config();
		Timer_config();
		Task_init();     // 裸机多任务
    
#if EC11	// 旋钮的外部中断
    // 配置 INT2、INT3 中断
    INT2_Interrupt(1);   // 使能 INT2
    INT3_Interrupt(1);   // 使能 INT3
#endif
		EA = 1;
		printf(" UART Init Success ! \n");
		
		//灯的初始化
		WS2812_initLED();
		printf(" WS2812 Init  ! \n");

		App_OLED_refresh();
        printf(" I2C OLED Init  ! \n");
		while(1){
				// 任务执行函数(main函数while里调用)
				Task_exec_handler();
		}
}