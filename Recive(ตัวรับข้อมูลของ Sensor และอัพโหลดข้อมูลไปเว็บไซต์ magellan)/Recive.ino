// RX
#include <SoftwareSerial.h>
#include "Magellan_BC95.h"
Magellan_BC95 magel;
#define rxPin 2
#define txPin 3
SoftwareSerial RX(rxPin, txPin); // RX | TX
String payload;
void setup() {
  Serial.begin(115200);
  magel.begin(); 
  RX.begin(4800);
}
void loop() {
  static int winddir;
  static float windspeedmph, humidity, tempf,  rainin, pressure, batt_lvl, light_lvl;
  static volatile float dailyrainin;
  static char SerialBuffer[9];
  static char SerialData;
  static byte SerialState = 0;
  static byte SerialIndex = 0;
  static double Timeout = millis();
  if (RX.available()) {
    SerialData = RX.read();
    switch (SerialState) {
      case 0: if (SerialData == '#') {
          SerialState = 1;
          SerialIndex = 0;
        }
        break;
      case 1: if (SerialData == 'a') {
          SerialBuffer[SerialIndex] = '\0';
          winddir = atoi(SerialBuffer);
          SerialState = 2;
          SerialIndex = 0;

        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
      case 2: if (SerialData == 'b') {
          SerialBuffer[SerialIndex] = '\0';
          windspeedmph = atoi(SerialBuffer);
          SerialState = 3;
          SerialIndex = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
      case 3: if (SerialData == 'c') {
          SerialBuffer[SerialIndex] = '\0';
          humidity = atoi(SerialBuffer);
          SerialState = 4;
          SerialIndex = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
      case 4: if (SerialData == 'd') {
          SerialBuffer[SerialIndex] = '\0';
          tempf = atoi(SerialBuffer);
          SerialState = 5;
          SerialIndex = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
      case 5: if (SerialData == 'e') {
          SerialBuffer[SerialIndex] = '\0';
          rainin = atoi(SerialBuffer);
          SerialState = 6;
          SerialIndex = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
      case 6: if (SerialData == 'f') {
          SerialBuffer[SerialIndex] = '\0';
          dailyrainin = atoi(SerialBuffer);
          SerialState = 7;
          SerialIndex = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
      case 7: if (SerialData == 'g') {
          SerialBuffer[SerialIndex] = '\0';
          pressure = atoi(SerialBuffer);
          SerialState = 8;
          SerialIndex = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
      case 8: if (SerialData == 'h') {
          SerialBuffer[SerialIndex] = '\0';
          batt_lvl = atoi(SerialBuffer);
          SerialState = 9;
          SerialIndex = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
      case 9: if (SerialData == 'i') {
          SerialBuffer[SerialIndex] = '\0';
          light_lvl = atoi(SerialBuffer);
          Serial.println();
          Serial.print("winddir=");
          Serial.println(winddir);
          String S_winddir      = String(winddir);
          String S_windspeedmph = String(windspeedmph);
          String S_humidity     = String(humidity);
          String S_tempf        = String(tempf);
          String S_rainin       = String(rainin);
          String S_dailyrainin  = String(dailyrainin);
          String S_pressure     = String(pressure);
          String S_batt_lvl     = String(batt_lvl);
          String S_light_lvl    = String(light_lvl);
          payload="{\"Winddir\":"+S_winddir+",\"Windspeedmph\":"+S_windspeedmph+",\"Humidity\":"+S_humidity+",\"tempf\":"+S_tempf+",\"Rainin\":"+S_rainin+",\"Dailyrainin\":"+S_dailyrainin+",\"Pressure\":"+S_pressure+",\"Batt_lvl\":"+S_batt_lvl+",\"Light_lvl\":"+S_light_lvl+"}";
          magel.report(payload); 
          Timeout = millis();
          SerialState = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 9) {
            SerialState = 0;
          }
        }
        break;
    }
  }
  if ((millis() - Timeout) > 3000) {
    Timeout = millis();
    Serial.println("การเชื่อมต่อมีปัญหา");
  } 
}
