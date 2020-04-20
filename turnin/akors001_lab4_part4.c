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

enum SM_States {SM_Start, SM_1, SM_2, SM_3} state;

void tickFct() {
	switch(state) {
		case SM_Start:
			if ((PINA & 0x07)== 0x04) {
				state = SM_1;
			} else {
				state = SM_Start;
			}
			break;
		case SM_1:
			if ((PINA & 0x07) == 0x04) {
				state = SM_1;
			} else if ((PINA & 0x07) == 0x00) {
				state = SM_2;
			} else {
				state = SM_Start;
			}
			break;
		case SM_2:
			if ((PINA & 0x07) == 0x00)  {
				state = SM_2;
			} else if ((PINA & 0x07) == 0x02) {
				state = SM_3;
			} else {
				state = SM_Start;
			}
			break;
		case SM_3:
			if ((PINA & 0x80) == 0x80) {
				state = SM_Start;
			} else {
				state = SM_3;
			}
			break;
		default:
			state = SM_Start;
			break;

	}
	switch(state) {
		case SM_Start:
		case SM_1:
		case SM_2:
			break;
		case SM_3:
			if ((PINA && 0x80) == 0x80) {
				PORTB = 0x00;
			}
			else if (PORTB == 0x00) {
				PORTB = 0x01;
			}
			else if (PORTB == 0x01) {
				PORTB = 0x00;
			}
			break;
		default:
			PORTB = 0x00;
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
	tickFct();
    }
    return 1;
}
