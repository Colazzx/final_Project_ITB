#include <Wire.h>
#define slaveAddr_2 0b0001001

int dataToSlave2[2];
float dataFromSlave2[4];

void com_setup_2(){
  Wire.begin();
}

void slave_2(){
//  serial();
//  dataToSlave2[0] = controlInput;
//  dataToSlave2[1] = controlInput;
//  Wire.beginTransmission(slaveAddr_2);
//  Wire.write((uint8_t*)dataToSlave2, 4);
//  Wire.endTransmission();

  Wire.requestFrom(slaveAddr_2,8);
  while (Wire.available()) {
        for (int i = 0; i < 4; i++) {
            float temp = receive_wire_int();
            dataFromSlave2[i] = temp/100;
        }
    }
}
