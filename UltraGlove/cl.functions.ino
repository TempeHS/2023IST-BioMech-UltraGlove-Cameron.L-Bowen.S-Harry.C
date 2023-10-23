/*
The following simple demo will show you a very easy application: When you move up, the red led will be turned on, otherwise the red led will be turned off.
*/
#include <Wire.h>
#include "paj7620.h"

void setup()
{
  paj7620Init();
}

void loop()
{
 uint8_t data = 0;  // Read Bank_0_Reg_0x43/0x44 for gesture result.

 paj7620ReadReg(0x43, 1, &data);  // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).

 if (data == GES_UP_FLAG)      // When up gesture be detected,the variable 'data' will be set to GES_UP_FLAG.
  digitalWrite(4, HIGH);      // turn the LED on (HIGH is the voltage level)
 if (data == GES_DOWN_FLAG)      // When down gesture be detected,the variable 'data' will be set to GES_DOWN_FLAG.
        digitalWrite(4, LOW);       // turn the LED off by making the voltage LOW
}

#include "LSM6DS3.h"
#include "Wire.h"
#include "SPI.h"

uint16_t errorsAndWarnings = 0;

//Create instance of LSM6DS3Core
LSM6DS3Core myIMU(I2C_MODE, 0x6A);    //I2C device address 0x6A

void setup() {
    //Init Serial port
    Serial.begin(9600);
    while (!Serial);

    //Call .beginCore() to configure the IMU
    if (myIMU.beginCore() != 0) {
        Serial.print("\nDevice Error.\n");
    } else {
        Serial.print("\nDevice OK.\n");
    }

    uint8_t dataToWrite = 0;  //Temporary variable

    //Setup the accelerometer******************************
    dataToWrite = 0; //Start Fresh!
    dataToWrite |= LSM6DS3_ACC_GYRO_BW_XL_100Hz;
    dataToWrite |= LSM6DS3_ACC_GYRO_FS_XL_8g;
    dataToWrite |= LSM6DS3_ACC_GYRO_ODR_XL_104Hz;

    //Now, write the patched together data
    errorsAndWarnings += myIMU.writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, dataToWrite);

    //Set the ODR bit
    errorsAndWarnings += myIMU.readRegister(&dataToWrite, LSM6DS3_ACC_GYRO_CTRL4_C);
    dataToWrite &= ~((uint8_t)LSM6DS3_ACC_GYRO_BW_SCAL_ODR_ENABLED);

}

void loop() {
    int16_t temp;
    //Get all parameters
    Serial.print("\nAccelerometer Counts:\n");

    //Acelerometer axis X
    if (myIMU.readRegisterInt16(&temp, LSM6DS3_ACC_GYRO_OUTX_L_XL) != 0) {
        errorsAndWarnings++;
    }
    Serial.print(" X = ");
    Serial.println(temp);

    //Acelerometer axis Y
    if (myIMU.readRegisterInt16(&temp, LSM6DS3_ACC_GYRO_OUTY_L_XL) != 0) {
        errorsAndWarnings++;
    }
    Serial.print(" Y = ");
    Serial.println(temp);

    //Acelerometer axis Z
    if (myIMU.readRegisterInt16(&temp, LSM6DS3_ACC_GYRO_OUTZ_L_XL) != 0) {
        errorsAndWarnings++;
    }
    Serial.print(" Z = ");
    Serial.println(temp);

    Serial.println();
    Serial.print("Total reported Errors and Warnings: ");
    Serial.println(errorsAndWarnings);

    delay(1000);
} 