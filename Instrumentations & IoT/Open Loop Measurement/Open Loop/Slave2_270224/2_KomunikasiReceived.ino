#include <Wire.h> 
#define slaveAddr_2 0b0001001

int dataFromMaster[2];

float InputSerial1;
float InputSerial2;

int receive_wire_int(){
    while(Wire.available() < 1){}
    // Read low byte into rxnum
    int rxnum = Wire.read();
    while(Wire.available() < 1){}
    // Read high byte into rxnum
    rxnum += Wire.read() << 8;
    return rxnum;
}

void com_setup_receive(){
  Wire.begin(slaveAddr_2);     
  Wire.onReceive(receiveData);
}

void receiveData(int byteCount){
  while (Wire.available()) {
        for (int i = 0; i < 2; i++) {
            dataFromMaster[i] = receive_wire_int();
        }
  InputSerial1 = 100;
  InputSerial2 = 100;
}
}
