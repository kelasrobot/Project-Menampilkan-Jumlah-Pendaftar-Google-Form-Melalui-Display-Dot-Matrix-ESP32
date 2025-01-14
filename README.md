# Project Menampilkan Jumlah Pendaftar Google Form Melalui Display Dot Matrix ESP32

## 1. **Membuat Google Form dan Menyiapkan Google Apps Script**
1. **Buat Google Form:**
   - Buat form baru di Google Forms.
   - Tambahkan pertanyaan sesuai kebutuhan (contoh: Nama, Email, Nomor Telepon, dll).
   - Klik **Responses** > **Link to Sheets** untuk menghubungkan form dengan Google Sheets.

2. **Menambahkan Google Apps Script:**
   - Buka Google Sheets yang terhubung dengan Google Form.
   - Klik **Extensions** > **Apps Script**.
   - Masukkan kode berikut:
     ```javascript
     function doGet(e) {
       var spreadsheet = SpreadsheetApp.getActiveSpreadsheet();
       var sheet = spreadsheet.getActiveSheet();
       var range = sheet.getDataRange();
       var data = range.getValues();
       var jumlahData = data.length - 1; // Abaikan header
       var output = {
         status: "success",
         jumlahData: jumlahData
       };
       return ContentService.createTextOutput(JSON.stringify(output))
                            .setMimeType(ContentService.MimeType.JSON);
     }
     ```
   - Klik **Save**, beri nama proyek, lalu klik **Deploy** > **New Deployment**.
   - Pilih **Web App**, atur hak akses ke **Anyone**. Klik **Deploy**.
   - Salin URL yang diberikan (contoh: `https://script.google.com/macros/s/your-script-id/exec`).

---

## 2. **Menambahkan Library ke Arduino IDE**
Untuk menggunakan **WiFi** dan **Dot Matrix MAX7219**, kita memerlukan library tambahan.

1. **Buka Library Manager:**
   - Buka **Arduino IDE**.
   - Klik **Sketch** > **Include Library** > **Manage Libraries**.

2. **Install Library yang Dibutuhkan:**
   - Cari dan install:
     - **WiFi (by Arduino/ESP32)**.
     - **ArduinoJson (by Benoît Blanchon)**.
     - **MD_Parola (by MajicDesigns)**.
     - **MD_MAX72XX (by MajicDesigns)**.

3. **Memastikan Library Terinstal:**
   - Setelah install, pastikan library tersedia di **File** > **Examples**.

---

## 3. **Rangkaian Hardware**
Gunakan diagram berikut untuk menyambungkan ESP32 ke Dot Matrix MAX7219:

### **Koneksi Pin**
| Dot Matrix | ESP32   |
|------------|---------|
| VCC        | 3.3V    |
| GND        | GND     |
| DIN        | D23     |
| CS         | D5      |
| CLK        | D18     |

Pastikan koneksi kuat dan suplai daya mencukupi.

---

## 4. **Kode Arduino untuk ESP32**
Gunakan kode berikut untuk ESP32:

```cpp
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// Konfigurasi WiFi
const char* ssid = "isi nama wifi";
const char* password = "isi password wifi";

// URL Google Apps Script
const char* serverName = "https://script.google.com/macros/s/your-script-id/exec";

// Konfigurasi Dot Matrix
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN      5

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int requestSukses = 0;
int requestGagal = 0;

void setup() {
  Serial.begin(115200);

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung!");

  // Inisialisasi Dot Matrix
  myDisplay.begin();
  myDisplay.setIntensity(6);
  myDisplay.displayClear();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      requestSukses++;
      String respons = http.getString();

      StaticJsonDocument<512> doc;
      deserializeJson(doc, respons);

      int jumlahData = doc["jumlahData"];
      Serial.println("Jumlah Data: " + String(jumlahData));

      // Menampilkan di Dot Matrix
      myDisplay.displayClear();
      myDisplay.print(jumlahData);
    } else {
      requestGagal++;
      Serial.println("Request gagal: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi tidak terhubung!");
    myDisplay.print("WiFi Error");
  }

  delay(10000);
}
```

---

## 5. **Pengujian**
1. **Upload Kode ke ESP32:**
   - Sambungkan ESP32 ke komputer.
   - Pilih port dan board yang sesuai.
   - Upload kode.

2. **Periksa Serial Monitor:**
   - Buka **Tools** > **Serial Monitor** untuk melihat log.
   - Pastikan ESP32 terhubung ke WiFi dan data berhasil diambil.

3. **Lihat Hasil di Dot Matrix:**
   - Jumlah data yang dihitung dari Google Form akan muncul di Dot Matrix.

---

Jika ada kendala atau perlu tambahan penjelasan, silakan tanyakan! 😊
