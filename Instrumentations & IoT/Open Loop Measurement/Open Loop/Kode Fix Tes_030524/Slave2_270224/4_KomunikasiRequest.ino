float dataToMaster[4];
int intdataToMaster[4];

void com_setup(){
  Wire.onRequest(sendData);    // Mendaftarkan fungsi sendData untuk event onRequest
}

void sendData() {
  Wire.write((uint8_t*)intdataToMaster, 8); 
}
