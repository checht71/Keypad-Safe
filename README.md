The following code is for an MSP430 based safe. At this stage in development, these components are not connected with the keypad. This will be in the next update.

## Servo
#### Purpose:
The servomotor is supposed to rotate when the correct combination is entered on the keypad and open the safe door.
#### Pinout:
Pin 6.4 - sends the signal to the servo.
Pin 4.1 - L Button
Pin 2.3 - R Button
#### Circuit:
To operate the servo, it must be part of transistor circuit.
#### Notes:
This file should be redesigned in the next update to rely on the keypad for input rather than the MSP buttons. The servo motor takes a PWM as input, which is timer based.

## Latch/Solenoid
#### Purpose:
The Solenoid should activate when the correct input is entered on the keypad in order to allow the door to open.
#### Pinout:
Pin 4.0 - sends the signal to the solenoid.
Pin 4.1 - L Button
Pin 2.3 - R Button
#### Circuit:
To operate the solenoid, it must be part of transistor circuit.
#### Notes:
This code uses a simple button interrupt to set 4.0 high or low. The interrupt should be changed to reflect the keypad values in the next update. The comments of the code also need to be updated.

## Buzzer
#### Purpose:
The buzzer should sound when the safe is left open for a certain amount of time to prevent the user accidentally leaving the safe unlocked.
#### Pinout:
Pin 6.3 - PWM out to buzzer
Pin 4.1 - L Button, decrease pitch
Pin 2.3 - R Button, increase pitch
#### Circuit:
To operate the servo, it must be part of transistor circuit.
#### Notes:
The pitch of the buzzer is dependent on the duty cycle of the PWM. The code should be updated to include a countdown which activates the buzzer after x seconds.
The L and R buttons are also redundant and can be removed. The comments of this code also need to be updated.
