#include "Keys.h"
#include "GPIO.h"

// 私有化, 避免被勿修改
static u8 states = 0x0F;

void Keys_init() {
    P0_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
		P0_MODE_IO_PU(GPIO_Pin_7);
}

void Keys_scan() {
    // KEY1 -----------------------------------------
    if(IS_KEY_DOWN(0) && KEY1 == 1) {
        // 感知抬起: 判断是否是上升沿 (上一次是低电平0, 这次是高电平1)
        //Keys_on_keyup(0);
        // 记录最后一次(上一次)的状态为抬起
        SET_KEY_UP(0);

        // P01 = 0;
    } else if(IS_KEY_UP(0)&& KEY1 == 0) {
        // 感知按下: 判断是否是下降沿 (上一次是高电平1, 这次是低电平0)
        Keys_on_keydown(0);
        // 记录最后一次(上一次)的状态为按下
        SET_KEY_DOWN(0);

    }

    // KEY2 -----------------------------------------
    if(IS_KEY_DOWN(1) && KEY2 == 1) {
        // 感知抬起: 判断是否是上升沿 (上一次是低电平0, 这次是高电平1)
        //Keys_on_keyup(1);
        // 记录最后一次(上一次)的状态
        SET_KEY_UP(1);
    } else if(IS_KEY_UP(1)&& KEY2 == 0) {
        // 感知按下: 判断是否是下降沿 (上一次是高电平1, 这次是低电平0)
        Keys_on_keydown(1);
        // 记录最后一次(上一次)的状态
        SET_KEY_DOWN(1);
    }

    // KEY3 -----------------------------------------
    if(IS_KEY_DOWN(2) && KEY3 == 1) {
        // 感知抬起: 判断是否是上升沿 (上一次是低电平0, 这次是高电平1)
        //Keys_on_keyup(2);
        // 记录最后一次(上一次)的状态
        SET_KEY_UP(2);
    } else if(IS_KEY_UP(2)&& KEY3 == 0) {
        // 感知按下: 判断是否是下降沿 (上一次是高电平1, 这次是低电平0)
        Keys_on_keydown(2);
        // 记录最后一次(上一次)的状态
        SET_KEY_DOWN(2);
    }

    // KEY4 -----------------------------------------
    if(IS_KEY_DOWN(3) && KEY4 == 1) {
        // 感知抬起: 判断是否是上升沿 (上一次是低电平0, 这次是高电平1)
        //Keys_on_keyup(3);
        // 记录最后一次(上一次)的状态
        SET_KEY_UP(3);
    } else if(IS_KEY_UP(3)&& KEY4 == 0) {
        // 感知按下: 判断是否是下降沿 (上一次是高电平1, 这次是低电平0)
        Keys_on_keydown(3);
        // 记录最后一次(上一次)的状态
        SET_KEY_DOWN(3);
    }

}

u8 pre_P07key_state = 0;
void P07_Btn(){
		if(pre_P07key_state == 0 && P07 == 1) {

        // 记录最后一次(上一次)的状态为抬起
				//Keys_on_keyup(4);	
			
        pre_P07key_state = 1;

        // P01 = 0;
    } else if(pre_P07key_state == 1 && P07 == 0) {

        // 记录最后一次(上一次)的状态为按下
				Keys_on_keydown(4);
			
        pre_P07key_state = 0;
    }
}

//extern void Keys_on_keydown(u8 key);
//extern void Keys_on_keyup(u8 key);
