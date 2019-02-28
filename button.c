
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "button.h"

BUTTON_T s_key1;
BUTTON_T s_key2;
BUTTON_T s_key3;
BUTTON_T s_key4;
BUTTON_T s_key5;




static KEY_FIFO_T s_key; 

static void InitButtonVar(void);
static uint8_t DetectSIngleClickButton(BUTTON_T *p_button);
uint8_t ReadButton(BUTTON_T *p_button);

uint8_t IsKeyDownKey1(void)
{
	return(1 != (gpio_get_level(GPIO_PIN_KEY1)));
}

static uint8_t IsKeyDownKey2(void)
{
	return(1 != (gpio_get_level(GPIO_PIN_KEY2)));

}
static uint8_t IsKeyDownKey3(void)
{
	return(1 != (gpio_get_level(GPIO_PIN_KEY3)));

}
static uint8_t IsKeyDownKey4(void)
{
	return(1 != (gpio_get_level(GPIO_PIN_KEY4)));

}
static uint8_t IsKeyDownKey5(void)
{
	return(1 != (gpio_get_level(GPIO_PIN_KEY5)));
}


void Init_Button()
{
	InitButtonVar(); 
}

void PutKey(uint8_t _KeyCode)
{
	s_key.Buf[s_key.Write] = _KeyCode;

	if (++s_key.Write >= KEY_FIFO_SIZE)
	{
		s_key.Write = 0;
	}
}

uint8_t GetKey(void)
{
	uint8_t ret;

	if (s_key.Read == s_key.Write)
	{
		return N_KEY;
	}
	else
	{
		ret = s_key.Buf[s_key.Read];

		if (++s_key.Read >= KEY_FIFO_SIZE)
		{
			s_key.Read = 0;
		}
		return ret;
	}
}


void InitButtonVar(void)
{

	s_key.Read = 0;
	s_key.Write = 0;

	
	s_key1.ID = 1;
	
	s_key1.IsKeyDownFunc = IsKeyDownKey1;
	
	s_key1.configure.fliter_time = BUTTON_FILTER_TIME; 
	s_key1.configure.long_time = BUTTON_LONG_TIME; 
	s_key1.configure.interval_time = DOUBLE_CLICK_INTERVAL; 
	s_key1.configure.double_clcik_support = 0;
	s_key1.configure.long_clcik_support = 1;
	
	s_key1.Count = 0;
	s_key1.LongCount = 0;
	
	s_key1.final_return = N_KEY;
	s_key1.double_clcik_interval_time = 0; 
	s_key1.single_click_state = 0;
	s_key1.double_click_state = 0;


	s_key2.ID = 2;
	s_key2.IsKeyDownFunc = IsKeyDownKey2; 
	
	s_key2.configure.fliter_time = BUTTON_FILTER_TIME; 
	s_key2.configure.long_time = BUTTON_LONG_TIME; 
	s_key2.configure.interval_time = DOUBLE_CLICK_INTERVAL; 
	s_key2.configure.double_clcik_support = 0;
	s_key2.configure.long_clcik_support = 0;
	
	
	
	s_key2.Count = 0; 
	s_key2.LongCount = 0; 
	
	s_key2.final_return = N_KEY;
	s_key2.double_clcik_interval_time = 0; 
	s_key2.single_click_state = 0;
	s_key2.double_click_state = 0;


	s_key3.ID = 3;
	s_key3.IsKeyDownFunc = IsKeyDownKey3; 
	s_key3.configure.fliter_time = BUTTON_FILTER_TIME; 
	s_key3.configure.long_time = BUTTON_LONG_TIME;
	s_key3.configure.interval_time = DOUBLE_CLICK_INTERVAL; 
	s_key3.configure.double_clcik_support = 0;
	s_key3.configure.long_clcik_support = 0;
	s_key3.Count = 0; 
	s_key3.LongCount = 0; 
	
	s_key3.final_return = N_KEY;
	s_key3.double_clcik_interval_time = 0; 
	s_key3.single_click_state = 0;
	s_key3.double_click_state = 0;


	s_key4.ID = 4;
	s_key4.IsKeyDownFunc = IsKeyDownKey4; 
	s_key4.configure.fliter_time = BUTTON_FILTER_TIME; 
	s_key4.configure.long_time = BUTTON_LONG_TIME; 
	s_key4.Count = 0;
	s_key4.LongCount = 0;
	s_key4.configure.interval_time = DOUBLE_CLICK_INTERVAL; 
	s_key4.configure.double_clcik_support = 0;
	s_key4.configure.long_clcik_support = 0;
	s_key4.final_return = N_KEY;
	s_key4.double_clcik_interval_time = 0; 
	s_key4.single_click_state = 0;
	s_key4.double_click_state = 0;

	
	s_key5.ID = 5;
	s_key5.IsKeyDownFunc = IsKeyDownKey5; 
	s_key5.configure.fliter_time = BUTTON_FILTER_TIME; 
	s_key5.configure.long_time = BUTTON_LONG_TIME; 
	s_key5.Count = 0; 
	s_key5.LongCount = 0; 
	s_key5.configure.interval_time = DOUBLE_CLICK_INTERVAL;
	s_key5.configure.double_clcik_support = 0;
	s_key5.configure.long_clcik_support = 0;
	s_key5.final_return = N_KEY;
	s_key5.double_clcik_interval_time = 0; 
	s_key5.single_click_state = 0;
	s_key5.double_click_state = 0;

}

