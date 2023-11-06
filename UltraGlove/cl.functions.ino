/*
The following simple demo will show you a very easy application: When you move up, the red LED will be turned on, otherwise the red LED will be turned off.
*/
#include <Wire.h>
#include "paj7620.h"

const int LED_PIN = 4; // Define the LED pin number

void setup()
{
  pinMode(LED_PIN, OUTPUT); // Initialize the LED pin as an output
  paj7620Init();
}

void loop()
{
  uint8_t data = 0;  // Read Bank_0_Reg_0x43/0x44 for gesture result.

  paj7620ReadReg(0x43, 1, &data);  // When different gestures are detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).

  if (data == GES_UP_FLAG)      // When an up gesture is detected, the variable 'data' will be set to GES_UP_FLAG.
    digitalWrite(LED_PIN, HIGH); // Turn the LED on (HIGH is the voltage level)

  if (data == GES_DOWN_FLAG)      // When a down gesture is detected, the variable 'data' will be set to GES_DOWN_FLAG.
    digitalWrite(LED_PIN, LOW);  // Turn the LED off by making the voltage LOW
}