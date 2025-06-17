#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "EmonLib.h"
#include <ZMPT101B.h>

// Objects
WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);
EnergyMonitor emon;
ZMPT101B voltageSensor(35, 50.0); // GPIO35, 50Hz

#define SENSITIVITY 653.0f
const float currCalibration = 1.0;

float kWh = 0.0, cost = 0.0;
const float ratePerkWh = 6.5;

unsigned long lastMillis = 0;
unsigned long lastPageChange = 0;
int displayPage = 0;

// CSV Data buffer
String csvData = "Voltage (V),Current (A),Power (W),Energy (kWh),Cost (INR)\n";

void setup() {
  Serial.begin(115200);

  // WiFi AP
  WiFi.softAP("ESP32_Server", "12345678");
  Serial.println("ESP32 AP IP: " + WiFi.softAPIP().toString());

  // LCD Init
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("Smart Energy");
  lcd.setCursor(0, 1); lcd.print("Meter");
  delay(2000);

  // Sensor Init
  voltageSensor.setSensitivity(SENSITIVITY);
  emon.current(34, currCalibration);

  // Web routes
  server.on("/", handleRoot);
  server.on("/data.csv", handleCSV);
  server.begin();
}

void loop() {
  server.handleClient();

  float voltage = voltageSensor.getRmsVoltage();
  float current = getCurrent();
  float power = voltage * current;

  

  unsigned long now = millis();
  kWh += (power * (now - lastMillis)) / 3600000.0;
  lastMillis = now;
  cost = kWh * ratePerkWh;

  // Add new reading to CSV data
 csvData += String(voltage, 2) + "\t" +
           String(current, 2) + "\t" +
           String(power, 2) + "\t" +
           String(kWh, 3) + "\t" +
           String(cost, 2) + "\n";

  updateLCD(voltage, current, power);

  if (millis() - lastPageChange > 3000) {
    displayPage = (displayPage + 1) % 2;
    lastPageChange = millis();
  }

  delay(100);
}

float getCurrent() {
  emon.calcVI(20, 2000);
  float current = emon.Irms;
  return (current < 0.05) ? 0 : current;
}

void updateLCD(float voltage, float current, float power) {
  lcd.clear();
  if (displayPage == 0) {
    lcd.setCursor(0, 0);
    lcd.print("V:"); lcd.print(voltage, 1);
    lcd.print(" I:"); lcd.print(current, 2);

    lcd.setCursor(0, 1);
    lcd.print("P:"); lcd.print(power, 1);
    lcd.print("W");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Energy:");
    lcd.print(kWh, 3);
    lcd.print("kWh");

    lcd.setCursor(0, 1);
    lcd.print("Cost:");
    lcd.print(cost, 2);
    lcd.print(" INR");
  }
}

void handleRoot() {
  float voltage = voltageSensor.getRmsVoltage();
  float current = getCurrent();
  float power = voltage * current;

 

  String html = "<html><head>\
  <meta http-equiv='refresh' content='2'>\
  <style>\
  body{font-family:Arial;text-align:center;background:#f4f4f4;}\
  .box{background:#fff;margin:30px auto;padding:20px;width:80%;\
  box-shadow:0 0 10px #ccc;border-radius:10px;}\
  .value{color:#007BFF;font-size:22px;}\
  .button{margin-top:20px;padding:10px 20px;background-color:#007BFF;\
  color:white;border:none;border-radius:5px;font-size:18px;cursor:pointer;}\
  .button:hover{background-color:#0056b3;}\
  </style></head><body>\
  <div class='box'>\
  <h1>Smart Energy Meter</h1>\
  <p>Voltage: <span class='value'>" + String(voltage, 2) + " V</span></p>\
  <p>Current: <span class='value'>" + String(current, 2) + " A</span></p>\
  <p>Power: <span class='value'>" + String(power, 2) + " W</span></p>\
  <p>Energy: <span class='value'>" + String(kWh, 3) + " kWh</span></p>\
  <p>Cost: <span class='value'>" + String(cost, 2) + " INR</span></p>\
  <a href='/data.csv'><button class='button'>Download Excel</button></a>\
  </div></body></html>";

  server.send(200, "text/html", html);
}

void handleCSV() {
  server.sendHeader("Content-Disposition", "attachment; filename=\"data.xls\"");
  server.send(200, "application/vnd.ms-excel", csvData);
}
