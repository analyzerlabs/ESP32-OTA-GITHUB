#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include "cert.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "Free_Fonts.h" 
TFT_eSPI tft = TFT_eSPI(); 

#include "variables.h"
#include "server.h"

#define URL_fw_Version "https://raw.githubusercontent.com/analyzerlabs/ESP32-OTA-GITHUB/master/bin_version.txt"
#define URL_fw_Bin "https://raw.githubusercontent.com/analyzerlabs/ESP32-OTA-GITHUB/master/fw.bin"



void connect_wifi();
void firmwareUpdate();
int FirmwareVersionCheck();



void repeatedCall() {
  static int num=0;
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    if (FirmwareVersionCheck()) {
      firmwareUpdate();
    }
  }
  if ((currentMillis - previousMillis_2) >= mini_interval) {
    previousMillis_2 = currentMillis;

   if(WiFi.status() == WL_CONNECTED) 
   {
   }
   else
   {
    connect_wifi();
   }
  }
}


/*void IRAM_ATTR isr(void* arg) {
    Button* s = static_cast<Button*>(arg);
    s->numberKeyPresses += 1;
    s->pressed = true;
}*/
void IRAM_ATTR increment() {
    more.pressed = true;
}
void IRAM_ATTR change() {
    enter.pressed = true;
}
void IRAM_ATTR decrement() {
    less.pressed = true;
}

void IRAM_ATTR isr() {
  button_boot.pressed = true;
}


void setup() {
  tft.init();
  tft.setRotation(3);
  fondo(true);
  pinMode(button_boot.PIN, INPUT);
  pinMode(more.PIN ,INPUT);
  pinMode(enter.PIN,INPUT);
  pinMode(less.PIN  ,INPUT);
  pinMode(1  ,OUTPUT);
  pinMode(3  ,OUTPUT);
  attachInterrupt(button_boot.PIN, isr, RISING);
  attachInterrupt(more.PIN , increment, FALLING);
  attachInterrupt(enter.PIN, change, FALLING);
  attachInterrupt(less.PIN , decrement, FALLING);
  //Serial.begin(115200);
  //Serial.print("Active firmware version:");
  //Serial.println(FirmwareVer);
  pinMode(LED_BUILTIN, OUTPUT);
  tft.setTextFont(7);
  Menu = 0;
  enter.pressed = false;
  connect_wifi();
  server_init();
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, SplashWidth, SplashHeight, SplashScreen);
  repeatedCall();
  delay(5000);
  tft.pushImage(0, 0, RealTimeWidth, RealTimeHeight, RealTimeScreen);
}

