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

enum SM_States {SM_Start, SM_Loop, SM_Next} state;
unsigned char cnt;
unsigned char arr[8] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x02, 0x00}; // last one is arbitrary, just so i dont overflow.

void tickFct() {
	switch(state) {
		case SM_Start:
			state = SM_Loop;
			break;
		case SM_Loop:
			if ((PINA & 0x80) == 0x80) {
				state = SM_Start;
			}
			if (cnt == 7) {
				state = SM_Next;
			}
			break;
		case SM_Next:
			state = SM_Start;
			break;
		default:
			state =  SM_Start;
			break;		
	}
	switch(state) {
		case SM_Start:
			break;
		case SM_Loop:
			if ((PINA & 0x80) == 0x80) {
				PORTB = 0x00;
				cnt = 0;
			}
			if ((PINA & 0x07) == arr[cnt]) {
				cnt = cnt + 1;
			}
			else {
				cnt = 0;
			}
			break;
		case SM_Next:
			if ((PORTB & 0x00) == 0x00) {
				PORTB = 0x01;
			} else {
				PORTB = 0x00;
			}
			cnt = 0;
			break;
		default:
			PORTB = 0x00;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
    cnt = 0; 
    state = SM_Start;
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	tickFct();
    }
    return 1;
}
