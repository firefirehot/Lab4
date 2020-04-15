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




enum States { START, CENTER, INCTRANS, DECTRANS,INC, DEC,RESETTRANS,RESET} state;

unsigned char ucOutput;

void Tick()
{
  switch(state) {   // Transitions
     case START:  // Initial transition
	ucOutput = 0x07;
	state = CENTER;
        break;

     case CENTER:
	if(PINA == 0x00)
		state = CENTER;
	else if(PINA == 0x01)
		state = INCTRANS;
	else if(PINA == 0x02)
		state = DECTRANS;
	else if(PINA == 0x03)
		state = RESETTRANS;
        break;

     case INCTRANS:
	if((PINA & 0x01) == 0x00)
		state = INC;
	else
		state = INCTRANS;
        break;
      case DECTRANS:
	if((PINA & 0x02) == 0x00)
		state = DEC;
	else
		state = DECTRANS;
	break;
      case RESETTRANS:
	if((PINA & 0x03) == 0x00)
		state = RESET;
	else
		state = RESETTRANS;
	break;
	
	case INC:
		state = CENTER;
	break;
	case DEC:
		state = CENTER;
	break;
	case RESET:
		state = CENTER;
	break;

     default:
        state = START;
        break;
  } // Transitions

  switch(state) {   // State actions
	case CENTER:
		PORTC = ucOutput;
        break;

	case INCTRANS:
        break;
	
	case DECTRANS:
	break;
	
	case RESETTRANS:
	break;

	case INC:
	if(ucOutput < 9)
		ucOutput = ucOutput + 1;
	break;

	case DEC:
	if(ucOutput > 0)
		ucOutput = ucOutput - 1 ;
	break;

	case RESET:
	ucOutput = 0;
	break;

	default:
        break;
   } // State actions
}

int main() {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

   ucOutput = 0x00;              // Initialize outputs
   state = START; // Indicates initial call

   while(1) {
      Tick();
   }
}
