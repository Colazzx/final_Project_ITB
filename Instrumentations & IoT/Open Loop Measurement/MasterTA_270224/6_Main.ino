unsigned long Time, StartTime, LastTime;
unsigned int TimeSampling = 500, DeltaTime;

// char ssid[] = SECRET_SSID;   // your network SSID (name) 
// char pass[] = SECRET_PASS;   // your network password
// int keyIndex = 0;            // your network key Index number (needed only for WEP)
// WiFiClient  client;

// unsigned long myChannelNumber = SECRET_CH_ID;
// const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

#define PIN_TURBIDITY2 34

float received_Turbidity_1;
float received_Turbidity_2;

// Define variables for controller parameters

float kx = 0.4625; // Control parameter for plant state
float kr = 0.6009; // Control parameter for reference signal
float theta = 0.8; // Initial value of adaptive parameter

float gamma1 = 0.000001; // Adaptation rate parameter

// Define variables for reference model
// float k = 2.2789;    % Value of 'k'
// float tau = 1369.3;    % Value of 'tau'
// float am = 0.0015; % Reference model parameter
// float bm = 0.001;   % Reference model parameter
// float a = 1/tau;   % Plant parameter
// float b = k/tau;   % Plant parameter


float plantState;
//float referenceSignal = 100; // Desired setpoint

float error;

float referenceModel(){  
  float referenceSignal = 50*exp(-0.0015*(Time - StartTime - TimeSampling)/1000)+150;
  return referenceSignal;
}

float measurePlantState() {
    int sensorValue2 = analogRead(PIN_TURBIDITY2);
    float voltage2 = sensorValue2 * (3.3/ 4095.0); 
    float NTU2 = -706*(voltage2*voltage2*voltage2) + 2519.4*(voltage2*voltage2) - 2990*(voltage2) + 1277.2+50;
    return NTU2;
}

void setup(){
  general_setup();
  StartTime = millis();
  LastTime = StartTime;
  header();
  com_setup();
}

void loop(){
  Time = millis();
  if(Time - LastTime >= TimeSampling){
    DeltaTime = Time - LastTime;
    slave_1();
    slave_2();

    // Measure plant state
    float actualPlantState = measurePlantState();

    // Calculate error
    error = actualPlantState - referenceModel();

    // Calculate control input using control law
    float controlInput = kx * actualPlantState + kr * referenceModel() - theta * actualPlantState;

    // float minimum = 0;
    // float maximum = 100;

    // // Limit control input to a minimum of 40
    // controlInput = min(controlInput,maximum);

    // Update adaptive parameter using adaptive law
    float theta_dot = -gamma1 * error * actualPlantState; // Compute the derivative of theta
    theta = theta + theta_dot; // Update theta

    serial();
    dataToSlave2[0] = controlInput;
    dataToSlave2[1] = controlInput;
    Wire.beginTransmission(slaveAddr_2);
    Wire.write((uint8_t*)dataToSlave2, 4);
    Wire.endTransmission();
    
    LastTime = Time;
    Serial.print((Time - StartTime - TimeSampling)/1000);
    Serial.print("\t");
    Serial.print(DeltaTime);
    Serial.print("\t");
    Serial.print(dataFromSlave2[0], 2);  // Menampilkan dua digit desimal
    Serial.print("\t");
    Serial.print(dataFromSlave2[2], 2);  // Menampilkan dua digit desimal
    Serial.print("\t");
    Serial.print(dataFromSlave2[1], 2);  // Menampilkan dua digit desimal
    Serial.print("\t");
    Serial.print(dataFromSlave2[3], 2);  // Menampilkan dua digit desimal
    Serial.print("\t");
    Serial.print(dataFromSlave1[0], 2);  // Menampilkan dua digit desimal
    // ThingSpeak.setField(1, received_Turbidity_1);
    Serial.print("\t");
    // ThingSpeak.setField(1, actualPlantState);
    Serial.print(actualPlantState, 2);  // Menampilkan dua digit desimal
    Serial.print("\t");    
    Serial.print("\n");
  }
}

void header(){
  Serial.println("Time\tdTime\tPercent1\tVolt1\tPercent2\tVolt2\tTurbidity1\tTurbidity2\tReference\terror\ttheta\controlInput");
//  Serial.println("Time\tdTime\tTurbidity1\tTurbidity2");
}
