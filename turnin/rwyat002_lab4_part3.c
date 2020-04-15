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



enum States { START, CENTER, POUNDTRANS, PRESSYTRANS,LOCKTRANS, LOCK,POUND,PRESSY} state;


void Tick()
{
  switch(state) {   // Transitions
     case START:  // Initial transition
	PORTB = 0x00;
	state = CENTER;
        break;

     case CENTER:
	if(PINA == 0x04)
		state = POUNDTRANS;
	else if(PINA == 0x08)
		state = LOCKTRANS;
	else
		state = CENTER;
        break;

     case POUNDTRANS:
	if(PINA == 0x00)
		state = POUND;
	else
		state = POUNDTRANS;
        break;
      case PRESSYTRANS:
	if(PINA == 0x00)
		state = PRESSY;
	else
		state = PRESSYTRANS;
	break;
      case LOCKTRANS:
	if(PINA == 0x00)
		state = LOCK;
	else
		state = LOCKTRANS;
	break;
	
	case POUND:
		if(PINA == 0x00)
			state = POUND;
		else if(PINA == 0x80)
			state = PRESSYTRANS;
		else 
			state = CENTER;
	break;
	case PRESSY:
		state = CENTER;
	break;
	case LOCK:
		state = CENTER;
	break;

     default:
        state = START;
        break;
  } // Transitions

  switch(state) {   // State actions
	case CENTER:
        break;

	case POUNDTRANS:
        break;
	
	case PRESSYTRANS:
	PORTB = 0x01;
	break;
	
	case LOCKTRANS:
	PORTB = 0x00;
	break;

	case POUND:
	break;

	case PRESSY:
	break;

	case LOCK:
	break;

	default:
        break;
   } // State actions
}

int main() {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

  // ucOutput = 0x00;              // Initialize outputs
   state = START; // Indicates initial call

   while(1) {
      Tick();
   }
}
