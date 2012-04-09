#include "BeagleBone_gpio.h"

/** 
 * @brief Writes a bit into a particular location in an unsigned int variable (32 bits)
 * @param groupOfBits Some data resides in these 32 bits 
 * @param bitVal The bitVal is wither a 1 or a 0
 * @param bitLoc Where in the groupOfBits, the value of bitVal will be written. 
 * Keep in mind that the bitLoc values ranges 0 to 31
 * @return Returns the updated groupOfBits
 **/ 
unsigned int bitWrite(unsigned int groupOfBits, int bitVal, int bitLoc)
{
    if (bitVal==1) groupOfBits |= 1 << bitLoc;
    else groupOfBits &= ~(1 << bitLoc);     
    return(groupOfBits);
}

/** 
 * @brief Returns the bit value of a particular location in an unsigned int variable (32 bits)
 * @param groupOfBits Some data resides in these 32 bits 
 * @param bitLoc Where in the groupOfBits, the value of bitVal will be written 
 * @return Retuns an integer with the bit value (1 or 0) that resides in bitLoc
 **/ 
int bitRead(unsigned int groupOfBits, int bitLoc)
{
    unsigned int bit = groupOfBits & (1 << bitLoc);
    if (bit!=0) bit=1;
    
    return(bit);
}
 
void pulsePin(struct gpioID enabled_gpio[],unsigned int data_to_write,int nbr_selectedPins, int pinID, int delay)
{
	data_to_write=bitWrite(data_to_write,1,pinID);
	digitalWrite_multiple(enabled_gpio,nbr_selectedPins,data_to_write); 
	if (delay>=0) delayms(delay);

	data_to_write=bitWrite(data_to_write,0,pinID);
	digitalWrite_multiple(enabled_gpio,nbr_selectedPins,data_to_write);
	if (delay>=0) delayms(delay);
}

void write_GPIO_value(int GPIONUMBER, int value)
{
	if (DEBUG_GPIO) 
	{
		printf("[start]... void write_GPIO_value(int GPIONUMBER, int value) >> ");
		printf ("%d, %d\n",GPIONUMBER,value);
	}
	
	char export_filename[50]; 
	FILE *f = NULL; 
    
	sprintf(export_filename, "/sys/class/gpio/gpio%d/value",GPIONUMBER); 
	f = fopen(export_filename,"w");
	assert(f!=NULL);    
	fprintf(f , "%d",value); 
	pclose(f); 
}
	

void digitalWrite_multiple(struct gpioID selected_GPIOs[], int nbr_selectedPins, unsigned int data_to_write)
{
	int i;
	//cycles every userdefined pin, and inializes its contents in the 
	//selected_GPIOs[] array.
	for (i=0; i<nbr_selectedPins;i++)
	{
		write_GPIO_value(selected_GPIOs[i].GPIONUMBER,bitRead(data_to_write,i));
	}	

}

void pinMode_multiple(struct gpioID selected_GPIOs[],int selectedPins[], int nbr_selectedPins, const char *direction)
{	
	int i;
	//You are not allowed to use more than 32 active pins. This is not a 
	//beagleboard limitation, but a limitation of this code.
	assert (nbr_selectedPins<=32);
	
	//cycles every userdefined pin, and inializes its contents in the 
	//selected_GPIOs[] array.
	for (i=0 ; i<nbr_selectedPins ; i++)
	{
		pinMode(&selected_GPIOs[i],selectedPins[i],direction);
	}	
}

