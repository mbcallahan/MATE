//------------------------------------------------------
//------------------------------------------------------
//   
//  AVRLIB-DEMO
//  For avrlib and Wiring development board.
//  
//
//  File:     blink.c
//  Author:   Juan Reyes    juanig-at-ccrma-stanford_edu
//  Date:     June 18, 2008
//
//  Notes:
//-----------------------------------------------------
//  USING THE WIRING DEVELOPMENT BOARD, BUILT-IN LED
//  IN PIN 48 PORT D SHOULD LIGHT.
//
//-----------------------------------------------------
//  More information about Wiring board:
//
//  http://wiring.org.co/hardware/index.html
//  
//-----------------------------------------------------
//  Information about functions used here and avrlib:
// 
//  ~/avrlib/examples/basic_io/basiciotest.c
//  
//  
//
//*********************************************************
//   Description:
//   ============
//
//   This program will cause Built-in LED to blink on/off 
//   every 500ms.
//
//*********************************************************


//compiler includes
#include <avr/io.h>
#include <avr/interrupt.h>

//avrlib includes
#include "global.h"
#include "timer.h"


int main(void)
{

	//  outb(register,byte) is a function that writes 
        //  a byte to a register.


        //  The DDRG register sets the direction of Port G.
        //  PORTG is labeled PORT6 on the Wiring Board.
  
	// a '1' makes the corresponding pin an OUTPUT.
        // a '0' makes the corresponding pin an INPUT.
	// Ports can only be set as INPUT or OUTPUT (0x00, 0xff).

        // 0xFF is hexadecimal for binary 11111111.
        // Therefore using �outb'. all pins of PORTG 
        // are set to OUTPUT as follows:
        //
        outb(DDRG, 0xFF);
	//
	

        // Gnome calculator in Fedora can do bin-to-hex conversion.
    
        // The PORTG register can set the physical pins on port G high
        // or low when those pins are set to be outputs using DDRG. 
        // When pins are set to input, the PORTG register does something
        // else that will be discussed later.
        
        // To turn off the LEDs we want to pull the end connected to 
        // port A high (to 5V) so that there will be no voltage drop across
        // the LEDs. See the schematic.
        // So we "set" the low 4 bits HIGH (to 5V) of PORTG by writing 1's.
	// Remember 0xF0 is hexadecimal for binary 11110000
	
        outb(PORTG, 0xF0);
	

	// initialize the timer library
	timerInit();

	//loop forever
	while (1) {
	  //clear bit PG0 in the PORTG register - turn LED on
	  cbi(PORTG,PG0);
	  //PORTG = 0xFF;
          // pause for 500ms
	  timerPause(500);

	  //set bit PG0 in the PORTG register - turn LED off
	  sbi(PORTG,PG0);
	  // PORTG = 0x00;
          //pause for 500ms
	  timerPause(500);
	} 

	return 0;
}
