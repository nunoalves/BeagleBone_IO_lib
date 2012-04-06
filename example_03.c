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

	//types "yo!" to the screen
	stringToScreen("yo!",enabled_gpio);

	//go to the the second line 
	goto_ScreenLine(1,enabled_gpio);
	
	//types "how are you?"
	stringToScreen("how are you?",enabled_gpio);
	
	//wait 2 seconds and return to first line
	sleep(2);
	goto_ScreenLine(0,enabled_gpio);
	
	//and types "hello!"
	stringToScreen("hello!",enabled_gpio);

	//don't forget to terminate the screen... or you may get
    terminate_Screen(enabled_gpio,selectedPins);

	return 1;
}