#ifndef BEAGLE_GPIO_H_GUARD
#define BEAGLE_GPIO_H_GUARD
 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

//The following #defines make it easier for the user to add differnt pins
#define P8_3  0
#define P8_4  1
#define P8_5  2
#define P8_11 3
#define P8_12 4
#define P8_14 5
#define P8_15 6
#define P8_16 7
#define P8_17 8
#define P8_20 9
#define P8_21 10
#define P9_12 11
 
#define DEBUG_GPIO 0

/** @brief Contains all elements which we need to pass into the beagleboard 
 * to specify which GPIO pin we want to turn ON/OFF **/ 
struct gpioID
{
	char PINNAME[10];   //eg. P8_3
	char GPIOID[10]; 	//e.g: gpio1[6] 
	int GPIONUMBER;     //e.g: 38
	char GPIOMUX[10];   //e.g: gpmc_ad6; 
};

unsigned int bitWrite(unsigned int groupOfBits, int bitVal, int bitLoc);
int bitRead(unsigned int groupOfBits, int bitLoc);

void digitalWrite(struct gpioID singlePin,unsigned int data_to_write);
void digitalWrite_multiple(struct gpioID selected_GPIOs[], int nbr_selectedPins, unsigned int data_to_write);
void write_GPIO_value(int GPIONUMBER, int value);

void pinMode_multiple(struct gpioID selected_GPIOs[],int selectedPins[], int nbr_selectedPins, const char *direction);
void pinMode(struct gpioID *singlePin,int pinID, const char *direction);

void cleanup(struct gpioID singlePin);
void cleanup_multiple(struct gpioID selected_GPIOs[], int nbr_selectedPins);

unsigned int digitalRead(struct gpioID singlePin);

void delayms(unsigned long mseconds);
void pulsePin(struct gpioID enabled_gpio[],unsigned int data_to_write,int nbr_selectedPins, int pinID, int delay);

#endif