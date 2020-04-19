/*	Author: akors001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_States { SM_Start, inc, dec, incpause, decpause} state;

void TickFct() {

	switch(state) {
		case SM_Start:
			state = SM_Start;
			if ((PINA & 0x03) == 0x01) {
				state = inc;
			} else if ((PINA & 0x03) == 0x02) {
				state = dec;
			} else if ((PINA & 0x03) == 0x03 {
				PORTC = 0x00;
			}
			break;
		case incpause:
			if ((PINA & 0x03) == 0x03) {
				PORTC = 0x00;
				state = SM_Start;
			} else if ((PINA & 0x01) == 0x01) {
				state = incpause;
			} else {
				state = SM_Start;
			}
			break;
		case decpause:
			if ((PINA & 0x03) == 0x03) {
				PORTC = 0x00;
				state = SM_Start;
			} else if ((PINA & 0x03) == 0x02) {
				state = decpause;
			} else { //when they let it go
				state = SM_Start;
			}
			break;
		case inc:
			if (PORTC < 0x09) {
				PORTC = PORTC + 1;
			}
			state = incpause;
			break;
		case dec:
			if (PORTC >  0x00) {
				PORTC = PORTC - 1;
			}
			state = decpause;
			break;
		default:
			PORTC = 0x07;
			state = SM_Start;	
			break;

	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
   state = SM_Start;
   DDRA = 0x00; PORTA = 0xFF;
   DDRC = 0xFF; PORTC = 0x00;

   PORTC = 0x07;
    /* Insert your solution below */
    while (1) {
	TickFct();
    }
    return 1;
}
