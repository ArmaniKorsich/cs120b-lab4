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

enum SM_States { SM_Start, SM_1, SM_12, SM_2, SM_21} state;

void TickFct() {

	switch(state) {
		case SM_Start:
			state = SM_1;
			break;
		case SM_1:
			if ((PINA & 0x01) == 0x01) {
				state = SM_12;
			} else {
				state = SM_1;
			}
			break;
		case SM_12:
			if ((PINA & 0x01) == 0x01) {
				state = SM_12;
			} else { //when they let it go
				state = SM_2;
			}
			break;
		case SM_2:
			if ((PINA & 0x01) == 0x01) {
				state = SM_1;
			} else {
				state = SM_2;
			} 
			break;
		case SM_21:
			if ((PINA & 0x01) == 0x01) {
				state = SM_21;
			} else {
				state = SM_1;
			}
			break;
		default:
			state = SM_Start;	
			break;

	}
	
	switch (state) {
		case SM_12:
		case SM_1:
			PORTB = ((PORTB & 0xFC) | 0x01);
			break;
		case SM_21:
		case SM_2:
			PORTB = ((PORTB & 0xFC) | 0x02);
			break;
	
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
   state = SM_Start;
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
	TickFct();
    }
    return 1;
}
