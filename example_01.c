#include "BeagleBone_gpio.h"

//connect a LED to the beaglebone P8_3 and a button to P9_12. 
int main()
{
	int i;
	struct gpioID LED1,BUTTON1;

	pinMode(&LED1,P8_3,"out");
	pinMode(&BUTTON1,P9_12,"in");

	for (i=0;i<100;i++)
	{
		if (digitalRead(BUTTON1)==1)
			digitalWrite(LED1,0);
		else
			digitalWrite(LED1,1);	
		delayms(500);
	}
	
	cleanup(LED1);
	cleanup(BUTTON1);
	
	return 1;
}