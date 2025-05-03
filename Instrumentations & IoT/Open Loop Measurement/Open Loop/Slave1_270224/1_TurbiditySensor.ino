/*========================== TURBIDITY 1 CODE ==========================*/
float NTU1;

// Variables
#define PIN_TURBIDITY1 A0

// Function
static float requestTurbidity1() {
  int sensorValue1 = analogRead(PIN_TURBIDITY1);// read the input on analog pin 0::
  float voltage1 = sensorValue1 * (5 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  NTU1 = 82.338*(voltage1*voltage1) -669.82*voltage1 + 1366;
  return NTU1;
}
