//proof of concept
#include <math.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL //*16MHz*

//    DDRC |= 1; //should be boarduino analog pin 0

int main () {

    uint8_t pulse_width=1;
    uint8_t space_width=1;

    TCCR0A = 0;                //fast pwm mode (page 103)
    TCCR0B = 2;                //scaler 2 (7.84 kHz) (page 105)
    TCCR1A = 0;                //16 bit Timer 1: main program timer 
    TCCR1B |= (3);         //F_CPU/64
    OCR0A = 128;             //gently lock stepper rotation 
    OCR0B = 128;
    OCR2A = 128;
    OCR2B = 128;

    //PWM timer configs
    TCCR0A = 0b10100011;     //fastPWM;  p.103 in datasheet
    TCCR2A = 0b10100011;     //fastPWM;  p.153
    TCCR0B = 2;              //F_CPU/8;  p.105  (7.84 kHz)
    TCCR2B = 2;              //F_CPU/8;  p.157
    OCR0A = 128;             //gently lock stepper rotation 
    //startup blinkenled

    DDRC = 0xFF;
    PORTC = 0xFF;
    DDRB = 0xFF;
    PORTB = 0xFF;


} //main

/*
    while(1){

	PORTC = 0;
	PORTB = 0;

	for(int i=0; i<100; i++){
	    _delay_ms(space_width); //max delay is 15ms at 16MHz so have to loop	
	}

	PORTC = 0xFF;
	PORTB = 0xFF;
	_delay_ms(pulse_width);
    }
}
8*/
