#include "LSM6DS3.h"
#include "Wire.h"

#define CLEAR_STEP      true
#define NOT_CLEAR_STEP  false

//Create a instance of class LSM6DS3
LSM6DS3 lsm6ds3(I2C_MODE, 0x6A);    //I2C device address 0x6A
uint16_t detectCount = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial);
    if (lsm6ds3.begin() != 0) {
        Serial.println("Device error");
    } else {
        Serial.println("Device OK!");
    }
x
    if (0 != config_free_fall_detect()) {
        Serial.println("Fail to configure!");
    } else {
        Serial.println("Success to Configure!");
    }
}

void loop() {
    uint8_t readDataByte = 0;
    //Read the wake-up source register
    lsm6ds3.readRegister(&readDataByte, LSM6DS3_ACC_GYRO_WAKE_UP_SRC);
    //Mask off the FF_IA bit for free-fall detection
    readDataByte &= 0x20;
    if (readDataByte) {
        detectCount ++;
        Serial.print("Free fall detected!  ");
        Serial.println(detectCount);
    }
    delay(10);
}

int config_free_fall_detect(void) {
    uint8_t error = 0;
    uint8_t dataToWrite = 0;

    dataToWrite |= LSM6DS3_ACC_GYRO_BW_XL_200Hz;
    dataToWrite |= LSM6DS3_ACC_GYRO_FS_XL_2g;
    dataToWrite |= LSM6DS3_ACC_GYRO_ODR_XL_416Hz;

    error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, dataToWrite);
    error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_WAKE_UP_DUR, 0x00);
    error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_FREE_FALL, 0x33);
    error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_MD1_CFG, 0x10);
    error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_MD2_CFG, 0x10);
    error += lsm6ds3.writeRegister(LSM6DS3_ACC_GYRO_TAP_CFG1, 0x81);

    return error;
}


#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_pt_PT.h>
#include <Keyboard_sv_SE.h>
#include <Wire.h>
#include "paj7620.h"


#define GES_REACTION_TIME  500
#define GES_ENTRY_TIME   800
#define GES_QUIT_TIME   1000

void setup()
{
  uint8_t error = 0;

  Serial.begin(9600);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  error = paj7620Init();
  if (error) 
  {
    Serial.print("INIT ERROR, CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:\n");

}

void loop()
{
  uint8_t data = 0, data1 = 0, error;
  
  error = paj7620ReadReg(0x43, 1, &data);
  if (!error) 
  {
    switch (data) 
    {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          Keyboard.press('w');  // Type 'w' when a forward gesture is detected
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Right");
        }          
        break;
      // Other cases remain unchanged
      // ...
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          Serial.println("Wave");
        }
        break;
    }
  }
  delay(100);
}