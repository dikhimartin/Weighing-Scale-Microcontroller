#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

// Initialize SoftwareSerial for the weighing scale
SoftwareSerial weighingScale(10, 11); // RX, TX pins for the scale
AltSoftSerial bluetooth; // RX Pin 8, TX Pin 9 for HC-06

// Function to process scale data
String processScaleData(String rawData) {
  // Add your processing logic here
  // This function is intended to handle the raw data received from the scale
}

void setup() {
  Serial.begin(9600);                // Initialize Serial Monitor
  weighingScale.begin(9600);         // Start communication with the weighing scale
  bluetooth.begin(9600);             // Start Bluetooth communication
}

void loop() {
  // Check if data is available from the weighing scale
  if (weighingScale.available()) {
    String dataFromScale = ""; // Initialize an empty string to hold incoming data
    
    // Read the incoming data until a newline character is received
    while (weighingScale.available()) {
      char c = weighingScale.read(); // Read a character
      dataFromScale += c;            // Append it to the data string
    }
    
    // Process the scale data
    String processedData = processScaleData(dataFromScale);
    
    // Display data in Serial Monitor
    Serial.println(processedData);    // Print processed data to Serial Monitor
    
    // Send processed data via Bluetooth
    bluetooth.print(processedData);    // Send data to the HC-06 module
  }
}
