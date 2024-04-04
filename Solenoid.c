/*
 * Christian Hecht
 * Homework: Button Changing Brightness
 * Date Submitted: 2/23/24
 * Description: This program initializes with both LEDs off. The brightness of each button
 * is then adjusted via the buttons. Button 4.1 will change the brightness of an LED,
 * Button 2.3 will change which LED is being targeted by the Button 4.1 Interrupt.
 * The timers for the LEDs have 10 different brightnesses based on their period.
 */

#include <msp430.h>

void gpioInit();
void enableButtonInterrupts();


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT
    gpioInit();
    enableButtonInterrupts();


    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM0_bits | GIE);           // Enter LPM3 w/ interrupts
    __no_operation();                             // For debug
}

void gpioInit(){

        P4DIR |= BIT0;                                // P6.4 output
        P4OUT &= ~BIT0;                                // P6.4 low
        P4SEL0 &= ~BIT0;
        P4SEL1 &= ~BIT0;

        //Button enable
        P4DIR &= ~BIT1;                         // Set P4.1 (L Button) as input
        P4REN |= BIT1;                          // Enable resistor for P4.1
        P4OUT |= BIT1;                          // Enable voltage source
        P4SEL0 &= ~BIT1;                           // Enable interrupts for this pin
        P4SEL1 &= ~BIT1;                          // Interrupt on falling edge.


        P2DIR &= ~BIT3;                         // Set P2.3 (R Button) as input
        P2REN |= BIT3;                          // Enable resistor for P23.
        P2OUT |= BIT3;
        P2SEL0 &= ~BIT3;
        P2SEL1 &= ~BIT3;
}

void enableButtonInterrupts(){
    P4IES |= BIT1; // High to Low Edge Select
    P4IE |= BIT1; // enable interrupt
    P4IFG &= ~BIT1; // Clear IFG

    P2IES |= BIT3;
    P2IE |= BIT3;
    P2IFG &= ~ BIT3;
}

// Button 4.1 Interrupt - Speed up timer
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
    P4IFG &= ~BIT1;  //Clear flag so that the button is available for interrupt
   P4OUT &= ~BIT0;
}

// Button  2.3 change LED
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3;  //Clear flag so that the button is available for interrupt
    P4OUT |= BIT0;
}

