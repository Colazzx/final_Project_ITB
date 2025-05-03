int InputSerial1 = 0; // Variable to store the first input
int InputSerial2 = 0; // Variable to store the second input


void serial(){
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
}
