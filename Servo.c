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
void enableTimer();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT
    gpioInit();
    enableButtonInterrupts();
    enableTimer();

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM0_bits | GIE);           // Enter LPM3 w/ interrupts
    __no_operation();                             // For debug
}

void gpioInit(){

        P6DIR |= BIT4;                                // P6.4 output
        P6OUT &= ~BIT4;                                // P6.4 low
        P6SEL0 &= ~BIT4;
        P6SEL1 &= ~BIT4;

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

void enableTimer(){
    TB0CCR0 = 19999;
    // set period of PWM to 1MHz/999 = 1ms
    TB0CCR1 = 1500;
    //middle servo
    TB0CCTL1 |= CCIE;
    // Enable CCR1 Interrupt
    TB0CTL |= TBSSEL__SMCLK | MC__UP | TBIE | TBCLR;
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
{
    switch(__even_in_range(TB0IV,TB0IV_TBIFG))
    {
        case TB0IV_NONE:
            break;                               // No interrupt
        case TB0IV_TBCCR1:
            P6OUT &= ~BIT4;
            break;
        case TB0IV_TBIFG:
           P6OUT |= BIT4;
            break;
        default:
            break;
    }
}

// Button 4.1 Interrupt - Speed up timer
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
    P4IFG &= ~BIT1;  //Clear flag so that the button is available for interrupt
   if (TB0CCR1 < 2000)
       TB0CCR1 += 100;
}

// Button  2.3 change LED
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3;  //Clear flag so that the button is available for interrupt
    if (TB0CCR1 >800)
        TBCCR1 -= 100;
}

