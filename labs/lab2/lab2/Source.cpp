#include "mbed.h"

DigitalOut led(LED1);
DigitalIn button(USER_BUTTON);

int main()
{
	int freq = 5;
	bool f = false;
	while (1)
	{
		led = 1;
		wait(1 / (f ? freq : freq * 2));
		led = 0;
		if (button) f = !f;
	}
	return 1;
}