# 🧪 Batik Wastewater Treatment System with Adaptive MRAC Control

This project is the final undergraduate thesis of **Caleb Effendi**, conducted at the **Institut Teknologi Bandung**, under the Engineering Physics Department. The research focuses on the **optimization of a batik wastewater adsorption system** and the **design of an adaptive MRAC (Model Reference Adaptive Control)** to improve the system’s performance in reducing turbidity.

## 📘 Project Overview

Batik production in Indonesia generates wastewater containing residual dyes, contributing to serious environmental issues. This project implements an adsorption system using a **fixed-bed method** with the following objectives:

- **System identification** using turbidity sensor data.
- **Optimization** of the adsorption system structure using **MINLP (Mixed Integer Non-Linear Programming)**.
- **Design and simulation** of an **adaptive MRAC control model** to improve the turbidity reduction process.

## 🛠️ Features

- **Data Acquisition** using turbidity sensors and **ThingSpeak**.
- **System Identification** via first-order system modeling with time delay.
- **Adaptive Control (MRAC)** implementation using simulation in MATLAB.
- **Optimization of system configuration** for minimal tank/pump usage using MINLP.
- **Achieved turbidity reduction** from 200 NTU to under 100 NTU.

## 📘 System Model Summary

- System modeled as:  
  `G(s) = (k / (τs + 1)) * e^(-Ls)`
- Gain range: 7.06 – 51.96
- Time constant (τ): 1331 – 3293 seconds
- Reference model τ (MRAC): 859 seconds
- Control parameters: θ₀, γ derived from system identification


## 🧰 Requirements

### MATLAB

- MATLAB (Recommended R2022a or later)
- Statistics and Optimization Toolbox
- Internet connection for ThingSpeak data retrieval

### ESP32 (C++) for IoT & Instrumentation

The turbidity monitoring system uses an **ESP32** microcontroller to collect real-time data from a turbidity sensor and transmit it to **ThingSpeak** over WiFi. This forms the basis of the IoT component used for system identification and monitoring.

#### Hardware Components

- **ESP32 Dev Module**
- **Turbidity Sensor** (e.g., SEN0189 or similar)
- Breadboard and Jumper Wires
- Resistors (as required for sensor connection)
- Power Source (USB or external 5V)
- (Optional) LCD / OLED Display

#### Arduino Libraries (for ESP32)

Ensure the following libraries are installed via the Arduino IDE:

- `WiFi.h` (for ESP32 WiFi)
- `ThingSpeak.h` (ThingSpeak API client)
- `Adafruit_Sensor` and others (optional, depending on added peripherals)

#### ESP32 Setup

1. Wire the turbidity sensor’s analog output to **GPIO36 (VP)** or any ESP32 ADC pin.
2. Configure your WiFi credentials and ThingSpeak channel credentials.
3. Upload the firmware using the Arduino IDE.
4. Observe turbidity readings on your ThingSpeak dashboard.

#### Example ESP32 Sketch

```cpp
#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiClient client;
unsigned long channelNumber = YOUR_CHANNEL_ID;
const char* writeAPIKey = "YOUR_API_KEY";

int turbidityPin = 36;  // GPIO36 (VP), ADC1 channel

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected.");
  ThingSpeak.begin(client);
}

void loop() {
  int sensorValue = analogRead(turbidityPin);
  float turbidity = map(sensorValue, 0, 4095, 0, 100); // Replace with proper calibration

  ThingSpeak.writeField(channelNumber, 1, turbidity, writeAPIKey);
  Serial.println("Turbidity: " + String(turbidity) + " NTU");
  delay(15000);  // 15s update interval
}

