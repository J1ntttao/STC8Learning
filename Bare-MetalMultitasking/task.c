#include "task.h"
#include "App.h"

u8 task_lock_state = TASK_STATE_UNLOCK;

void Task_init(){
		Keys_init();
#if EC11
		EC11_init();
#endif
		OLED_Init();
}

Task_t task_list[] = {
// 			   state         task_cnt     task_period      callback
			{TASK_STATE_STOP,		 100,         50,       App_Keys_task},
			//{TASK_STATE_STOP,		 10,          250,      StandbyAnimationWave},
};

// 任务数量
u8 task_len = sizeof(task_list) / sizeof(task_list[0]);


// 修改全局计数值(在中断函数里1ms调用一次, 用于任务切换)
void Task_switch_handler(void){
		u8 i = 0;
    for(i = 0; i < task_len; i++) {
        Task_t* task = &task_list[i];
        
        // 如果任务是上锁状态了, 直接跳过当前循环
        if(task_lock_state == TASK_STATE_LOCK){
            continue;
        }			
        // 如果任务计数值task_cnt不是0, 减1
        if(task->task_cnt) task->task_cnt--;
        
        // 计数值为0, 切换任务为可运行状态
        if(task->task_cnt == 0){
            // 切换任务状态, 不在这里(在终端exec)运行
            task->state = TASK_STATE_RUN;
            // 重置count计数值
            task->task_cnt = task->task_period;
        }
    }
}


// 任务执行的函数
void Task_exec_handler(void){	// 每时每刻 main函数中while(1)运行

    u8 i = 0;    
    for(i = 0; i < task_len; i++){ 
				Task_t *task = &task_list[i];
			
				// 判断任务是否是RUN 可运行状态
        if(task->state == TASK_STATE_RUN){
					  // 重置任务为停止状态
						task->state = TASK_STATE_STOP; 
            // 真正执行函数任务的地方
            task->callback();
        }
    }
}
 
// 上锁任务
void Task_Lock(){
    task_lock_state = TASK_STATE_LOCK;
}

// 解锁任务
void Task_Unlock(){
    task_lock_state = TASK_STATE_UNLOCK;    
}
