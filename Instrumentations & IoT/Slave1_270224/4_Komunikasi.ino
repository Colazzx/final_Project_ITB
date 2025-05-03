#include <Wire.h> 
#define slaveAddr_1 0b0001000

float dataToMaster[1];
int intdataToMaster[1];

void com_setup(){
  Wire.begin(slaveAddr_1);     // Set alamat slave ke 8
  Wire.onRequest(sendData);    // Mendaftarkan fungsi sendData untuk event onRequest
}

void sendData() {
  Wire.write((uint8_t*)intdataToMaster, 2); 
}