void pinMode(struct gpioID *singlePin,int pinID, const char *direction)
{
	char export_filename[50]; 
    
    FILE *f = NULL; 
	
	switch (pinID)
	{
		case P8_3:
			strcpy(singlePin->PINNAME, "P8_3");
			strcpy(singlePin->GPIOID, "gpio1[6]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad6");
			singlePin->GPIONUMBER=38;
			break;
                
		case P8_4:
			strcpy(singlePin->PINNAME, "P8_4");
			strcpy(singlePin->GPIOID, "gpio1[7]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad7");
			singlePin->GPIONUMBER=39;
			break;
            
		case P8_5:
			strcpy(singlePin->PINNAME, "P8_5");
			strcpy(singlePin->GPIOID, "gpio1[2]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad2");
			singlePin->GPIONUMBER=34;
			break;
        
        case P8_11:
			strcpy(singlePin->PINNAME, "P8_11");
			strcpy(singlePin->GPIOID, "gpio1[13]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad13");
			singlePin->GPIONUMBER=45;
			break;
                
		case P8_12:
			strcpy(singlePin->PINNAME, "P8_12");
			strcpy(singlePin->GPIOID, "gpio1[12]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad12");
			singlePin->GPIONUMBER=44;
			break;

		case P8_14:
			strcpy(singlePin->PINNAME, "P8_14");
			strcpy(singlePin->GPIOID, "gpio0[26]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad10");
			singlePin->GPIONUMBER=26;
			break;
           
   	  	case P8_15:
			strcpy(singlePin->PINNAME, "P8_15");
			strcpy(singlePin->GPIOID, "gpio1[15]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad15");
			singlePin->GPIONUMBER=47;
			break;
 
 		case P8_16:
			strcpy(singlePin->PINNAME, "P8_16");
			strcpy(singlePin->GPIOID, "gpio1[14]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad14");
			singlePin->GPIONUMBER=46;
			break;

 		case P8_17:	
 			strcpy(singlePin->PINNAME, "P8_17");
			strcpy(singlePin->GPIOID, "gpio0[27]");
			strcpy(singlePin->GPIOMUX, "gpmc_ad11");
			singlePin->GPIONUMBER=27;
			break;

 		case P8_20:
			strcpy(singlePin->PINNAME, "P8_20");
			strcpy(singlePin->GPIOID, "gpio1[31]");
			strcpy(singlePin->GPIOMUX, "gpmc_csn2");
			singlePin->GPIONUMBER=63;
			break;

 		case P8_21:
			strcpy(singlePin->PINNAME, "P8_21");
			strcpy(singlePin->GPIOID, "gpio1[30]");
			strcpy(singlePin->GPIOMUX, "gpmc_csn1");
			singlePin->GPIONUMBER=62;
			break;
           
        case P9_12:
			strcpy(singlePin->PINNAME, "P9_12");
			strcpy(singlePin->GPIOID, "gpio1[28]");
			strcpy(singlePin->GPIOMUX, "gpmc_ben1");
			singlePin->GPIONUMBER=60;
			break;       

		default:
			//This statement should never be reached... since
			//the program won't even compile if the user 
			//specified a bad pin specification.
			break;
		}
    
    	if (strncmp(direction,"out",3) == 0)
		{
			//set mux to mode 7 
	 		sprintf(export_filename, "/sys/kernel/debug/omap_mux/%s", singlePin->GPIOMUX); 
			f = fopen(export_filename,"w");
        
			if (f == NULL)
			{
        	 	printf( "\nERROR: There was a problem opening /sys/kernel/debug/omap_mux/%s\n", singlePin->GPIOMUX); 
				printf("\n%s\t%s\t%s\t%d\n\n", singlePin->PINNAME, singlePin->GPIOID, singlePin->GPIOMUX, singlePin->GPIONUMBER);
            
				assert(f!=NULL);
        	} 
        	fprintf(f, "7"); 
        	pclose(f); 
		}   
		
		//export the pin
		f = fopen("/sys/class/gpio/export","w");
        
		if (f == NULL)
		{
         	printf( "\nERROR: There was a problem opening /sys/kernel/debug/omap_mux/%s\n", singlePin->GPIOMUX); 
			printf("\n%s\t%s\t%s\t%d\n\n", singlePin->PINNAME,singlePin->GPIOID,singlePin->GPIOMUX,singlePin->GPIONUMBER);
            
			assert(f!=NULL);
        } 
        fprintf(f, "%d",singlePin->GPIONUMBER); 
        pclose(f); 
        
		if (strncmp(direction,"out",3) == 0)
		{
	        //set the appropriate io direction (out)
		 	sprintf(export_filename, "/sys/class/gpio/gpio%d/direction", singlePin->GPIONUMBER); 

			f = fopen(export_filename,"w");        
			if (f == NULL)
			{
         		printf( "\nERROR: There was a problem opening /sys/class/gpio/gpio%d/direction\n", singlePin->GPIONUMBER); 
				printf("\n%s\t%s\t%s\t%d\n\n",singlePin->PINNAME,singlePin->GPIOID,singlePin->GPIOMUX,singlePin->GPIONUMBER);
           	 
				assert(f!=NULL);
        	} 
        	fprintf(f , "out" ); 
        	pclose(f); 

        	write_GPIO_value(singlePin->GPIONUMBER,0);
        }
        else
        {
        	//right now, only P9_12 can be an input port...
        	assert(singlePin->GPIONUMBER==60);
        }
        
        if (DEBUG_GPIO) 
		{
			printf("\n");
			printf("PINNAME\tGPIOID\t\tGPIOMUX\t\tGPIONBR\n");
			printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
			printf("%s\t%s\t%s\t%d\n",
					singlePin->PINNAME,
					singlePin->GPIOID,
					singlePin->GPIOMUX,
					singlePin->GPIONUMBER);
			printf("\n");
		}
		
}
 
void digitalWrite(struct gpioID singlePin,unsigned int data_to_write)
{
	write_GPIO_value(singlePin.GPIONUMBER,data_to_write);
}

void cleanup(struct gpioID singlePin)
{
	FILE *f = NULL; 

	//unexport the pin
	f = fopen("/sys/class/gpio/unexport","w");
	assert(f!=NULL);   
    fprintf(f, "%d",singlePin.GPIONUMBER); 
	pclose(f);         
}

void cleanup_multiple(struct gpioID selected_GPIOs[], int nbr_selectedPins)
{	
	int i;
	//You are not allowed to use more than 32 active pins. This is not a 
	//beagleboard limitation, but a limitation of this code.
	assert (nbr_selectedPins<=32);
	
	//cycles every userdefined pin, and inializes its contents in the 
	//selected_GPIOs[] array.
	for (i=0; i<nbr_selectedPins;i++)
	{
		cleanup(selected_GPIOs[i]);
	}	
}


//Right now only P9_3 is configured. If we leave the pin unconnected, it
//will read a 1 by default (pull up network). If we make a connection to ground
//then the pin will be 0.
unsigned int digitalRead(struct gpioID singlePin)
{
	char export_filename[128];
   	char line [ 128 ];
   	unsigned int x;
	
	if (DEBUG_GPIO) 
	{
		printf("[start]... unsigned int digitalRead() >> ");
		printf ("singlePin.GPIONUMBEr=%d\n",singlePin.GPIONUMBER);
	}

	sprintf(export_filename, "/sys/class/gpio/gpio%d/value", singlePin.GPIONUMBER); 
   	FILE *file = fopen (export_filename, "r" );
   	if ( file != NULL )
   	{
     	fgets ( line, sizeof line, file );   	  
     	fclose ( file );
   	}
   	x=(int)line[0];
   	return(x-48);
}

void delayms(unsigned long mseconds)
{
	usleep(mseconds*1000);
}

