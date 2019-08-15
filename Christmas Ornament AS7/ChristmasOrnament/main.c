/*
 * ChristmasOrnament.c
 *
 * Created: 12/11/2018 12:08:06 PM
 * Author : jantoun
 */ 

#include <avr/io.h>
#include <avr/delay.h>

unsigned char ledPattern[4] = { //Defined patterns for LEDs (1 indicates on)
	0b01010101,
	0b10101010,
	0b10011001,
	0b01100110
};

uint16_t followPattern = 0b0000000000000000;

int main(void)
{
    DDRA = 0xFF; // All Port A output
	DDRB |= (1 << 0); // PB0 output
	PORTA = 0; //Turn LEDs off on startup
	PORTB &= ~(1 << 0); //Turn LEDs off on startup
	
    while (1) 
    {
		for(int i = 0; i<9; i++) {
			followPattern = followPattern | (1 << i);
			PORTA = followPattern;
			PORTB = (followPattern >> 8);
			_delay_ms(300);
		}
		for(int j = 9; j >= 0; j--) {
			followPattern = followPattern &= ~(1 << j);
			PORTA = followPattern;
			PORTB = (followPattern >> 8);
			_delay_ms(300);
		}
		/* Cycle through patterns */
		PORTA = ledPattern[0]; //Show pattern [0]
		PORTB |= (1 << PORTB0); //Turn top LED on
		_delay_ms(1000); //Wait...
		PORTA = ledPattern[1];
		PORTB &= ~(1 << PORTB0);	
		_delay_ms(1000);
		PORTA = ledPattern[2];
		PORTB |= (1 << PORTB0);
		_delay_ms(1000);
		PORTA = ledPattern[3];
		PORTB &= ~(1 << PORTB0);
		_delay_ms(1000);	
    }
}