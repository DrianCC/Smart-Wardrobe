# Smart-Wardrobe with ESP32, Ultrasonic Sensor, Humidity & Temperature Sensor.
Final Project Embedded System

## Anggota Kelompok
1. Adrian Alessandro Christopher Chandra - 235150301111020
2. Kenichi Amarul Ardi - 235150300111014
3. Timotius Joseph Mahardika Hartono - 235150307111016
4. Muhammad Shafly Syarif Aji Kurnia - 235150300111021
5. Rayhan Sulistyawan - 235150301111019
6. Muhammad Alwen Franzzy - 205150300111003

## Gambaran Umum
Proyek ini berfokus pada otomatisasi pengeringan pakaian secara efisien dengan menggunakan sensor, aktuator, dan mikrokontroller ESP32

## Latar Belakang Masalah
- Proses pengeringan pakaian umumnya dilakukan dengan menjemur pakaian di bawah terik sinar matahari, metode pengeringan tersebut memakan waktu dan memerlukan sinar matahari yang cukup agar pakaian dapat kering dengan baik.
- Pakaian yang telah digunakan sekali dan hanya terkena basah hujan atau tumpah air hanya perlu dikeringkan saja, tidak perlu dilakukan pencucian ulang.
- Pakaian - pakaian yang telah terkena basah hujan atau tumpah air, perlu digunakan lagi dengan cepat.

## Solusi yang ditawarkan
- Pengeringan pakaian yang lebih cepat dan efektif, dibanding sinar matahari yang hanya ada di siang hari
- Proses Pengeringan pakaian tanpa proses cuci baju terlebih dahulu
- Monitoring baju agar tetap kering dan siap dipakai
  
## Komponen yang diperlukan
- **ESP32S**: Sebagai pusat pengendali system.
- **Sensor DHT 22**: Sebagai sensor suhu lemari.
- **Sensor Ultrasonik HCSR04**: Sebagai sensor ada atau tidaknya objek dalam lemari.
- **PTC Heater 12V**: Sebagai pemancar Panas untuk menghangatkan objek dalam lemari. 
- **Fan DC 12V**: Sebagai penyebar suhu panas dalam lemari
- **Adaptor 12V**: Sebagai sumber daya untuk Fan dan PTC Heater
- **DC-005 Module Socket**: Sebagai penyalur tegangan DC dari Adaptor ke rangkaian.

## Datasheet ESP32S
![Datasheet ESP32S](https://github.com/user-attachments/assets/aa81bf9e-b97c-4a69-b641-b1f83533cc67)

## Schematic Rangkaian
![Skematik rangkaian projek_fixed fixed fix](https://github.com/user-attachments/assets/8faf7e0f-4962-4909-a241-3378cd5eedcd)

## Demo
- **Setup**    : Pasang semua komponen yang dibutuhkan hingga seperti pada skematik rangkaian, lalu upload kode ke esp32s menggunakan arduino IDE.
- **Demo**     : Basahkan baju hingga lembab atau sedikit basah, lalu taruh baju tersebut menggunakan gantungan pakaian khusus untuk alat ini, lalu tunggu hingga lampu led mati.
- **Evaluasi** : Cek apakah baju sudah kering atau belum, jika belum maka dapat menjalankan demo lagi hingga baju kering 

**Video Demo** : https://drive.google.com/file/d/1rmECCz-hHelhXy4JRZZ3N6yS2sYXi1DK/view?usp=sharing

## Kesimpulan
Alat ini ditujukan untuk pengeringan pakaian secara otomatis dengan rentang waktu pengeringan dari 30 menit - 1 jam, yang mana cukup efektif ketika pakaian yang kita keringkan, perlu digunakan secepatnya atau pakaian tersebut hanya basah sedikit dan tidak perlu pengeringan dengan mesin cuci.
