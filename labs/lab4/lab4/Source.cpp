#include "mbed.h"

PortOut portA(PortA, 0xF3);

//TODO: edit mask
int mask[] = { 0x00, 0x01, 0x13, 0x33, 0x73, 0xf3,
				0x73, 0x33, 0x13, 0x03, 0x01, 0x00 };

int main()
{
	int i = 0;
	while (1)
	{
		portA = mask[i];
		i++;
		if (i >= sizeof(mask) / sizeof(mask[0]))
			i = 0;
		wait(0.1);
	}
	return 0;
}