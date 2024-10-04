#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Pilih pin untuk RX dan TX sesuai dengan wiring yang kamu gunakan
#define RXD_PIN 3
#define TXD_PIN 1  // Tidak digunakan dalam komunikasi ini, tapi perlu di-declare

// BLE setup
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
const char* serviceUUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
const char* characteristicUUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

// Callback class untuk koneksi BLE
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Device connected");
    }

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Device disconnected");
      BLEDevice::startAdvertising(); // Restart advertising setelah disconnect
    }
};

void setup() {
  // Inisialisasi Serial (untuk debugging)
  Serial.begin(115200);
  
  // Inisialisasi Serial1 untuk RS232
  Serial1.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN);

  // Inisialisasi BLE
  BLEDevice::init("ESP32_C3_Scale"); // Nama perangkat BLE
  BLEServer *pServer = BLEDevice::createServer();
  
  // Callback untuk koneksi BLE
  pServer->setCallbacks(new MyServerCallbacks());
  
  BLEService *pService = pServer->createService(serviceUUID);
  pCharacteristic = pService->createCharacteristic(
                      characteristicUUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
  pCharacteristic->addDescriptor(new BLE2902());
  
  pService->start();
  
  // Mulai advertising BLE agar perangkat lain bisa mendeteksi
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
}

void loop() {
  // Cek apakah ada data yang tersedia dari RS232 (Serial1)
  if (Serial1.available() > 0) {
    // Baca data dari RS232
    String data = Serial1.readStringUntil('\n');
    
    // Kirim data ke BLE jika ada perangkat terhubung
    if (deviceConnected) {
      pCharacteristic->setValue(data.c_str());
      pCharacteristic->notify(); // Mengirim notifikasi ke perangkat yang terhubung
    }
    
    // Tampilkan di Serial Monitor untuk debugging
    Serial.print("Data diterima: ");
    Serial.println(data);
  }

  delay(100);  // Delay untuk mengurangi load
}
