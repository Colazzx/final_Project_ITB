  #include <Wire.h>
#define slaveAddr_1 0b0001000

float dataFromSlave1[1];

int receive_wire_int(){
    while(Wire.available() < 1){}
    // Read low byte into rxnum
    int rxnum = Wire.read();
    while(Wire.available() < 1){}
    // Read high byte into rxnum
    rxnum += Wire.read() << 8;
    return rxnum;
}

void com_setup(){
  Wire.begin();
}

void slave_1(){
  Wire.requestFrom(slaveAddr_1,2);
  while (Wire.available()) {
        for (int i = 0; i < 1; i++) {
            float temp = receive_wire_int();
            dataFromSlave1[i] = temp/100;
        }
    }
}
