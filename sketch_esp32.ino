#include "BluetoothSerial.h"
#include <HardwareSerial.h>

// Inisialisasi Bluetooth pada ESP32
BluetoothSerial ESP_BT; 

// Menggunakan UART2 pada GPIO16 (RX) dan GPIO17 (TX)
HardwareSerial weighingScale(2);

// Fungsi untuk memproses data dari timbangan
String processScaleData(String rawData) {
  // Cek apakah data dimulai dengan "wn"
  if (rawData.startsWith("wn")) {
    rawData = rawData.substring(2); // Hapus "wn"
    
    // Hapus "kg" di akhir
    rawData.replace("kg", "");
    
    // Ubah titik menjadi koma
    rawData.replace(".", ",");

    // Cek jika data negatif
    bool isNegative = rawData.startsWith("-");
    
    // Jika negatif, hapus sementara tanda minus untuk pemrosesan
    if (isNegative) {
      rawData = rawData.substring(1); // Hapus tanda minus sementara
    }

    // Hapus leading zero, kecuali jika nol diikuti oleh koma (misalnya, "0,25")
    while (rawData.length() > 1 && rawData[0] == '0' && rawData[1] != ',') {
      rawData = rawData.substring(1);  // Hapus nol yang tidak diperlukan
    }

    // Tambahkan '0' jika angka pertama adalah koma
    if (rawData[0] == ',') {
      rawData = "0" + rawData;
    }

    // Jika awalnya negatif, tambahkan kembali tanda minus
    if (isNegative) {
      return "-" + rawData;
    }

    return rawData;
  }
  return "";
}

void setup() {
  // Inisialisasi serial monitor dan timbangan
  Serial.begin(9600);
  weighingScale.begin(9600, SERIAL_8N1, 16, 17); // RX = GPIO16, TX = GPIO17
  
  // Inisialisasi Bluetooth
  ESP_BT.begin("TimbanganESP32"); // Nama Bluetooth yang muncul di smartphone
  Serial.println("Bluetooth Started! Pair device with 'TimbanganESP32'");
}

void loop() {
  // Buffer untuk membaca data dari timbangan
  static String scaleData = "";

  // Baca data dari timbangan
  while (weighingScale.available()) {
    char incomingByte = weighingScale.read();
    
    // Memastikan bahwa data lengkap sudah diterima (hingga newline '\n')
    if (incomingByte == '\n') {
      // Proses data dari timbangan
      String processedData = processScaleData(scaleData);

      // Jika data valid setelah proses
      if (processedData != "") {
        // Tampilkan di serial monitor
        Serial.println(processedData);
        
        // Kirim data ke Bluetooth
        ESP_BT.println(processedData);
      }
      
      // Reset buffer setelah data diproses
      scaleData = "";
    } else {
      // Menambahkan karakter yang diterima ke buffer
      scaleData += incomingByte;
    }
  }
}
