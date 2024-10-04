#include <HardwareSerial.h>

// Inisialisasi objek serial
HardwareSerial MySerial(1); // Menggunakan Serial1

void setup() {
    // Mengatur kecepatan baud
    MySerial.begin(9600, SERIAL_8N1, 1, 0); // RX di pin GPIO 1, TX di pin GPIO 0
    Serial.begin(115200); // Serial monitor
}

void loop() {
    // Cek jika data tersedia di serial
    if (MySerial.available()) {
        // Membaca data dari serial
        String data = MySerial.readStringUntil('\n'); // Membaca hingga newline
        Serial.println("Data diterima: " + data); // Menampilkan data di serial monitor
    }
}
