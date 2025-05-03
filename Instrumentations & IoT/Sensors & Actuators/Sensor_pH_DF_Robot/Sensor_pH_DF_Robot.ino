/*
 # This sample code is used to test the pH meter Pro V1.0.
 # Editor : YouYou
 # Ver    : 1.0
 # Product: analog pH meter Pro
 # SKU    : SEN0169
*/
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

void setup(void)
{
  pinMode(LED,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("pH meter experiment!");    //Test the serial monitor
}
void loop(void)
{
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
  Serial.print(millis()-printTime);
  Serial.print(",");
  Serial.print("Voltage1: ");
  Serial.print(voltage1,2);
  Serial.print(" pH1 value: ");
  Serial.print(pHValue1,2);
  Serial.print("\tVoltage2: ");
  Serial.print(voltage2,2);
  Serial.print("\tpH2 value: ");
  Serial.println(pHValue2,2);
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
