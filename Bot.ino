#define LED_PIN 4
#define LED_PIN2 5
#define LED_PIN3 16
#define D3 0
#define D4 2

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <AsyncTelegram2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

# wifi
#define ssid = "";
#define password = "";

# LCD 
LiquidCrystal_I2C lcd(0x27, 16, 2);

void displayLCD(const char *pesan1, const char *pesan2) {
  lcd.setCursor((16 / 2) - (strlen(pesan1) / 2),0);
  lcd.print(pesan1);
  lcd.setCursor((16 / 2) - (strlen(pesan2) / 2),1);
  lcd.print(pesan2);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);

  Wire.begin(D3, D4);  
  lcd.init();   
  lcd.backlight();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    displayLCD("wifi","....");

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN3, HIGH);

    delay(60 * 1000); # one minute
  } else {
    displayLCD("wifi", WiFi.localIP().toString().c_str());

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN3, LOW);
    delay(500);

    digitalWrite(LED_PIN, LOW);  
    digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN3, LOW);
    delay(500);

    digitalWrite(LED_PIN, LOW); 
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN3, HIGH);
    delay(500);    
  }           
}
