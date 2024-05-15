/*
 * ADC.c
 *
 *  Created on: Jun 20, 2023
 *      Author: hp
 */
#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */
#include "std_types.h"
#include "ADC.h"
#include <util/delay.h>

void init_ADC(void)
{
	ADMUX |= (1<<REFS0);								//Voltage reference from AVCC
	ADCSRA |= (1<<ADEN);								//Turn on ADC
	ADCSRA |= (1<<ADSC);								//Start conversion from analog to digital
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));		//16Mhz/128 = 125Khz which is the ADC reference clock
}

uint16_t ADC_Read(uint8_t channel)
{
	unsigned int value;
	ADCSRA |= (1<<ADIF);		// Clear ADIF flag
	_delay_ms(50);
	ADMUX &= 0xF0;				//Clear the previous channel
	ADMUX |= channel;
	ADCSRA |= (1<<ADSC);		//Start new conversion
	while(ADIF==0);				//ADIF is interrupt flag. When it equals 1, it means that the conversion from analog to digital has finished
	value=ADCL|ADCH<<8;		//Shift left ADCH by 8bits then combine it with ADCL with the OR operator "|"
	return value;

}
