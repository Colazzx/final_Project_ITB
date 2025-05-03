unsigned long Time, StartTime, LastTime;
unsigned int TimeSampling = 1000, DeltaTime;

void setup(){
  general_setup();
  com_setup_receive();
  DAC_setup();
  com_setup();
}

void loop(){
  Time = millis();
  if(Time - LastTime >= TimeSampling){
    DeltaTime = Time - LastTime;
    DAC();
    LastTime = Time;
  }
  dataToMaster[0] = Percent1;
  dataToMaster[1] = Percent2;
  dataToMaster[2] = volt1;
  dataToMaster[3] = volt2;

  for(int i=0;i<4;i++){
        intdataToMaster[i] = round(dataToMaster[i]*100);  
      }
}
