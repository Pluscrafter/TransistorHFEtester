/*
 * TransistorHFEtester.cpp
 *
 * Created: 27.11.2018 22:33:31
 * Author : Pluscrafter
 */ 


#include <avr/io.h>

#ifndef  F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include <stdint.h>

const double res[2] = {1000,100000};
const double Ucc = 5.04;
const double UDiode = 0.8;
const double I1 = 0.000025075;
const double U1 = 0.025074627;
const double U2 = 2.532575;
double U3,I2,I3;
uint16_t hfe;

int main(void)
{
	
	TCCR0A |= (1<<WGM00)|(1<<WGM01)|(1<<COM0B1);
	TCCR0B |= (1<<CS00);
    ADMUX = (0<<REFS0)|(0<<REFS1)|(1<<MUX0);
    ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	

	OCR0B = 0x40;
	DDRB |= (1 << DDB1);
	while(ADCSRA & (1<<ADSC)){
	}
	
    while (1) 
    {
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC)){
		}*
		OCR0A = 0x40;
		OCR0B = 0x40;
		U3 = (Ucc/1024)*ADC; 
		I2 = (U2-U3)/1000;
		I3 = (U3-UDiode)/100000;
		hfe = I2/I3;
		
		
			
		//_delay_ms(1000);
    }
	
	return 0;
}

