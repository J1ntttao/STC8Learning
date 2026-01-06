#include "EC11.h"
extern u32 sys_ms;

static void GPIO_config(void) {
    //准双向口
        P3_MODE_IO_PU(GPIO_Pin_6);
		P3_MODE_IO_PU(GPIO_Pin_7);
		P4_MODE_IO_PU(GPIO_Pin_7);	
}

void EC11_init(){
		GPIO_config();
}

// 编码器状态变化表
const char encoder_table[16] = {
    0, -1, 1, 0,
    1, 0, 0, -1,
    -1, 0, 0, 1,
    0, 1, -1, 0
};

// 全局计数
static int EC11_count = 0;
static u8 last_state = 0;

void EC11_Knob(){
    static u8 pin_a, pin_b;
    static u8 curr_state;
    static u8 idx; 
    char dir;

    pin_a = P37;
    pin_b = P36;

    if (pin_a == 0 && pin_b == 0) {
        curr_state = 0;
    } else if (pin_a == 0 && pin_b == 1) {
        curr_state = 1;
    } else if (pin_a == 1 && pin_b == 0) {
        curr_state = 2;
    } else if (pin_a == 1 && pin_b == 1) {
        curr_state = 3;
    }

    idx = (last_state * 4) + curr_state;  // 代替 last_state << 2
    dir = encoder_table[idx];

    if (dir != 0) {
        EC11_count += dir;
    }

    last_state = curr_state;
		//  red  orange  yellow	 green  cyan  blue  purple
		// 0    5      10 		 15     20    25    30      35
}

// 获取计数值
int EC11_GetCount(void) {
    return EC11_count;
}

u8 pre_ec11key_state = 0;

void EC11_Btn(){
		if(pre_ec11key_state == 0 && EC11_KEY == 1) {

        // 记录最后一次(上一次)的状态为抬起
				Keys_on_keydown(5);			
        pre_ec11key_state = 1;

        // P01 = 0;
    } else if(pre_ec11key_state == 1 && EC11_KEY == 0) {

        // 记录最后一次(上一次)的状态为按下
				//Keys_on_keyup(5);
        pre_ec11key_state = 0;
    }
}

void EC11_Btn_Scan()
{
		EC11_Btn();
}
