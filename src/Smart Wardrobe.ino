#include <Arduino.h>
#include <DHT.h>

// ========== Konstanta & Pin Assignment ==========
#define DHTPIN1 32
#define DHTPIN2 26
#define DHTTYPE DHT22
#define TRIG_PIN 12
#define ECHO_PIN 14
#define RELAY_OUTPUT_PIN 27
#define LED_INDIKATOR_PIN 25

#define SUHU_AMBANG 31.5       // Ambang suhu (°C)
#define KELEMBAPAN_AMBANG 81.5  // Ambang kelembapan (%)
#define JARAK_AMBANG 15         // Ambang jarak (cm)

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

// ========== Variabel Global ==========
float suhuGlobal = 0.0;
float kelembapanGlobal = 0.0;
int jarakGlobal = 100;
bool dataValid = false;

// ========== Fungsi Membaca Jarak ==========
int bacaJarak() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long durasi = pulseIn(ECHO_PIN, HIGH);
  int jarak = durasi * 0.034 / 2;
  return jarak;
}

// ========== Task Sensor ==========
void TaskSensor(void *pvParameters) {
  for (;;) {
    float suhu1 = dht1.readTemperature();
    float suhu2 = dht2.readTemperature();
    float hum1 = dht1.readHumidity();
    float hum2 = dht2.readHumidity();
    int jarak = bacaJarak();

    if (!isnan(suhu1) && !isnan(suhu2) && !isnan(hum1) && !isnan(hum2)) {
      suhuGlobal = (suhu1 + suhu2) / 2.0;
      kelembapanGlobal = (hum1 + hum2) / 2.0;
      jarakGlobal = jarak;
      dataValid = true;
    } else {
      dataValid = false;
    }

    Serial.print("[Sensor] Suhu: ");
    Serial.print(suhuGlobal);
    Serial.print(" °C | Kelembapan: ");
    Serial.print(kelembapanGlobal);
    Serial.print(" % | Jarak: ");
    Serial.print(jarakGlobal);
    Serial.println(" cm");

    vTaskDelay(pdMS_TO_TICKS(500));  // Delay 0.5 detik
  }
}

// ========== Task Aktuator ==========
void TaskAktuator(void *pvParameters) {
  for (;;) {
    if (dataValid && jarakGlobal <= JARAK_AMBANG) {
      digitalWrite(LED_INDIKATOR_PIN, HIGH);

      if (kelembapanGlobal >= KELEMBAPAN_AMBANG && suhuGlobal < SUHU_AMBANG) {
        Serial.println("[Aktuator] Relay ON (Kelembapan di bawah ambang)");
        digitalWrite(RELAY_OUTPUT_PIN, HIGH);
      } else if (suhuGlobal > SUHU_AMBANG && kelembapanGlobal >= KELEMBAPAN_AMBANG) {
        Serial.println("[Aktuator] Relay OFF (Suhu tinggi dan kelembapan tinggi)");
        digitalWrite(RELAY_OUTPUT_PIN, LOW);
      } else if(kelembapanGlobal <= KELEMBAPAN_AMBANG){
        digitalWrite(RELAY_OUTPUT_PIN, LOW);
        digitalWrite(LED_INDIKATOR_PIN, LOW);
      }else {
        Serial.println("[Aktuator] Kondisi tidak memenuhi syarat, Relay OFF");
        digitalWrite(RELAY_OUTPUT_PIN, LOW);
      }

    } else {
      Serial.println("[Aktuator] Tidak ada baju atau data tidak valid");
      digitalWrite(LED_INDIKATOR_PIN, LOW);
      digitalWrite(RELAY_OUTPUT_PIN, LOW);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));  // Delay 1 detik
  }
}

// ========== Setup ==========
void setup() {
  Serial.begin(115200);

  dht1.begin();
  dht2.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);                                                                      
  pinMode(RELAY_OUTPUT_PIN, OUTPUT);
  pinMode(LED_INDIKATOR_PIN, OUTPUT);

  digitalWrite(RELAY_OUTPUT_PIN, LOW);
  digitalWrite(LED_INDIKATOR_PIN, LOW);


  Serial.println("Smart Wardrobe RTOS Aktif");

  // Membuat task RTOS
  xTaskCreatePinnedToCore(TaskSensor, "Sensor Task", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskAktuator, "Aktuator Task", 2048, NULL, 1, NULL, 1); 
}

// ========== Loop Kosong ==========
void loop() {
  // Kosong karena logic berada di RTOS Task
}
