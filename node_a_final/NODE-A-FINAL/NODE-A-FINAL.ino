#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>

#define DHT_PIN 25
#define SOIL1_PIN 32
#define SOIL2_PIN 33
#define PIR_PIN 26

DHT dht(DHT_PIN, DHT11);

uint8_t broadcastAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // i use broadcast id

struct Data {
  int   soil1;
  int   soil2;
  float temp;
  float humidity;
  int   motion;
};

Data myData;

void setup() {
  analogSetAttenuation(ADC_11db); //3.3v full range
  pinMode(PIR_PIN, INPUT);
  dht.begin();
  delay(2000);

  WiFi.mode(WIFI_STA);
  esp_now_init();

  esp_now_peer_info_t partner = {};
  memcpy(partner.peer_addr, broadcastAddr, 6);
  partner.channel = 0;
  partner.encrypt = false;
  esp_now_add_peer(&partner); // got help from gemini
}

void loop() {
  myData.soil1 = analogRead(SOIL1_PIN);
  myData.soil2= analogRead(SOIL2_PIN);
  myData.temp= dht.readTemperature();
  myData.humidity = dht.readHumidity();
  myData.motion= digitalRead(PIR_PIN);

  esp_now_send(broadcastAddr, (uint8_t *) &myData, sizeof(myData));
  delay(2000);
}