#ifndef __KEYS_H__
#define __KEYS_H__

#include "Config.h"

#define KEY1    P03
#define KEY2    P04
#define KEY3    P05
#define KEY4    P06

#define UP         1
#define DOWN       0

//last_key3_state
//last_key_states[2]

                       //  0   1   2   3
//u8 last_key_states[] = {UP, UP, UP, UP};

// 0 0 0 0 - 1 1 1 1
//extern u8 states;  // 声明

// [判断] 指定位置是否是 按下0
// 0b 0 0 0 0 - 1 0 1 1
//&0b 0 0 0 0 - 0 1 0 0 判断指定位置是否是0, 按下
// 0b 0 0 0 0 - 0 0 0 0 == 0
#define IS_KEY_DOWN(k)  ((states >> k) & 0x01) == DOWN    // 按下 (states & (1 << k)) == 0

// [判断] 指定位置是否是 抬起1
// 0b 0 0 0 0 - 1 0 1 1
//&0b 0 0 0 0 - 0 0 1 0 判断指定位置是否是1, 抬起
// 0b 0 0 0 0 - 0 0 1 0 != 0
#define IS_KEY_UP(k)    ((states >> k) & 0x01) == UP      // 抬起 (states & (1 << k)) != 0

// [设置] 指定位置为 按下0
//   0b 0 0 0 0 - 1 0 1 1
//&= 0b 1 1 1 1 - 0 1 1 1
//&=~0b 0 0 0 0 - 1 0 0 0   将指定位设置为0, 1 << k
//   0b 0 0 0 0 - 0 0 1 1
#define SET_KEY_DOWN(k) states &= ~(1L << k)    // 设置为按下0
// 0 0 0 0 - 0 0 0 0 | 0 0 0 0 - 0 0 0 1
// 1 0 0 0 - 0 0 0 0 | 0 0 0 0 - 0 0 0 0

// 0 0 0 0 - 0 0 0 0 | 0 0 0 0 - 0 0 0 0 | 0 0 0 0 - 0 0 0 0 | 0 0 0 0 - 0 0 0 1

// [设置] 指定位置为 抬起1
//   0b 0 0 0 0 - 1 0 1 1
//|= 0b 0 0 0 0   0 1 0 0  将指定位设置为1, 1 << k
//   0b 0 0 0 0 - 1 1 1 1
#define SET_KEY_UP(k)   states |= (1L << k)     // 设置为抬起1

// ---------------------------二进制位操作
// 设置k位为1: states |=  (1 << k)
// 设置k位为0: states &= ~(1 << k)
// 判断k位是否为1: 
//    (states >> k ) & 0x01
//    (states & (1 << k)) != 0
// ---------------------------二进制位操作

void Keys_init();
void Keys_scan();
void P07_Btn();

extern void Keys_on_keydown(u8 key);
//extern void Keys_on_keyup(u8 key);


#endif