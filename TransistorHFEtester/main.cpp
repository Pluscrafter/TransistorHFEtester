/*
 * TransistorHFEtester.cpp
 *
 * Created: 27.11.2018 22:33:31
 * Author : Pluscrafter
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef  F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include <stdint.h>

const float res[2] = {1000,100000};
const float Ucc = 5.1;
const float UDiode = 0.8;
const float I1 = Ucc/res[0]+res[1]+res[1];
const float U1 = I1*res[0];
const float U2 = I1*(res[1]+res[2]);
float U3,I2,I3;
uint16_t hfe;

int main(void)
{
	TCCR0B = (1<<WGM00)|(1<<WGM01)|(1<<COM0B1);
	
    ADMUX = (0<<REFS0)|(0<<REFS1)|(1<<MUX0);
    ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	
	sei();
	
	DDRB = (1<<PB1)|(0<<PB2);
	PORTB = (0<<PB1)|(1<<PB2);
	
	
	while(ADCSRA & (1<<ADSC)){
	}
	
    while (1) 
    {
		ADCSRB |= (1<<ADSC);
		while(ADCSRB & (1<<ADSC)){
		}
		
		U3 = (Ucc/1024)*ADC; 
		I2 = (U2-U3)/res[0];
		I3 = (U3-UDiode)/res[1];
		hfe = I2/I3;
		
		OCR0B = 100;
			
		_delay_ms(1000);
    }
	
	return 0;
}