void navegador(){
  if(ventana == 0 && enter.pressed == true){
       delay(50);enter.pressed = false;
       ventana = 1;
    }
  else if(ventana == 1 && more.pressed == true){
       delay(50);more.pressed = false;
       Menu ++;
    }  
  else if(ventana == 1 && less.pressed == true){
       delay(50);less.pressed = false;
       Menu --;
    }

  else if(ventana == 1 && enter.pressed == true){
      delay(50);enter.pressed = false;
      if(Menu == 0) ventana = 10;
      else if(Menu == 1) ventana = 11; 
      else if(Menu == 2) ventana = 12;
      else if(Menu == 3) ventana = 13; 
    }
    //*********************************************//
  else if(ventana == 10 && more.pressed == true){
      delay(50);more.pressed = false;
      volumen+=5;
    }
  else if(ventana == 10 && less.pressed == true){
      delay(50);less.pressed = false;
      volumen-=5;
    } 
    //*********************************************//   
  else if(ventana == 11 && more.pressed == true){
      delay(50);more.pressed = false;
      oxigenacion+=1;
    }
  else if(ventana == 11 && less.pressed == true){
      delay(50);less.pressed = false;
      oxigenacion-=1;
    }
    //*********************************************//    
  else if(ventana == 12 && more.pressed == true){
      delay(50);more.pressed = false;
      frecuencia+=1;
    }
  else if(ventana == 12 && less.pressed == true){
      delay(50);less.pressed = false;
      frecuencia-=1;
    }
  //*********************************************//
  else if(ventana == 13 && enter.pressed == true){
      delay(50);enter.pressed = false;
      ventana = 0;
    }
  //*********************************************//
   else if( (ventana == 10 || ventana == 11 || ventana == 12)   && enter.pressed == true){
      delay(50);enter.pressed = false;
      ventana = 1;
    }  
   //*********************************************//
  if(Menu%4 == 0){
      tft.setSwapBytes(true);
      tft.pushImage(0, 0, VolumenOnWidth, VolumenOnHeight, VolumenScreenOn);
      tft.pushImage(240, 0, OxigenacionOnWidth, OxigenacionOnHeight, OxigenacionScreenOff);
      tft.pushImage(0, 160, FrecuenciaOnWidth, FrecuenciaOnHeight, FrecuenciaScreenOff);
      tft.pushImage(240, 160, AtrasOnWidth, AtrasOnHeight, AtrasScreenOff);
  }
  else if(Menu%4 == 1){
      tft.setSwapBytes(true);
      tft.pushImage(0, 0, VolumenOnWidth, VolumenOnHeight, VolumenScreenOff);
      tft.pushImage(240, 0, OxigenacionOnWidth, OxigenacionOnHeight, OxigenacionScreenOn);
      tft.pushImage(0, 160, FrecuenciaOnWidth, FrecuenciaOnHeight, FrecuenciaScreenOff);
      tft.pushImage(240, 160, AtrasOnWidth, AtrasOnHeight, AtrasScreenOff);
  } 
  else if(Menu%4 == 2){
      tft.setSwapBytes(true);
      tft.pushImage(0, 0, VolumenOnWidth, VolumenOnHeight, VolumenScreenOff);
      tft.pushImage(240, 0, OxigenacionOnWidth, OxigenacionOnHeight, OxigenacionScreenOff);
      tft.pushImage(0, 160, FrecuenciaOnWidth, FrecuenciaOnHeight, FrecuenciaScreenOn);
      tft.pushImage(240, 160, AtrasOnWidth, AtrasOnHeight, AtrasScreenOff);
  }
  else if(Menu%4 == 3){
      tft.setSwapBytes(true);
     tft.pushImage(0, 0, VolumenOnWidth, VolumenOnHeight, VolumenScreenOff);
      tft.pushImage(240, 0, OxigenacionOnWidth, OxigenacionOnHeight, OxigenacionScreenOff);
      tft.pushImage(0, 160, FrecuenciaOnWidth, FrecuenciaOnHeight, FrecuenciaScreenOff);
      tft.pushImage(240, 160, AtrasOnWidth, AtrasOnHeight, AtrasScreenOn);
  }
}
void loop(){
  if (button_boot.pressed) { //to connect wifi via Android esp touch app 
    //Serial.println("Firmware update Starting..");
    firmwareUpdate();
    button_boot.pressed = false;
  }
  navegador();  
}

void connect_wifi() {
  //Serial.println("Waiting for WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

}


void firmwareUpdate(void) {
  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  httpUpdate.setLedPin(LED_BUILTIN, LOW);
  t_httpUpdate_return ret = httpUpdate.update(client, URL_fw_Bin);

  switch (ret) {
  case HTTP_UPDATE_FAILED:
    //Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
    break;

  case HTTP_UPDATE_NO_UPDATES:
    //Serial.println("HTTP_UPDATE_NO_UPDATES");
    break;

  case HTTP_UPDATE_OK:
    //Serial.println("HTTP_UPDATE_OK");
    break;
  }
}
int FirmwareVersionCheck(void) {
  String payload;
  int httpCode;
  String fwurl = "";
  fwurl += URL_fw_Version;
  fwurl += "?";
  fwurl += String(rand());
  //Serial.println(fwurl);
  WiFiClientSecure * client = new WiFiClientSecure;

  if (client) 
  {
    client -> setCACert(rootCACertificate);

    // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
    HTTPClient https;

    if (https.begin( * client, fwurl)) 
    { // HTTPS      
      //Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      delay(100);
      httpCode = https.GET();
      delay(100);
      if (httpCode == HTTP_CODE_OK) // if version received
      {
        payload = https.getString(); // save received version
      } else {
        //Serial.print("error in downloading version file:");
        //Serial.println(httpCode);
      }
      https.end();
    }
    delete client;
  }
      
  if (httpCode == HTTP_CODE_OK) // if version received
  {
    payload.trim();
    if (payload.equals(FirmwareVer)) {
      //Serial.printf("\nDevice already on latest firmware version:%s\n", FirmwareVer);
      return 0;
    } 
    else 
    {
      //Serial.println(payload);
      //Serial.println("New firmware detected");
      return 1;
    }
  } 
  return 0;  
}
