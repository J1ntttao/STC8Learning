#ifndef __TASKS_H__
#define __TASKS_H__

#include "Config.h"

#define  TASK_STATE_UNLOCK         0 // 任务解锁
#define  TASK_STATE_LOCK     			 1 // 任务锁定

#define  TASK_STATE_STOP        0 // 任务停止
#define  TASK_STATE_RUN         1 // 任务运行


// 定义函数指针类型
typedef void (*Task_cb)(void);

// 定义结构体
typedef struct {
		u8 state;
	
    u32 task_cnt;       // 任务的计数值(动态修改)
    
    u32 task_period;    // 即多少ms执行一次(固定)
    
//    void (*callback)(void); // 任务函数的指针变量
    Task_cb callback;    // 任务函数的指针变量
	
} 	Task_t;

void Task_init();

// 任务切换函数(中断里调用)
void Task_switch_handler(void);

// 任务执行函数(main函数while里调用)
void Task_exec_handler(void);

// 上锁任务
void Task_Lock();

// 解锁任务
void Task_Unlock();

#endif