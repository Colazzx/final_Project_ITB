//Program : Sensor temperature DS18S20

#include <OneWire.h>

int PIN_TEMP1 = 4; //DS18S20 Signal pin on digital 2
int PIN_TEMP2 = 2;

//Temperature chip i/o
OneWire ds1(PIN_TEMP1);  // on digital pin 2
OneWire ds2(PIN_TEMP2);

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  float temperature1 = getTemp1();
  Serial.print("Temperature 1: ");
  Serial.print(temperature1);

  float temperature2 = getTemp2();
  Serial.print("\tTemperature 2: ");
  Serial.println(temperature2);
  
  delay(500); //just here to slow down the output so it is easier to read
  
}


float getTemp1(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds1.search(addr)) {
      //no more sensors on chain, reset search
      ds1.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds1.reset();
  ds1.select(addr);
  ds1.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds1.reset();
  ds1.select(addr);    
  ds1.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds1.read();
  }
  
  ds1.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead1 = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum1 = tempRead1 / 16;
  
  return TemperatureSum1;
}

float getTemp2(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds2.search(addr)) {
      //no more sensors on chain, reset search
      ds2.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds2.reset();
  ds2.select(addr);
  ds2.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds2.reset();
  ds2.select(addr);    
  ds2.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds2.read();
  }
  
  ds2.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead2 = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum2 = tempRead2 / 16;
  
  return TemperatureSum2;
  
}
