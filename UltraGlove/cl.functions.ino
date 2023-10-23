#include <Wire.h>
#include "paj7620.h"

#define LED_PIN 4
#define GES_UP_FLAG 1
#define GES_DOWN_FLAG 2

void setup()
{
  Wire.begin();
  pinMode(LED_PIN, OUTPUT);
  paj7620Init(); // Assuming the function is provided by the library and properly set up
}

void loop()
{
  uint8_t data = 0;  // Read Bank_0_Reg_0x43/0x44 for gesture result.

  paj7620ReadReg(0x43, 1, &data);  // When different gestures are detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).

  if (data == GES_UP_FLAG)      // When up gesture is detected, the variable 'data' will be set to GES_UP_FLAG.
    digitalWrite(LED_PIN, HIGH);      // turn the LED on (HIGH is the voltage level)
  else if (data == GES_DOWN_FLAG)      // When down gesture is detected, the variable 'data' will be set to GES_DOWN_FLAG.
    digitalWrite(LED_PIN, LOW);       // turn the LED off by making the voltage LOW
}
