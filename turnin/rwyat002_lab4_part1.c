/*	Author: rwyat002
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




enum States { START, PB0ON, PB1ON,PB0TRANS, PB1TRANS } state;

unsigned char ucOutput;

void Tick()
{
  switch(state) {   // Transitions
     case START:  // Initial transition
	state = PB0ON;
        break;

     case PB0ON:
	if(PINA == 0x01)
		state = PB0TRANS;
	else
		state = PB0ON;
        break;

     case PB1ON:
	if(PINA == 0x01)
		state = PB1TRANS;
	else
		state = PB1ON;
        break;
      case PB0TRANS:
	if(PINA == 0x00)
		state = PB1ON;
	else
		state = PB0TRANS;
	break;
      case PB1TRANS:
	if(PINA == 0x00)
		state = PB0ON;
	else
		state = PB1TRANS;
	break;

     default:
        state = START;
        break;
  } // Transitions

  switch(state) {   // State actions
	case PB0ON:
		PORTB = 0x01;
        break;

	case PB1ON:
		PORTB = 0x02;
        break;
	
	case PB0TRANS:
		PORTB = 0x01;
	break;
	
	case PB1TRANS:
		PORTB = 0x02;
	break;

	default:
        break;
   } // State actions
}

int main() {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

   ucOutput = 0x00;              // Initialize outputs
   state = START; // Indicates initial call

   while(1) {
      Tick();
   }
}