static uint8_t DetectSIngleClickButton(BUTTON_T* p_button)
{

	unsigned char temp = N_KEY;

	switch (p_button->single_click_state)
	{
		case KEY_STATE_IDLE:
			if(1 == p_button->IsKeyDownFunc())
			{
				p_button->Count = 0;
				p_button->single_click_state = KEY_STATE_SHORT_PRESS_START;
			}
		break;
		case KEY_STATE_SHORT_PRESS_START:
			if(1 == p_button->IsKeyDownFunc())
			{
				p_button->Count++;
				p_button->LongCount++;
				if (p_button->Count >= p_button->configure.fliter_time)
				{
					p_button->single_click_state = KEY_STATE_SHORT_PRESSING;
				}
			}
			else
			{
				p_button->single_click_state = KEY_STATE_IDLE;
			}
			break;

		case KEY_STATE_SHORT_PRESSING:
			if (p_button->IsKeyDownFunc() == 0)
			{
					temp = SINGLE_CLICK;
					p_button->single_click_state = KEY_STATE_IDLE;
			}
			else
			{
				if(1 == p_button->configure.long_clcik_support)
				{
					p_button->LongCount++;
					if((p_button->LongCount >= p_button->configure.long_time))
					{
						p_button->single_click_state = KEY_STATE_LONG_PRESSING;
					}
				}
			}
			break;
		case KEY_STATE_LONG_PRESSING:
			p_button->single_click_state = KEY_STATE_LONG_FORCE_RELEASE;
			p_button->final_return = LONG_CLICK;
			PutKey(p_button->ID|LONG_CLICK);
			break;
		case KEY_STATE_LONG_FORCE_RELEASE:
			if (p_button->IsKeyDownFunc() == 0)
			{
				p_button->LongCount = 0;
				p_button->single_click_state = KEY_STATE_IDLE;
			}
			break;
		default:
			p_button->single_click_state = KEY_STATE_IDLE;
			break;
	}
	return temp;
}

void DetectDoubleClickButton(BUTTON_T *p_button,unsigned char click_state)
{
	if(1 == p_button->configure.double_clcik_support)
	{
		switch(p_button->double_click_state)
		{
			case KEY_STATE_IDLE:
				if(SINGLE_CLICK == click_state)
				{
					p_button->double_click_state = KEY_STATE_DOUBLE_START;
				}
				break;
			case KEY_STATE_DOUBLE_START:
				if (click_state == SINGLE_CLICK)
				{
					p_button->final_return = DOUBLE_CLICK;
					PutKey(p_button->ID|DOUBLE_CLICK);
					p_button->double_click_state = KEY_STATE_IDLE;
				}
				else
				{
					p_button->double_clcik_interval_time++;
					if (p_button->double_clcik_interval_time >= p_button->configure.interval_time)
					{
						p_button->double_clcik_interval_time = 0;
						p_button->final_return = SINGLE_CLICK;
						PutKey(p_button->ID|SINGLE_CLICK);
						p_button->double_click_state = KEY_STATE_IDLE;
					}
				}
				break;
			default:
				p_button->double_click_state = KEY_STATE_IDLE;
				break;
		}
	}
	else
	{
		if(SINGLE_CLICK == click_state)
		{
			p_button->final_return = SINGLE_CLICK;
		}
	}
	//return p_button->final_return;
}

uint8_t ReadButton(BUTTON_T *p_button)
{
	unsigned char temp;
	
	p_button->final_return = N_KEY;
	
	temp= DetectSIngleClickButton(p_button);
	
	DetectDoubleClickButton(p_button,temp);
	
	return p_button->final_return;
}


void example(void)
{
//	ReadButton(&s_key4);			
//	ReadButton(&s_key5);		
}

