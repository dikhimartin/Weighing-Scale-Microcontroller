#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

// Timbangan menggunakan SoftwareSerial pada Pin 10 dan 11
SoftwareSerial weighingScale(10, 11);

// HC-06 menggunakan AltSoftSerial pada Pin 8 dan 9
AltSoftSerial bluetooth; // RX Pin 8, TX Pin 9

void setup() {
  Serial.begin(9600);           // Serial monitor
  weighingScale.begin(9600);    // Baud rate untuk timbangan
  bluetooth.begin(9600);        // Baud rate untuk HC-06
}

void loop() {
  if (weighingScale.available()) {
    char dataFromScale = weighingScale.read(); // Membaca data dari timbangan
    
    Serial.write(dataFromScale);               // Menampilkan di serial monitor
    bluetooth.write(dataFromScale);            // Mengirim data ke HC-06
  }
}