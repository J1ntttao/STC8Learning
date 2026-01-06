#ifndef __EC11_H__
#define __EC11_H__
#include "config.h"
#include "App.h"
#include "GPIO.h"

#define 	EC11_KEY	 P47

void EC11_init();

void EC11_Btn_Scan();
void EC11_Knob();
int  EC11_GetCount(void);

#endif