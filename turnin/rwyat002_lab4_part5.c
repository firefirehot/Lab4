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



enum States { START, CENTER, POUNDTRANS, ARRAYTRANS,LOCKTRANS, LOCK,ARRAY} state;

unsigned char ucOutput;
unsigned char ucCorrectInput;
unsigned char secretCode[3];

void Tick()
{
  switch(state) {   // Transitions
     case START:  // Initial transition
	PORTB = ucOutput;
	state = CENTER;
        break;

     case CENTER:
	if(PINA == 0x04)
		state = POUNDTRANS;
	else if(PINA == 0x07)
		state = LOCKTRANS;
	else
		state = CENTER;
        break;

     case POUNDTRANS:
	if(PINA == 0x00)
		state = ARRAY;
	else
		state = POUNDTRANS;
        break;

      case ARRAY:
	if(ucCorrectInput == 3){
		state = CENTER;
		if(ucOutput == 0x00){
			ucOutput = 0x01;
			PORTB = 0x01;
		}
		else if(ucOutput == 0x01){
			ucOutput = 0x00;
			PORTB = 0x00;	
		}
	}
	else if(PINA == secretCode[ucCorrectInput]){
		state = ARRAYTRANS;
		ucCorrectInput = ucCorrectInput + 1;
	}
	else if(PINA == 0x00)
		state = ARRAY;
	else
		state = CENTER;
	break;

      case LOCKTRANS:
	if(PINA == 0x00)
		state = LOCK;
	else
		state = LOCKTRANS;
	break;
	
	case ARRAYTRANS:
		if(PINA == 0x00)
			state = ARRAY;
		else
			state = ARRAYTRANS;
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
		ucCorrectInput = 0x00;
        break;

	case POUNDTRANS:
        break;
	
	case ARRAYTRANS:
	break;
	
	case LOCKTRANS:
	break;

	case ARRAY:
	break;

	case LOCK:
	ucOutput = 0x00;
	PORTB = 0x00;
	break;

	default:
        break;
   } // State actions
}

int main() {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

   ucOutput = 0x00;              // Initialize outputs
   ucCorrectInput = 0x00;
   secretCode[0] = 0x01;secretCode[1] = 0x02;secretCode[2] = 0x01;
   state = START; // Indicates initial call

   while(1) {
      Tick();
   }
}
