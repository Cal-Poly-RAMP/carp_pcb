// Constants
#define BAUD_RATE 9600

// Variables
String receivedData = "";
unsigned long lastReceiveTime = 0;
const unsigned long DISPLAY_TIMEOUT = 500; // ms

void setup() {
  Serial.begin(BAUD_RATE); // Initialize serial communication with computer
  Serial1.begin(BAUD_RATE); // Initialize serial communication with chip

  Serial.println("Chip Serial Monitor Started");
  Serial.println("Waiting for data...");
}

void loop() {
  // Read data from the chip
  while (Serial1.available() > 0) {
    char inByte = Serial1.read();
    receivedData += inByte;
    lastReceiveTime = millis();
  }

  // Print complete messages after timeout
  if (receivedData.length() > 0 && (millis() - lastReceiveTime > DISPLAY_TIMEOUT)) {
    Serial.print("Received: ");

    // Print as ASCII
    Serial.print("ASCII: \"");
    Serial.print(receivedData);
    Serial.print("\" | HEX: ");

    // Print as HEX
    for (int i = 0; i < receivedData.length(); i++) {
      char c = receivedData.charAt(i);
      if (c < 0x10) Serial.print("0");
      Serial.print(c, HEX);
      Serial.print(" ");
    }

    Serial.println();
    receivedData = "";
  }

  // Send data to chip if entered in Serial Monitor
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    Serial1.println(input);
    Serial.println("Sent: " + input);
  }
}