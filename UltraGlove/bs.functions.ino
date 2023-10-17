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