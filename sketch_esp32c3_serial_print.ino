// Pilih pin untuk RX dan TX sesuai dengan wiring yang kamu gunakan
#define RXD_PIN 3
#define TXD_PIN 1  // Tidak digunakan untuk komunikasi ini, tapi perlu di-declare

void setup() {
  // Inisialisasi komunikasi Serial pada port 0 (USB Serial) untuk debugging
  Serial.begin(115200);
  // Inisialisasi komunikasi Serial1 pada port RX/TX untuk RS232 dengan baud rate 9600 (atau sesuai perangkatmu)
  Serial1.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN); 
}

void loop() {
  // Cek apakah ada data yang tersedia dari Serial1 (RS232)
  if (Serial1.available() > 0) {
    // Baca data dari RS232
    String data = Serial1.readStringUntil('\n');  // Membaca sampai ada new line
    // Tampilkan data pada serial monitor untuk debugging
    Serial.print("Data diterima: ");
    Serial.println(data);
  }

  delay(100);  // Delay untuk mengurangi load
}
