#include <Wire.h> 
#define slaveAddr_1 0b0001000

#define PIN_TURBIDITY1 A0
#define PIN_TURBIDITY2 A1

/*Tab 1_pHSensor*/
static float requestTurbidity1() {
  int sensorValue1 = analogRead(PIN_TURBIDITY1);// read the input on analog pin 0::
  float voltage1 = sensorValue1 * (3.3 / 4095.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float NTU1 =-485.13*(voltage1*voltage1*voltage1) + 1944.2*(voltage1*voltage1) - 2668.4*(voltage1) + 1274.9;
  return NTU1;
}
static float requestTurbidity2() {
  int sensorValue2 = analogRead(PIN_TURBIDITY2);// read the input on analog pin 0::
  float voltage2 = sensorValue2 * (3.3 / 4095.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float NTU2 = -40.89*(voltage2*voltage2*voltage2) + 667.96*(voltage2*voltage2) - 1854*(voltage2) + 1446.2;
  return NTU2;
}

/*Tab 4_Komunikasi*/
void com_setup(){
  Wire.begin(slaveAddr_1);     // Set alamat slave ke 8
  Wire.onRequest(sendData);    // Mendaftarkan fungsi sendData untuk event onRequest
}

void sendData() {
  float dataTurbidity1 = requestTurbidity1();    // Panggil fungsi data() untuk mendapatkan nilai terbaru
  float dataTurbidity2 = requestTurbidity2();
  Wire.write((byte*)&dataTurbidity1, sizeof(dataTurbidity1));
  Wire.write((byte*)&dataTurbidity2, sizeof(dataTurbidity2));
}

/*Tab 5_Main*/
void setup(){
  Serial.begin(9600);
}

void loop(){
  com_setup();
}
