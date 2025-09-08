#define LED_PIN 4
#define LED_PIN2 5
#define LED_PIN3 16
#define D3 0
#define D4 2

// wifi
#include <ESP8266WiFi.h>
#define ssid  ""
#define password  ""

// LCD SCREEN
#include <Wire.h>
#include <string.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Client
#include <WiFiClientSecure.h>

// Telegram
#include <AsyncTelegram2.h>
#define token ""

WiFiClientSecure client;
AsyncTelegram2 myBot(client);

void displayLCD(const char *pesan1, const char *pesan2) {
  lcd.setCursor((16 / 2) - (strlen(pesan1) / 2),0);
  lcd.print(pesan1);
  lcd.setCursor((16 / 2) - (strlen(pesan2) / 2),1);
  lcd.print(pesan2);
}

void setup() {
  Serial.begin(300);
  Serial.println("Bot is ready!!");

  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);

  Wire.begin(D3, D4);  
  lcd.init();   
  lcd.backlight();
}

void getStock(TBMessage msg) {
  myBot.sendMessage(msg, "Get product stock");
}

void updateStock(TBMessage msg){
  myBot.sendMessage(msg, "Update product stock");
  // using infunction loop and status based on step
  // can be stop if user give certain command

  // get product
  // product name. etc
  // update database
}

void addProduct(TBMessage msg) {
  myBot.sendMessage(msg, "Add new product");
  // using infunction loop and status based on step
  // can be stop if user give certain command

  // get product
  // product name, etc
  // store database
}

void addTransaction(TBMessage msg) {
  myBot.sendMessage(msg, "Add new transaction");
  // will use struck to act like an object
  // using infunction loop and status based on step
  // can be stop if user give certain command

  // date
  // name
  // get product
  // select product
  // confirmation
    // recipt??
  // store to database
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    displayLCD("wifi","....");

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN3, HIGH);

    //  Telegram setup
    client.setInsecure();  // skip certificate validation
    myBot.setTelegramToken(token);
    Serial.println(myBot.begin() ? "Bot OK" : "Bot FAIL");

    delay(60 * 1000);
  } else {
    displayLCD("wifi", WiFi.localIP().toString().c_str());

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN3, LOW);

    TBMessage msg;
    if (myBot.getNewMessage(msg)) {
      digitalWrite(LED_PIN, LOW);  
      digitalWrite(LED_PIN2, HIGH);
      digitalWrite(LED_PIN3, LOW);
      delay(500);

      //  check user

      if (msg.text == "/start") {
        myBot.sendMessage(msg, "Hello, this is RUNO House!");
        char message[] = "--bot commands--\n/getStock\n/updateStock\n/addProduct\n/addTransaction\n/getReport";
        myBot.sendMessage(msg, message);
      } else if(msg.text == "/getStock") {
        getStock(msg);
      } else if(msg.text == "/updateStock") {
        // conversation
        updateStock(msg);
      } else if(msg.text == "/addProduct") {
        // conversation
        addProduct(msg);
      } else if(msg.text == "/addTransaction") {
        // conversation
        addTransaction(msg);
      } else if(msg.text == "/getReport") {
        myBot.sendMessage(msg, "Sales monthly report");
      }

 
      digitalWrite(LED_PIN, LOW); 
      digitalWrite(LED_PIN2, LOW);
      digitalWrite(LED_PIN3, HIGH);
      msg = {};
      delay(500);    
    }
  }           
}
