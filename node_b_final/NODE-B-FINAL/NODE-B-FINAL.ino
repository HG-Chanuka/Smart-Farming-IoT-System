#include <esp_now.h>
#include <WiFi.h>

int pumpA= 26;
int pumpB= 27;
int valve= 14;
int buzzer=16;
int trig= 32;
int echo= 33;

struct Data {
  int soil1;
  int soil2;
  float temp;
  float humidity;
  int motion;
};

Data inData;

int statusA = 0;
int statusB = 0;

void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t * data, int len) {
  memcpy(&inData, data, sizeof(inData));
}

void setup() {
  Serial2.begin(9600, SERIAL_8N1, -1, 17); // send data to uno

  pinMode(pumpA,OUTPUT);
  pinMode(pumpB,OUTPUT);
  pinMode(valve,OUTPUT);
  pinMode(buzzer,OUTPUT);

//high no low yes

  digitalWrite(pumpA,HIGH);
  digitalWrite(pumpB,HIGH);
  digitalWrite(valve ,HIGH);
  digitalWrite(buzzer,LOW);//

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // water level
  digitalWrite(trig,LOW); 
  delayMicroseconds(2);
  digitalWrite(trig,HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  float dist =pulseIn(echo,HIGH) * 0.034 / 2; //cm

  if (dist > 5) {
    digitalWrite(pumpA,LOW);
    statusA = 1;
  } else {
    digitalWrite(pumpA,HIGH);
    statusA = 0;
  }

  if (inData.soil1 >2000 ||inData.soil2 >2000) {
    // anything
    digitalWrite(pumpB,LOW);
    digitalWrite(valve,LOW);
    statusB = 1;
  } else {
    digitalWrite(pumpB,HIGH);
    digitalWrite(valve,HIGH);
    statusB =0;
  }

  if (inData.motion == 1) {
    digitalWrite(buzzer,HIGH);
  } else {
    digitalWrite(buzzer,LOW);
  }

Serial2.print(dist);
Serial2.print(",");
Serial2.print(inData.soil1);
Serial2.print(",");
Serial2.print(inData.soil2);
Serial2.print(",");
Serial2.print(inData.temp);
Serial2.print(",");
Serial2.print(inData.humidity);
Serial2.print(",");
Serial2.print(inData.motion);
Serial2.print(",");
Serial2.print(statusA);
Serial2.print(",");
Serial2.println(statusB);

  delay(2000);
}
