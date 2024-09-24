#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

// Initialize SoftwareSerial for the weighing scale on Pins 10 and 11
SoftwareSerial weighingScale(10, 11); // RX, TX pins for the scale

// Initialize AltSoftSerial for HC-06 on Pins 8 and 9
AltSoftSerial bluetooth; // RX Pin 8, TX Pin 9

// Function to process scale data
String processScaleData(String rawData) {
  // Add your processing logic here
  // Example: Removing unwanted characters or formatting the data
  return rawData; // Returning the raw data as is for now
}

void setup() {
  Serial.begin(9600);           // Initialize Serial Monitor
  weighingScale.begin(9600);    // Baud rate for the weighing scale
  bluetooth.begin(9600);        // Baud rate for HC-06
}

void loop() {
  // Check if data is available from the weighing scale
  if (weighingScale.available()) {
    char dataFromScale = weighingScale.read(); // Read data from the scale
    String scaleData = ""; // Initialize string to hold incoming data

    // Append character to the scaleData string
    scaleData += dataFromScale;

    // Process the scale data
    String processedData = processScaleData(scaleData);

    Serial.write(processedData.c_str());      // Display processed data in Serial Monitor
    bluetooth.write(processedData.c_str());   // Send processed data to HC-06
  }
}
