unsigned long Time, StartTime, LastTime;
unsigned int TimeSampling = 1000, DeltaTime;


void setup(){
  StartTime = millis();
  LastTime = StartTime;
  general_setup();
  //flow_setup();
  com_setup();
}


void loop(){
  requestTurbidity1();
  Time = millis();
  dataToMaster[0] = NTU1;

  for(int i=0;i<1;i++){
        intdataToMaster[i] = round(dataToMaster[i]*100);  
      }
}
