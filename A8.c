#include <stdio.h>
#include <stdint.h>
#include "MKL25Z4.h"


#define MOSI (6) // Master Out Slave In
#define SCK (5) // S Clock
#define CS (3) // Chip Select
#define MASK(X) (1 << X)



void init_LED();
void init_Timer();
void DAC_init();
void DAC_write(uint16_t value);
void DAC_write_atomic(uint8_t value);
uint16_t DAC_volt_conv(uint16_t voltage);


uint8_t dummy;

int main(void) {
	DAC_init();
	while(1){
	DAC_write(0x0555);
	}
	return 0 ;
}


void DAC_init(){



	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; // PORT C Clock gate
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;  // SPI0 Clock gate

	PORTC->PCR[MOSI] |= PORT_PCR_MUX(2);	//Set Alternate for MOSI
	PORTC->PCR[SCK] |= PORT_PCR_MUX(2);		//Set Alternate for SCK
	PORTC->PCR[CS] |= PORT_PCR_MUX(1);    //Set Chip Select to GPIO

	SPI0->C1 &=~ MASK(6); //Disable SPI
	PTC->PDDR |= (1UL<<CS); // Setting Chip Select as Output
	SPI0->C1 |= 0x5C;
	SPI0->C2 |= 0x80;
	SPI0->BR |= 0X00;
	SPI0->S |= 0X00;
	SPI0->C1 |= MASK(6); //Enable SPI
	PTC->PDOR |= (1UL << CS);  // Setting initially to high

}

 void DAC_write_atomic(uint8_t value){
 	//PTC->PCOR |= (1 << CS);//set chip select to low

 	// Waiting until SPTEF is set
 	while(!(SPI0->S & SPI_S_SPTEF_MASK));
 	SPI0->D = value;

 	// Waiting until SPRF is clear
 	//(!(SPI0->S & SPI_S_SPRF_MASK));
 	while(!(SPI0->S & SPI_S_SPRF_MASK))
 	dummy = SPI0->D;

 	//PTC->PSOR |= (1 << CS);//set chip select to high

 }


 void DAC_write(uint16_t value){

 	PTC->PCOR |= (1 << CS);//set chip select to low


 	uint16_t data = 0x0FFF & value;
 	data = 0x3000 | data;// Adding command bits to data

 	uint8_t tmp = data >> 8;// storing the first 4 data bits
 	DAC_write_atomic(tmp);

 	tmp = data;// storing the last 8 bits
 	DAC_write_atomic(tmp);

 	PTC->PSOR |= (1 << CS);//set chip select to high

 }
