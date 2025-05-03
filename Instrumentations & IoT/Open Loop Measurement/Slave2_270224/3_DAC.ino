#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 DAC1;
Adafruit_MCP4725 DAC2;

float Percent1 = 0.0, Percent2 = 0.0;
uint16_t InputMCP1 = 0, InputMCP2 = 0;
float volt1 = 0, volt2 = 0;

void DAC_setup(){
  DAC1.begin(0x60);
  DAC2.begin(0x61);
}

void DAC(){
  Percent1 = percentageLimit((float)InputSerial1);
  InputMCP1 = (uint16_t)(4095 * Percent1 / 100);
  DAC1.setVoltage(InputMCP1, false);

  // Menghitung persentase dan nilai InputMCP2
  Percent2 = percentageLimit((float)InputSerial2);
  InputMCP2 = (uint16_t)(4095 * Percent2 / 100);
  DAC2.setVoltage(InputMCP2, false);
  volt1 = (float)(Percent1 * 12)/100;
  volt2 = (float)(Percent2 * 12)/100;
}

float percentageLimit(float Percent) {
  if (Percent > 100.0) return 100.0;
  else if (Percent < 0.0) return 0.0;
  else return Percent;
}
