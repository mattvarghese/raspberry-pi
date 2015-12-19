#include <wiringPi.h>
#include <stdio.h>

#define LedPin    0
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

