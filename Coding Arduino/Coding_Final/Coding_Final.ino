/*
   Kode ini dibuat oleh Ajang Rahmat dari Kelas Robot.
   Hubungi melalui WhatsApp di 0812-8793-1296 untuk pertanyaan atau konsultasi.
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Konfigurasi WiFi
const char* ssid = "isi nama wifi";
const char* password = "isi password wifi";

// URL Google App Script
const char* serverName = "https://script.google.com/macros/s/*****************/exec";

// Konfigurasi LED Matrix
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN      5

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Variabel untuk menghitung request sukses dan gagal
int requestSukses = 0;
int requestGagal = 0;

// Variabel untuk kontrol waktu dengan millis()
unsigned long previousMillis = 0;
const unsigned long interval = 10000; // 10 detik

void setup() {
  Serial.begin(115200);

  // Menghubungkan ke WiFi
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung!");
  Serial.println("Alamat IP: " + WiFi.localIP().toString());

  // Inisialisasi LED Matrix
  myDisplay.begin();
  myDisplay.setIntensity(6); // Brightness
  myDisplay.displayClear();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      // Mengakses URL Google App Script
      Serial.println("Mengakses server Google App Script...");
      http.begin(serverName);
      http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);

      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        if (httpResponseCode == 200) {
          // Request berhasil
          requestSukses++;
          Serial.println("HTTP Response code: " + String(httpResponseCode));

          String respons = http.getString();
          respons.trim();

          StaticJsonDocument<512> doc;
          DeserializationError error = deserializeJson(doc, respons);
          if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
          }
          const char* status = doc["status"]; // "success"
          int jumlahData = doc["jumlahData"]; // 502

          Serial.println("Respon dari Google App Script: ");
          Serial.println(respons);
          Serial.println("Jumlah Data: " + String(jumlahData));

          // Menampilkan data di LED Matrix
          myDisplay.displayClear();
          myDisplay.setTextAlignment(PA_CENTER);
          myDisplay.print(jumlahData);
        } else {
          // Request gagal
          requestGagal++;
          Serial.println("HTTP Response code (Gagal): " + String(httpResponseCode));
        }
      } else {
        // Request gagal
        requestGagal++;
        Serial.println("HTTP Request Gagal. Kode Error: " + String(httpResponseCode));
      }

      // Menampilkan jumlah request sukses dan gagal
      Serial.println("Request Sukses: " + String(requestSukses));
      Serial.println("Request Gagal: " + String(requestGagal));
      Serial.println();

      http.end();
    } else {
      Serial.println("WiFi tidak terhubung!");
      myDisplay.setTextAlignment(PA_CENTER);
      myDisplay.print("WiFi Error");
    }
  }
}
