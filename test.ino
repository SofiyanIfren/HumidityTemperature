#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "SevSeg.h"

#define DHTPIN A5
#define DHTTYPE DHT11   // DHT 11
DHT dht = DHT(DHTPIN, DHTTYPE);
SevSeg sevseg;

unsigned long previousMillis = 0;
unsigned long previousMillis_2 = 0;
const long interval = 10000; 
const long interval_2 = 20000; 

float tempHumidity = 0;
float tempTemp = 0;
float t = 0.0;
float h = 0.0;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    t = dht.readTemperature();
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print(" \xC2\xB0");
    Serial.println("C");
    sevseg.setNumber(t,2);
    previousMillis = currentMillis;
  }
  if (currentMillis - previousMillis_2 >= interval_2) {
    h = dht.readHumidity();
    Serial.print("Humidité : ");
    Serial.print(h);
    Serial.println(" %");
    sevseg.setNumber(h,2);
    previousMillis_2 = currentMillis;
  } 
  
  
  sevseg.refreshDisplay(); // Must run repeatedly
  /*// Communication via port série
  char mot[5] = {}; // faut tjrs initialiser en c, sinon pointe n'importe où => illisible
  int index = 0;
  if (Serial.available()) { // si des caractères sont en attente d'être lus
    char c = Serial.read();
    Serial.print(c); // on l'écrit sur le moniteur
    mot[index] = c;
    index += 1;
  }
  Serial.println(mot);
  delay(50);*/
  
}
