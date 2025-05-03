//Program : Pembacaan Sensor Turbidity

//#include <WiFi.h>
//#include "secrets.h"
// #include "ThingSpeak.h"

#define PIN_TURBIDITY1 35
#define PIN_TURBIDITY2 34

// char ssid[] = SECRET_SSID;   // your network SSID (name) 
// char pass[] = SECRET_PASS;   // your network password
// int keyIndex = 0;            // your network key Index number (needed only for WEP)
// WiFiClient  client;

// unsigned long myChannelNumber = SECRET_CH_ID;
// const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  // WiFi.mode(WIFI_STA);   
  // ThingSpeak.begin(client);  // Initialize ThingSpeak
}
void loop() {
      // Connect or reconnect to WiFi
      // if(WiFi.status() != WL_CONNECTED){
      //   Serial.print("Attempting to connect to SSID: ");
      //   Serial.println(SECRET_SSID);
      //   while(WiFi.status() != WL_CONNECTED){
      //     WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      //     Serial.print(".");
      //     delay(5000);     
      //   } 
      //   Serial.println("\nConnected.");
      // }

      // Read sensor value and update
      // int sensorValue1 = analogRead(PIN_TURBIDITY1);// read the input on analog pin 0::
      // float voltage1 = sensorValue1 * (3.3 / 4095.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
      // Serial.print("Voltage:");
      // Serial.print(voltage1);
      // float NTU1 =-485.13*(voltage1*voltage1*voltage1) + 1944.2*(voltage1*voltage1) - 2668.4*(voltage1) + 1274.9;
      // Serial.print("\tTurbidity1: ");
      // Serial.print(NTU1);

      int sensorValue2 = analogRead(PIN_TURBIDITY2);// read the input on analog pin 0::
      float voltage2 = sensorValue2 * (3.3 / 4095.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
      Serial.print("\tVoltage2:");
      Serial.print(voltage2);
      float NTU2 = -40.89*(voltage2*voltage2*voltage2) + 667.96*(voltage2*voltage2) - 1854*(voltage2) + 1446.2;
      Serial.print("\tTurbidity2: ");
      Serial.println(NTU2);

       // set the fields with the values
      //  ThingSpeak.setField(1, NTU1);
      //  ThingSpeak.setField(2, NTU2);

      // write to the ThingSpeak channel
      // int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      // if(x == 200){
      //   Serial.print("-> success");
      // }
      // else{
      //   Serial.print("-> Problem updating channel. HTTP error code " + String(x));
      // } 
      
      delay(500);  
  }
