#include "mbed.h"

//InterruptIn btn1(D7);
//InterruptIn btn2(D6);
//InterruptIn btn3(D5);
//InterruptIn btn4(D4);
InterruptIn btn[4] = {D7, D6, D5, D4}
//DigitalOut led0(A0);
//DigitalOut led1(A1);
//DigitalOut led2(A2);
DigitalOut leds[3] = { A0, A1, A2 };

#define ALL_LEDS(on) leds[0] = leds[1] = leds[2] = on

enum State
{
	CODE,
	NONE,
	SECURE
};

State _state = NONE;
char code[] = { 0, 0, 0 };
char ccode[] = { 0, 0, 0 };
bool btn_on[] = { false, false, false };

void btn1_released()
{
	StateMachine(0);
}

void btn2_released()
{
	StateMachine(1);
}
void btn3_released()
{
	StateMachine(2);
}
void btn4_released()
{
	StateMachine(3);
}

void StateMachine(char button)
{
	switch (state)
	{
	case CODE:
		if (!button)
			_state = NONE;
		else
			code[button - 1] = (code[button - 1] + 1) % 10;
		break;

	case NONE:
		if (!button)
			_state = CODE;
		else if (button == 1)
			leds[0] = btn_on[0] = 1;
		else if (button == 2 && btn_on[0])
			leds[1] = btn_on[1] = 1;
		else if (button == 3 && btn_on[0] && btn_on[1])
			leds[2] = btn_on[2] = 1;
		else
		{
			_state = NONE;
			btn_on[0] = btn_on[1] = btn_on[2] = false;
			ALL_LEDS(0);
		}
		if (btn_on[0] && btn_on[1] && btn_on[2])
		{
			_state = SECURE;
			ALL_LEDS(1);
		}
			
		break;

	case SECURE:
		if (!button)
			ccode[0] = ccode[1] = ccode[2] = 0;
		else
			ccode[button - 1] = (ccode[button - 1] + 1) % 10;
		if (ccode[0] == code[0] && ccode[1] == code[1] && ccode[2] == code[2])
		{
			_state = NONE;
			ALL_LEDS(0);
		}
		break;

	default: return;
	}
	return;
}

int main()
{
	btn[0].mode(PullUp);
	btn[1].mode(PullUp);
	btn[2].mode(PullUp);
	btn[3].mode(PullUp);
	btn[0].fall(&btn1_released);
	btn[1].fall(&btn2_released);
	btn[2].fall(&btn3_released);
	btn[3].fall(&btn4_released);
	while (0 == 0);
	return 0;
}