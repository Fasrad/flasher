/*-------|---------|---------|---------|---------|---------|---------|---------|
flasher.c	

by chaz miller for ATMEGAxx8 set at 1MHz 

a program to flash brake lights and then leave them turned on. The idea is for
the brakelights (or just the center brake light) to flash rapidly several times 
to gain attention, then just stay on so as not to be excessively annoying.
commercial LED lamps that do this will not fit small miata and motorcycle lamp
sockets.

The program assumes you have the uC hooked up to a 'normally closed' relay
so that if the uC breaks; the brakelights work normally. The uC basically 
bypassses the brake light lamp by opening the relay to create blinkage.

This is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 or any later
version. This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

Note that this is for BRAKE LIGHTS for a CAR, something which is IMPORTANT
and could cause danger if there is a malfunction. NEVER USE THIS SOFTWARE.
******************************************************************/

#include <avr/io.h>

#define flash_delay 400  //How fast it flashes. 4 units is 1 ms
#define flash_blinks 3   //How many times it flashes

void delay(uint16_t);
void blink (uint8_t);

int main(){
    DDRB = 0xFF;

    //8 bit Timer 0 is used by delay().
    TCCR0A = 0;                //standard timer mode (page 103)
    TCCR0B = 2;                //fcpu / 1

    for (int i = 0; i<flash_blinks; i++){
	PORTB=0xFF;  
	delay(flash_delay); 
	PORTB=0;  
	delay(flash_delay); 
    }

    for(;;){  
	PORTB=0;  //do nothing else; leave brakelights on until reboot
    } //infty

}//main

void delay(uint16_t me){    //at 1MHz, each unit is 2.55us. 1ms is 4units. 
    while(me){
	while(TCNT0 < 128){}
	me--;
	while(TCNT0 > 128){}
    }
}
