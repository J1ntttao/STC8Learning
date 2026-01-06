#ifndef __APP_H__
#define __APP_H__
#include "config.h"
#include "WS2812B.h"
#include "EC11.h"
#include "task.h"
#include "Keys.h"
#include "oled.h"

// 定义状态枚举
enum DEVICESTATES{
        DeviceStandBy  = -1,
		DeviceDefault  =  0,
		DeviceLevelSW  =  1,
        DeviceLvSwitch     ,
		DeviceStart        ,
		DeviceDefeat       ,
		DeviceVictory      ,
};

// 定义关卡难度 枚举
enum LEVELSW{
		Level1 = 1,
		Level2 = 2,
		Level3 = 3,
};

extern u8 Lv1Lvsw;
extern u8 Lv2Lvsw;
extern u8 Lv3Lvsw;

extern const u8 Lv1Code[4][4];
extern const u8 Lv2Code[4][4];
extern const u8 Lv3Code[4][4];

extern u8   DeviceState;
extern char LevelSwitch;

// Gaming Needs Variables 
extern u8   g_color_array[];
extern char g_current_color;
extern u8   g_current_pos;
extern u8   g_current_line;

// Level Guess
void GuessColorLv1(u8 Lv);
void GuessColorLv2(u8 Lv);
void GuessColorLv3(u8 Lv);

// Device Change Functions
void Device_Default2LevelSW(u8 key);
void Device_LevelSW2DeviceLvSwitch(u8 key);
void Device_LvSwitch2Start(u8 key);

// Peripherals Init Functions
void WS2812_initLED();
void Lv1LEDinit(u8 Lv);
void Lv2LEDinit(u8 Lv);
void Lv3LEDinit(u8 Lv);

// Application Task Functions
void App_Keys_task();
void App_Print_1s();

void App_OLED_refresh();

#define EC11 0 // 不用旋钮EC11

#endif