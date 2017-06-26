#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */


#define LED1  PTBD_PTBD4
#define LED2  PTBD_PTBD5
#define LED3  PTBD_PTBD6
#define LED4  PTBD_PTBD7

#define L1 	32
#define L2 	96
#define L3 	160
#define L4 	224

void Init_ports(void);
void ADCcfg(void);
unsigned int valorADC(unsigned char canal);
void indicador_leds(unsigned char valor);
unsigned char conversion;

void main(void) {
	EnableInterrupts;
	Init_ports();
	ADCcfg();



	for(;;) {
		__RESET_WATCHDOG();	
		indicador_leds(0);
		conversion = (unsigned char)(valorADC(6));
		if (conversion > L4){
			indicador_leds(4);
		}else if(conversion > L3){
			indicador_leds(3);
		}else if(conversion > L2){
			indicador_leds(2);
		}else if(conversion > L1){
			indicador_leds(1);
		}

	} 

}


void Init_ports(void){
	PTBD = 0;
	PTBDD_PTBDD4 = 1;    // led1
	PTBDD_PTBDD5 = 1;    // led2
	PTBDD_PTBDD6 = 1;    // led3
	PTBDD_PTBDD7 = 1;    // led4
}

void ADCcfg(void){
	ADCCFG = 0b01100000;
	APCTL1 = 0b01000000;
}


unsigned int valorADC(unsigned char canal){
	ADCSC1 = 0x20 | (0x1F & canal);
	while(!ADCSC1_COCO);
	(void)ADCR;
	while(!ADCSC1_COCO);
	ADCSC1 = 0x1F;
	return ADCR;
}


void indicador_leds(unsigned char valor){
	switch(valor){
	case 0:
		LED1 = 0;
		LED2 = 0;
		LED3 = 0;
		LED4 = 0;
		break;
	case 1:
		LED1 = 1;
		LED2 = 0;
		LED3 = 0;
		LED4 = 0;
		break;
	case 2:
		LED1 = 1;
		LED2 = 1;
		LED3 = 0;
		LED4 = 0;
		break;
	case 3:
		LED1 = 1;
		LED2 = 1;
		LED3 = 1;
		LED4 = 0;
		break;
	case 4:
		LED1 = 1;
		LED2 = 1;
		LED3 = 1;
		LED4 = 1;
		break;
	}

}
