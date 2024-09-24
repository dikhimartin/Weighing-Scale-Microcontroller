# **Weighing Scale Microcontroller**

This repository provides a solution for integrating digital weighing scales with microcontrollers like **NodeMCU ESP32** and **Arduino**. The project enables real-time weight data collection and wireless transmission to smartphones, utilizing the **RS232 protocol** for communication between the scale and the microcontroller. This setup is highly valuable for IoT applications, particularly in **agriculture**, **logistics**, and **inventory management**.

---

## **Features**

- **Arduino Support**: Code for interfacing Arduino with digital weighing scales.
- **NodeMCU ESP32 Support**: Code for NodeMCU ESP32 to receive weight data and transmit it via Bluetooth Serial.
- **RS232 Communication**: Uses an **RS232 to TTL Converter** to handle communication between the scale and microcontroller.
- **Bluetooth Connectivity**: ESP32 sends weight data wirelessly to smartphones or Bluetooth-enabled devices.
- **Data Processing**: Custom functions to process and format raw weight data.

---

## **Project Overview**

The repository is structured to provide two main solutions:
1. **Arduino-based Setup**: Interface Arduino with digital scales via RS232.
2. **NodeMCU ESP32 Setup**: Interface with scales and transmit data wirelessly over Bluetooth.

---

## **Branches**

- **`Arduino`**: Contains the Arduino code for the project.
- **`NodeMCU ESP32`**: Contains the NodeMCU ESP32 code.

---

## **Hardware Requirements**

- **NodeMCU ESP32** or **Arduino**
- **Digital Weighing Indicator** (supporting RS232 protocol)
- **RS232 to TTL Converter** (e.g., MAX232 module)
- **Jumper Wires**
- **RS232 Data Cable**
- **Smartphone** with **Bluetooth** and a **Bluetooth Serial Terminal** app

---

## **Getting Started**

### **Hardware Setup**

1. **Connect the RS232 to TTL Converter** between the weighing scale and microcontroller.
2. **Bluetooth Communication**: For NodeMCU ESP32, Bluetooth is built-in, eliminating the need for additional modules.

### **Software Setup**

1. **Download the Arduino IDE** for uploading code to the microcontrollers.
2. **Install the Bluetooth Serial Terminal App** on your smartphone.

---

## **Code Overview**

### **Arduino Code**
This sketch allows the Arduino to read weight data from the scale via RS232 and transmit it to a connected HC-06 Bluetooth module.

```cpp
#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

// SoftwareSerial on Pins 10 and 11 for the weighing scale
SoftwareSerial weighingScale(10, 11);

// AltSoftSerial for HC-06 Bluetooth on Pins 8 and 9
AltSoftSerial bluetooth; // RX Pin 8, TX Pin 9

void setup() {
  Serial.begin(9600);           // Serial monitor
  weighingScale.begin(9600);    // Baud rate for the scale
  bluetooth.begin(9600);        // Baud rate for HC-06
}

void loop() {
  if (weighingScale.available()) {
    char dataFromScale = weighingScale.read(); // Read data from the scale
    Serial.write(dataFromScale);               // Display on the serial monitor
    bluetooth.write(dataFromScale);            // Send data to HC-06
  }
}
```

### **NodeMCU ESP32 Code**
This sketch interfaces NodeMCU ESP32 with the weighing scale and transmits the data wirelessly via Bluetooth.

```cpp
#include "BluetoothSerial.h"
#include <HardwareSerial.h>

// Initialize Bluetooth for ESP32
BluetoothSerial ESP_BT;

// Function to process scale data
String processScaleData(String rawData) {
  // Add your processing logic here
}

void setup() {
  Serial.begin(9600);
  weighingScale.begin(9600, SERIAL_8N1, 16, 17); // UART configuration

  // Initialize Bluetooth
  ESP_BT.begin("TimbanganESP32");
}

void loop() {
  // Logic to read scale data and transmit via Bluetooth
}
```

---

## **Testing**

1. **Upload the Arduino/ESP32 code** to your microcontroller.
2. **Connect the hardware** as per the wiring diagram.
3. **Open Serial Monitor** to view the weight data.
4. **Pair the Bluetooth** device with your smartphone and use the **Bluetooth Serial Terminal** app to view real-time data.

---

## **License**

This project is licensed under the MIT License.
