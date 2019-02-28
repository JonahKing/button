


#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



#define GPIO_PIN_KEY1	16
#define GPIO_PIN_KEY2   4
#define GPIO_PIN_KEY3   0
#define GPIO_PIN_KEY4   35
#define GPIO_PIN_KEY5   34




#define BUTTON_FILTER_TIME    1
#define DOUBLE_CLICK_INTERVAL  15      
#define BUTTON_LONG_TIME      100      



typedef struct _BUTTON_
{
	uint8_t (*IsKeyDownFunc)(void); 
	struct
	{
		unsigned char double_clcik_support:1;
		unsigned char long_clcik_support:1;
		unsigned char fliter_time;  
		unsigned int  long_time;   
		unsigned int  interval_time; 
	}configure;
	
	
	uint8_t Count;       
	uint16_t LongCount;  
	uint8_t double_clcik_interval_time;
	
	uint8_t single_click_state;  
	uint8_t double_click_state; 
	uint8_t final_return;   
	
	
	uint16_t ID;
	
}BUTTON_T;

enum
{
	KEY_STATE_IDLE = 0,
	KEY_STATE_SHORT_PRESS_START,
	KEY_STATE_SHORT_PRESSING,
	
	KEY_STATE_LONG_PRESSING,
	KEY_STATE_LONG_FORCE_RELEASE,
	KEY_STATE_LONG_WAITING,
	
	KEY_STATE_DOUBLE_START,
};

enum
{
	N_KEY= 0,   // no click
	SINGLE_CLICK = 10,     // single click
	DOUBLE_CLICK,     // double click
	LONG_CLICK,    // long press
};


#define KEY_FIFO_SIZE 20

typedef struct
{
  uint8_t Buf[KEY_FIFO_SIZE];
  uint8_t Read;
  uint8_t Write;
}KEY_FIFO_T;



void Init_Button(void);
void PutKey(uint8_t _KeyCode);
uint8_t GetKey(void);

uint8_t ReadButton(BUTTON_T *_pBtn);

extern BUTTON_T s_key1;
extern BUTTON_T s_key2;
extern BUTTON_T s_key3;
extern BUTTON_T s_key4;
extern BUTTON_T s_key5;

extern void Init_Button(void);
#endif

