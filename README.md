# Project Menampilkan Jumlah Pendaftar Google Form Melalui Display Dot Matrix ESP32

Berikut adalah tutorial lengkap yang diperbarui dengan petunjuk mengambil file dari repositori dan Google Apps Script.

---

# Tutorial Menghitung Data Google Form dengan ESP32 dan Dot Matrix MAX7219

## 1. **Membuat Google Form dan Menyiapkan Google Apps Script**

1. **Buat Google Form:**
   - Buat form baru di Google Forms.
   - Tambahkan pertanyaan sesuai kebutuhan (contoh: Nama, Email, Nomor Telepon, dll).
   - Klik **Responses** > **Link to Sheets** untuk menghubungkan form dengan Google Sheets.

2. **Menambahkan Google Apps Script:**
   - Buka Google Sheets yang terhubung dengan Google Form.
   - Klik **Extensions** > **Apps Script**.
   - Salin dan tempel kode dari file **Code.gs** yang dapat ditemukan di Google Apps Script dengan nama **Code.gs**.
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

Kode Arduino dapat ditemukan di folder repositori dengan nama **Coding_Final.ino**. Silakan salin kode tersebut ke dalam Arduino IDE Anda. 

### **Cara Menggunakan Kode Arduino:**
1. Salin file **Coding_Final.ino** dari folder repositori Anda ke komputer.
2. Buka file tersebut menggunakan Arduino IDE.
3. Pastikan untuk mengganti URL Google Apps Script pada bagian kode dengan URL Anda (contoh: `https://script.google.com/macros/s/your-script-id/exec`).
4. Upload ke board ESP32.

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

## 6. **Informasi Tambahan**

Untuk kebutuhan custom proyek atau lainnya, silakan hubungi kami melalui WhatsApp: **081287931296**.

**Ikuti dan Dukung KelasRobot di Media Sosial:**
- **Instagram:** [KelasRobot](https://www.instagram.com/kelasrobot)
- **Facebook:** [KelasRobot](https://www.facebook.com/kelasrobot)
- **YouTube:** [KelasRobot Channel](https://www.youtube.com/kelasrobot)

Semoga bermanfaat, dan jangan ragu untuk bertanya jika ada kesulitan! 😊
