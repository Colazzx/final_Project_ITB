int serial(int SerialRead) {

    if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read the entire line until newline
    int commaIndex = input.indexOf(' '); // Find the space in the input

    if (commaIndex != -1) {
      String value1 = input.substring(0, commaIndex); // Extract the first value
      String value2 = input.substring(commaIndex + 1); // Extract the second value

      // Convert the extracted values to integers
      int InputSerial1 = value1.toInt();
      int InputSerial2= value2.toInt();

      // Print the value
      if (SerialRead > 100) return 100;
      else if (SerialRead < 0) return 0;
    }
  }
  return InputSerial1,InputSerial2;
}
