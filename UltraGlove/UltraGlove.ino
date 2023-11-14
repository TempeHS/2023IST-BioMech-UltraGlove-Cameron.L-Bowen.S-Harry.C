
void accel-gyro setup() {
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

void accel-gyro loop() {
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
=======
>>>>>>> 4db8d3a077577f0664ec160b8853c48fc4a2a9bf
