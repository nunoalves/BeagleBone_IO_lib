#include "BeagleBone_gpio.h"
#include "BeagleBone_hd44780.h"

//Connect a HD44780 compatible screen to the beaglebone using the 
//follwing connections:
//P8_14 ==> DB7
//P8_12 ==> DB6
//P8_11 ==> DB5
//P8_5  ==> DB4 
//P8_4  ==> RS
//P8_3  ==> E

int main()
{
	//specifies the pins that will be used
	int selectedPins[]={P8_14,P8_12,P8_11,P8_5,P8_4,P8_3};

	struct gpioID enabled_gpio[6];

    initialize_Screen(enabled_gpio,selectedPins);	
	
	//clear screen
	clear_Screen(enabled_gpio);

	//types "hi" to the screen
	stringToScreen("hi",enabled_gpio);

	//enable blinking cursor
	enableBlinkingCursor(enabled_gpio);
	
	//types " there"
	stringToScreen(" there",enabled_gpio);

	//wait for 3 second and disable blinking cursor
	sleep(3);
	disableBlinkingCursor(enabled_gpio);
	
	
	//don't forget to terminate the screen... or you may get
    terminate_Screen(enabled_gpio,selectedPins);

	return 1;
}