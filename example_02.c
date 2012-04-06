#include "BeagleBone_gpio.h"


//Connect 10 LEDs to the folowing beaglebone pins:
//P8_20,P8_17,P8_16,P8_15,P8_14,P8_12,P8_11,P8_5,P8_4,P8_3
//This example will turn ON/OFF several of the LEDs at the same time,
//using a bitwise operation.
int main()
{
	int pinID[]={P8_20,P8_17,P8_16,P8_15,P8_14,P8_12,P8_11,P8_5,P8_4,P8_3};

	int nbr_selectedPins=sizeof(pinID)/sizeof(*pinID);
	struct gpioID selectedPins[nbr_selectedPins]; 
	pinMode_multiple(selectedPins,pinID,nbr_selectedPins,"out");
	
	unsigned int data_to_write;
	
	//in the array pinID[] P8_20 is on position 0 while P8_3 is on position 9.
	//to just turn ON P8_20 and P8_3, write the decimal value 513, which
	//is the binary equivalent of this pins P8_20 and P8_3 (2^0 + 2^9)  
	data_to_write=513;
	digitalWrite_multiple(selectedPins,nbr_selectedPins,data_to_write);
	delayms(2000);
	
	//turning ON P8_20, P8_15 and P8_5 (2^0 + 2^3 + 2^7 = 137)
	data_to_write=137;
	digitalWrite_multiple(selectedPins,nbr_selectedPins,data_to_write);
	delayms(2000);

	//turn ON pin P8_17 (2^1 = 2)  
	data_to_write=2;
	digitalWrite_multiple(selectedPins,nbr_selectedPins,data_to_write);
	delayms(2000);

	data_to_write=0;
	//pulse pin P8_4 twice with 1 second delay
 	pulsePin(selectedPins,data_to_write,nbr_selectedPins,8,1000);
 	pulsePin(selectedPins,data_to_write,nbr_selectedPins,8,1000);

	cleanup_multiple(selectedPins,nbr_selectedPins);
	
	return 1;
}