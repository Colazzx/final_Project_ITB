/*
 # This sample code is used to test the pH meter Pro V1.0 and Temperature Sensor.
 # Editor : Caleb & Hansen (Engineering Physics)
 # Ver    : 1.0
 # Product: Analog pH meter Pro & temperature sensor
 # Date   : 23 October 2023 
 # SKU    : SEN0169
*/
#include <OneWire.h>

#define SensorPin1 A1        //pH meter Analog output to Arduino Analog Input 0
#define SensorPin2 A2
#define Offset 0.15           //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 1000
#define ArrayLenth  40    //times of collection
int pHArray1[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;  
int pHArray2[ArrayLenth];   //Store the average value of the sensor feedback 
int PIN_TEMP1 = 4; //DS18S20 Signal pin on digital 2
int PIN_TEMP2 = 2; 

//Temperature chip i/o
OneWire ds1(PIN_TEMP1);  // on digital pin 2
OneWire ds2(PIN_TEMP2);

void setup(void) {
  pinMode(LED,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("pH meter and temperature measurement!");    //Test the serial monitor
}

void loop(void) {
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue1,voltage1,pHValue2,voltage2;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray1[pHArrayIndex++]=analogRead(SensorPin1);
      pHArray2[pHArrayIndex++]=analogRead(SensorPin2);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage1 = (avergearray(pHArray1, ArrayLenth)*5.0/1024);
      voltage2 = (avergearray(pHArray2, ArrayLenth)*5.0/1024);
      pHValue1 = 3.5*voltage1+Offset;
      pHValue2 = 3.5*voltage2+Offset;
      samplingTime=millis();
  }

  if(millis() - printTime > printInterval)   //Every 1000 milliseconds, print a numerical, convert the state of the LED indicator
  {
  //Serial.print(millis()-printTime);
  //Serial.print(",");

  // Pengukuran Temperatur
  float temperature1 = getTemp1();
  Serial.print("Temperature 1 (°C): ");
  Serial.print(temperature1);

  float temperature2 = getTemp2();
  Serial.print("\tTemperature 2 (°C): ");
  Serial.print(temperature2);
  
  //Serial.print("\t Voltage1: ");
  //Serial.print(voltage1,2);
  Serial.print("\tpH1: ");
  Serial.print(pHValue1,2);
  //Serial.print("\tVoltage2: ");
  //Serial.print(voltage2,2);
  Serial.print("\tpH2: ");
  Serial.println(pHValue2,2);

  delay(500);

  digitalWrite(LED,digitalRead(LED)^1);
  printTime=millis();
  }

}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
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
