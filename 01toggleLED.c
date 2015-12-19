/* Author: Matt | Varghese Mathew
 * Copyright 2015 Varghese Mathew
 * Youtube video: https://www.youtube.com/watch?v=KXMdAYQf3QA
 * License: GNU General Public License
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * Compile Command:
 *  gcc 01toggleLED.c -o 01toggleLED -l wiringPi
 */
#include <wiringPi.h>
#include <stdio.h>

// RPi2 GPIO17 maps to pin 0
#define LedPin    0
// RPi2 GPIO18 maps to pin 1
#define ButtonPin 1

int state = 0;         // used to track if LED is on or off.
int toggleCount = 0;   // used to count number of falling edges received.

void toggle()
{
    // NOTE: LED is connected to +3.3V and to the PIN.
    // So configuration is active low. 
    if(state==1)
    {
        // Set -ve lead of LED to ground.
        digitalWrite(LedPin,LOW);
        state = 0;
        printf("%d: LED ON\n", toggleCount++);
    }
    else
    {
        // Set -ve lead of LED to +3.3V.
        digitalWrite(LedPin, HIGH);
        state = 1;
        printf("%d: LED OFF\n", toggleCount++);
    }
}

int main(void)
{
    // Try setting up wiringPi.
    if (wiringPiSetup() == -1)
    {
        printf("setup wiringPi failed !\n");
        return 1; 
    }

    // Set LED Pin mode as output.
    // NOTE: we don't need to set Button Pin Mode sinc wiringPiISR does that.
    pinMode(LedPin, OUTPUT);
    
    // Try registering interrupt handler.
    if (wiringPiISR(ButtonPin,INT_EDGE_FALLING,&toggle) != 0)
    {
        printf("Registering ISR failed\n");
        return 2;
    }
    
    // wait for ever so the program doesn't terminate.
    while(1)
    {
        // Yield the thread so CPU doesn't run 100%
        delay(5000);
    }
    
    // make the compilter happy with a return 0 that will never execute.
    return 0;
}

