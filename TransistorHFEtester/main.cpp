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

volatile int DT = 0, CL = 0;

const double Ucc = 5.04;
const double UDiode = 0.8;
const double I1 = 0.000025075;
const double U1 = 0.025074627;
const double U2 = 5.015;
double U3,I2,I3;
float hfe;

ISR(TIMER1_OVF_vect){
	static int rem;
	if(CL == 0) rem = DT;
	if (rem >= 256){
		OCR1A = 255;
		rem -=256;
	}else{
		OCR1A = rem;
		rem = 0;
	}
	CL = (CL + 1) &0x0F;
}
void analogWrite(int value){
	cli();
	DT = value;
	sei();
}

int main(void){
	
	TCCR1 |= (1<<PWM1A)|(1<<COM1A1)|(1<<CS10);
	TIMSK |= (1<<TOIE1);
	

	
    ADMUX = (0<<REFS0)|(0<<REFS1)|(1<<MUX0);
    ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	
	
	DDRB |= (1 << DDB1);
	while(ADCSRA & (1<<ADSC)){
	}
	
    while (1) 
    {
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC)){
		}
		
		
		U3 = (Ucc/1024)*ADC; 
		I2 = (U2-U3)/1000;
		I3 = (U3-UDiode)/100000;
		hfe = I2/I3;
		
		analogWrite((4096/1000)*hfe);
			
		//_delay_ms(1000);
    }
	
	return 0;
}

