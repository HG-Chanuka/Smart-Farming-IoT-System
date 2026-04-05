#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;


#define BLACK  0x0000
#define WHITE  0xFFFF
#define RED    0xF800 //color

void setup() {
  Serial.begin(9600); // data from node b
  tft.begin(tft.readID());
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(20, 10);
  tft.print("SMART FARM SYSTEM");
  tft.drawFastHLine(0, 45, 320, WHITE); //underline
}

void loop() {
  if (Serial.available() > 0) {

  
    String water= Serial.readStringUntil(',');
    String soil1= Serial.readStringUntil(',');
    String soil2= Serial.readStringUntil(',');
    String temp= Serial.readStringUntil(',');
    String hum= Serial.readStringUntil(',');
    String motion= Serial.readStringUntil(',');
    String pA= Serial.readStringUntil(',');
    String pB= Serial.readStringUntil('\n');

tft.fillRect(0, 50, 320, 190, BLACK);
tft.setTextSize(2);
tft.setTextColor(WHITE);

tft.setCursor(10, 60); 
tft.print("Soil 1: "); 
tft.print(soil1);
tft.setCursor(10, 85); 
tft.print("Soil 2: "); 
tft.print(soil2);
tft.setCursor(10, 110); 
tft.print("Temperature: "); 
tft.print(temp);
tft.setCursor(10, 135); 
tft.print("Humidity: "); 
tft.print(hum);
tft.setCursor(10, 160); 
tft.print("Water Dist: "); 
tft.print(water);

tft.setCursor(10, 185);
tft.print("Motion: ");
if (motion == "1") {
  tft.setTextColor(RED);
  tft.print("ALERT!");
  tft.setTextColor(WHITE);
} else {
  tft.print("SAFE");
}

if (pA == "1") {
  tft.setTextColor(RED);
  tft.setCursor(10, 215); 
  tft.print("PUMP A ON");
  tft.setTextColor(WHITE);
}
if (pB == "1") {
  tft.setTextColor(RED);
  tft.setCursor(180, 215); 
  tft.print("PUMP B ON");
  tft.setTextColor(WHITE); // i got some helps from gemini
} 

  }
}