// Nama : Kodingan 2 Pompa OK EYNH
// Tanggal Revisi : 12122023

#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 DAC1;
Adafruit_MCP4725 DAC2;

int InputSerial1 = 0; // Variable to store the first input
int InputSerial2 = 0; // Variable to store the second input
float Percent1 = 0.0, Percent2 = 0.0;
uint16_t InputMCP1 = 0, InputMCP2 = 0;
//int sign = 1;

//#define pompa1 3
//#define pompa2 5

unsigned long Time, StartTime, LastTime;
unsigned int TimeSampling = 1000, DeltaTime;

void setup() {
  Serial.begin(115200);
  DAC1.begin(0x60);
  DAC2.begin(0x61);
  //  print_header();
  //pinMode(pompa1, OUTPUT); 
  //pinMode(pompa2, OUTPUT);
  StartTime = millis();
  LastTime = StartTime;
}

void loop() {
  Time = millis ();
  if (Time - LastTime >= TimeSampling) {
    DeltaTime = Time - LastTime;
    LastTime = Time;
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n'); // Read the entire line until newline
      int commaIndex = input.indexOf(' '); // Find the space in the input

      if (commaIndex != -1) {
        String value1 = input.substring(0, commaIndex); // Extract the first value
        String value2 = input.substring(commaIndex + 1); // Extract the second value

        // Convert the extracted values to integers
        InputSerial1 = value1.toInt();
        InputSerial2 = value2.toInt();
      }
    }
    // Print the values
    Serial.print (DeltaTime);
    Serial.print(",");
    Serial.print((Time - StartTime - TimeSampling) / 1000);
    Serial.print(",");


    Percent1 = percentageLimit((float)InputSerial1);
    InputMCP1 = (uint16_t)(4095 * Percent1 / 100);
    DAC1.setVoltage(InputMCP1, false);

    // Menghitung persentase dan nilai InputMCP2
    Percent2 = percentageLimit((float)InputSerial2);
    InputMCP2 = (uint16_t)(4095 * Percent2 / 100);
    DAC2.setVoltage(InputMCP2, false);
    float volt1 = (float)(Percent1 * 12) / 100;
    float volt2 = (float)(Percent2 * 12) / 100;
    Serial.print("IN_1: ");
    Serial.print(Percent1);
    Serial.print(",");
    Serial.print("IN_2: ");
    Serial.print(Percent2);
    Serial.print(",");
    Serial.print("IN_MCP1: ");
    Serial.print(InputMCP1);
    Serial.print(",");
    Serial.print("IN_MCP2: ");
    Serial.print(InputMCP2);
    Serial.print(",");
    Serial.print("Vol_1: ");
    Serial.print(volt1);
    Serial.print(",");
    Serial.print("Vol_2: ");
    Serial.println(volt2);
  }
}
float percentageLimit(float Percent) {
  if (Percent > 100.0) return 100.0;
  else if (Percent < 0.0) return 0.0;
  else return Percent;
}
//void print_header() {
//  Serial.println("Voltage\tDelta\tInput\tMotor\tPos 1\tPos 2\tKec 1\tKec 2");
//}
