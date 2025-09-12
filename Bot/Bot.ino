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

struct Product {
    String name;
    int quantity; 
    int price;
};

struct Date {
  int day;
  int month;
  int year;
};

struct Order {
  String product;
  int quantity;
};

struct Transaction {
    struct Date date;
    struct Order order;
    String customer;
    unsigned int totalPrice;
};

void displayLCD(const char *pesan1, const char *pesan2) {
  lcd.setCursor((16 / 2) - (strlen(pesan1) / 2),0);
  lcd.print(pesan1);
  lcd.setCursor((16 / 2) - (strlen(pesan2) / 2),1);
  lcd.print(pesan2);
}

Product getProduct(String name){
  // get spesific product data

  struct Product product;

  // call database

  return product;
}

void storeData(struct Product product, String index){

}

int updateQuantity(int a, int b, String operatorStr){
  if (operatorStr.equals("+")) {
      return b - a;
  } else if (operatorStr.equals("-")) {
      return b - a;
  } else {
      return b; 
  }
}

void getStock(TBMessage msg) {
  // get all product data

  myBot.sendMessage(msg, "Get product stock");
}

void updateProduct(long chatId) {
  // show stock

  myBot.sendTo(chatId, String("type /done to end the sesion"));
  myBot.sendTo(chatId, String("Product name:"));

  String status = "/start"; 
  struct Product product;
  TBMessage msg;

  do {
    if (myBot.getNewMessage(msg)) {
      if (chatId == msg.chatId) {
        msg.text.trim();

        if (msg.text.equals("/done")) {
          myBot.sendMessage(msg, "Cancel update item");
          status = msg.text;

        } else if (status.equals("/start")){
          // get from database
          product = getProduct(msg.text);
          
          // null checking
            // set status to /done if there is no product
          

          myBot.sendMessage(msg, "How many: [-/+].[quantity]");
          status = "/quantity";

        } else if (status.equals("/quantity")){
          int quantity = msg.text.substring(3).toInt();

          // update quantity of the product
          product.quantity = updateQuantity(quantity, product.quantity, msg.text.substring(0, 1));

          myBot.sendMessage(msg, "Update product price? [n/y].[number]");
          status = "/price";

        } else if (status.equals("/price")){
          if (msg.text.charAt(0) == 'y' || msg.text.charAt(0) == 'Y'){
            product.price = msg.text.substring(3).toInt();

          }
          myBot.sendMessage(msg, "Processing");

          // store product to database

          status = "/done";
          myBot.sendMessage(msg, "Update stock is complete");

          // show getStock
        }
      } else {
        myBot.sendMessage(msg, "The bot is currently used by another user");
      }
    }

    delay(1000);
  } while(!msg.text.equals("/done"));

  free(msg)
  free(status)
  free(product)
}

void addProduct(long chatId) {
  // show stock

  myBot.sendTo(chatId, String("type /done to end the sesion"));
  myBot.sendTo(chatId, String("Product name:"));

  String status = "/start"; 
  struct Product product;
  TBMessage msg;

  do {
    if (myBot.getNewMessage(msg)) {
      if (chatId == msg.chatId) {
        msg.text.trim();

        if (msg.text.equals("/done")) {
          myBot.sendMessage(msg, "Cancel add product");
          status = msg.text;

        } else if (status.equals("/start")){
          // get from database
          product = getProduct(msg.text);
          
          // null checking
            // set status to /done if the product already in database
          

          myBot.sendMessage(msg, "Product stock:");
          status = "/quantity";

        } else if (status.equals("/quantity")){
          product.quantity = msg.text.toInt();

          myBot.sendMessage(msg, "Product price:");
          status = "/price";

        } else if (status.equals("/price")){
          product.price = msg.text.toInt();

          myBot.sendMessage(msg, "Processing");
          // store product to database

          status = "/done";
          myBot.sendMessage(msg, "Product successfully added");

          // show getStock
        }
      } else {
        myBot.sendMessage(msg, "The bot is currently used by other user");
      }
    }

    delay(1000);
  } while(!msg.text.equals("/done"));

  free(msg)
  free(status)
  free(product)
}

void addTransaction(long chatId) {
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

  myBot.sendTo(chatId, String("type /done to end the sesion"));
  myBot.sendTo(chatId, String("Transaction date: [dd-mm-yyy]"));

  String status = "/start"; 
  struct Transaction transaction;
  TBMessage msg;

  do {
    if (myBot.getNewMessage(msg)) {
      if (chatId == msg.chatId) {
        msg.text.trim();

        if (msg.text.equals("/done")) {
          myBot.sendMessage(msg, "Cancel transaction");
          status = msg.text;

        } else if (status.equals("/start")){
          int start = 0;
          int index;
          int i = 0;
          String date[3];
          while ((index = msg.text.indexOf('-', start)) != -1) {
            date[i] = msg.text.substring(start, index);
            start = index + 1;
            i++;
          }

          transaction.date.day = date[0].toInt();
          transaction.date.month = date[1].toInt();
          transaction.date.year = date[2].toInt();

          myBot.sendMessage(msg, "Customer name:");
          status = "/customer";
        } else if (status.equals("/cutomer")){
          transaction.customer = msg.text;

          myBot.sendMessage(msg, "Customer order: [name-quantity]");
          status = "/order";
        }else if (status.equals("/order")){

          status = "/verify";
        } else if (status.equals("/verify")){

          // show getStock
          status = "/process";
        } else if (status.equals("/process")){
          myBot.sendMessage(msg, "Processing");
          // store product to database

          status = "/done";
          myBot.sendMessage(msg, "Product successfully added");

          // show getStock
        }
      } else {
        myBot.sendMessage(msg, "The bot is currently used by other user");
      }
    }

    delay(1000);
  } while(!msg.text.equals("/done"));
}

void getMonthlyReport(long chatId){
    myBot.sendTo(chatId, String("Monthly report"));

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

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    displayLCD("wifi","....");

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN3, HIGH);

    //  Telegram setup
    client.setInsecure();
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


      msg.text.trim();
      if (msg.text.equals("/start")) {
        myBot.sendMessage(msg, "Hello, this is RUNO House!");
        char message[] = "--bot commands--\n/getStock\n/updateStock\n/addProduct\n/addTransaction\n/getReport";
        myBot.sendMessage(msg, message);

      } else if(msg.text.equals("/getStock")) {
        getStock(msg);

      } else if(msg.text == "/updateStock") {
        updateProduct(msg.chatId);

      } else if(msg.text.equals("/addProduct")) {
        addProduct(msg.chatId);

      } else if(msg.text.equals("/addTransaction")) {
        addTransaction(msg.chatId);

      } else if(msg.text.equals("/getReport")) {
        getMonthlyReport(msg.chatId);

      } else {
        char message[] = "--bot commands--\n/getStock\n/updateStock\n/addProduct\n/addTransaction\n/getReport";
        myBot.sendMessage(msg, message);

      }

      digitalWrite(LED_PIN, LOW); 
      digitalWrite(LED_PIN2, LOW);
      digitalWrite(LED_PIN3, HIGH);
      msg = {};
      delay(500);    
    }
  }           
}
