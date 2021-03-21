unsigned long previousMillis = 0;
unsigned long previousMillis_2 = 0;
const long interval = 600000;
const long mini_interval = 10000;
#include "FONDO.h"
const char* ssid = "MIGUEL";
const char* password = "20120415H";

const int output = 2;
const char* PARAM_INPUT = "value";
AsyncWebServer server(80);
String sliderValue;
int LED_BUILTIN = 2;
boolean paso=true;
int angulo_subida=0;
int w=480,h=320;
int volumen=300;
int frecuencia = 20;
int opcion=0;
bool refresh = true;
struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button_boot = {
  0,
  0,
  false
};
unsigned long int t1,t0;
int angulos[2]={0,170};
int t_i_e[2]={1250,1500};
int flag_angulo=0;

Button more =  {14 , 0, false};
Button enter = {27,  0, false};
Button less =  {26, 0, false};

String FirmwareVer = {
  "5.0"
};

void fondo(bool r){
    if(r){
      t1= millis();
      t0 = millis();
      tft.setSwapBytes(true);
      tft.pushImage(0, 0, fondoWidth, fondoHeight, fondo1);
     }
  }

void drawPulmon(){ 
  tft.drawLine(30, 10, 30, 35, TFT_BLACK);
  tft.drawLine(40, 10, 40, 35, TFT_BLACK);
  tft.drawLine(30, 35, 20, 50, TFT_BLACK);
  tft.drawLine(40, 35, 50, 50, TFT_BLACK);
}
int calculoFrecuencia(){
  int aux = int(60000.00/frecuencia);
  return (aux);  
}
int calculoVolumen(){
  int aux = int(volumen*178.00/600);
  return (aux);  
}  
void principal(){
    //Serial.println("opcion principal");
    fondo(refresh);
    if(refresh){
      tft.setCursor(w/2-60, h/2-90);
      tft.setTextColor(TFT_BLACK,TFT_WHITE);
      tft.setTextDatum(TC_DATUM); // Centre text on x,y position

      int xpos = tft.width() / 2; // Half the screen width
      int ypos = 70;
    /*
      tft.setFreeFont(FSB24);                              // Select the font
      tft.drawString("VENTILADOR", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
      ypos += tft.fontHeight(GFXFF);
      tft.drawString("MECANICO DE", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
      ypos += tft.fontHeight(GFXFF);
      tft.drawString("EMERGENCIAS", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
      ypos += tft.fontHeight(GFXFF);
      tft.setFreeFont(FSB9);  
      tft.drawString("Soporte : miguelquispecastro@uni.com", 20, 300, GFXFF);
      tft.pushImage(0, 0, pulmonWidth, pulmonHeight, pulmon);*/
    }
    refresh = false;

      tft.fillRect(400,250,50,30,TFT_MAGENTA);
      tft.fillTriangle(450,230,475,265,450,300,TFT_MAGENTA);
  }

void volume(){
    //Serial.println("opcion volumen");
    fondo(refresh);
    if(refresh){
        tft.setTextColor(TFT_BLACK,TFT_WHITE);
        tft.setTextDatum(TC_DATUM); // Centre text on x,y position
  
        int xpos = tft.width() / 2; // Half the screen width
        int ypos = 70;
      
        tft.setFreeFont(FSB24);                              // Select the font
        tft.drawString("Volumen", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
        tft.drawString( String(volumen), xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
        drawPulmon();
    }
    refresh = false;
    if(more.pressed){
      delay(50);
      more.pressed = false;
      volumen+=5;
      tft.setTextColor(TFT_BLACK,TFT_WHITE);
        tft.setTextDatum(TC_DATUM); // Centre text on x,y position
  
        int xpos = tft.width() / 2; // Half the screen width
        int ypos = 70;
      
        tft.setFreeFont(FSB24);                              // Select the font
        tft.drawString("Volumen", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
        tft.drawString( String(volumen), xpos, ypos, GFXFF); 
    }
    else if(less.pressed){
      delay(50);
      less.pressed = false;
      volumen-=5;
      tft.setTextColor(TFT_BLACK,TFT_WHITE);
        tft.setTextDatum(TC_DATUM); // Centre text on x,y position
  
        int xpos = tft.width() / 2; // Half the screen width
        int ypos = 70;
      
        tft.setFreeFont(FSB24);                              // Select the font
        tft.drawString("Volumen", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
        tft.drawString( String(volumen), xpos, ypos, GFXFF); 
    }
    
    if(volumen >= 700) volumen = 700;
    else if(volumen <=100) volumen = 100;
    angulos[1]=calculoVolumen();
  }
  

  
void frecuency(){
    //Serial.println("opcion frecuencia");
    fondo(refresh);   
    if(refresh){
        tft.setTextColor(TFT_BLACK,TFT_WHITE);
        tft.setTextDatum(TC_DATUM); // Centre text on x,y position
  
        int xpos = tft.width() / 2; // Half the screen width
        int ypos = 70;
      
        tft.setFreeFont(FSB24);                              // Select the font
        tft.drawString("Frecuencia", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
        tft.drawString( String(frecuencia), xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
    }
    refresh = false;
    //aqui mas codigo
    if(more.pressed){
      delay(50);
      more.pressed = false;
      frecuencia+=1;
      tft.setTextColor(TFT_BLACK,TFT_WHITE);
        tft.setTextDatum(TC_DATUM); // Centre text on x,y position
  
        int xpos = tft.width() / 2; // Half the screen width
        int ypos = 70;
      
        tft.setFreeFont(FSB24);                              // Select the font
        tft.drawString("Frecuencia", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
        tft.drawString( String(frecuencia), xpos, ypos, GFXFF); 
    }
    else if(less.pressed){
      delay(50);
      less.pressed = false;
      frecuencia-=1;
      tft.setTextColor(TFT_BLACK,TFT_WHITE);
        tft.setTextDatum(TC_DATUM); // Centre text on x,y position
  
        int xpos = tft.width() / 2; // Half the screen width
        int ypos = 70;
      
        tft.setFreeFont(FSB24);                              // Select the font
        tft.drawString("Frecuencia", xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
        tft.drawString( String(frecuencia), xpos, ypos, GFXFF); 
    }
    t_i_e[0]=calculoFrecuencia()-t_i_e[1];
    //Serial.println(t_i_e[0]);
  }


int contador_pasos = 0 ;
int r = 1 ; 
int direccion = 0;
void Respira(){
  if(contador_pasos >= 200  || contador_pasos <=0){
      direccion = 1 - direccion;
      digitalWrite(3,direccion);    
      r = r *(-1);
    }
  contador_pasos = contador_pasos + r;
  digitalWrite(1,HIGH);
  delay(2);
  digitalWrite(1,LOW);
  delay(2);
 }
 void secundario(){
    //fondo(refresh);
    refresh = false;
    Respira();
    unsigned long currentMillis = millis();
  
    /*if(currentMillis - previousMillis >= 1500) {
     // Check WiFi connection status
        
      if(WiFi.status()== WL_CONNECTED ){
        temperature = httpGETRequest(serverNameTemp);
        Respira();
        humidity = httpGETRequest(serverNameHumi);
        Respira();
        if(humidity.toInt()<90){
            tft.fillRect(0,0,w,h,TFT_RED);
            tft.setTextColor(TFT_WHITE,TFT_RED);
        }
        else if(humidity.toInt()>=90){
          tft.fillRect(0,0,w,h,TFT_WHITE);
          tft.setTextColor(TFT_BLACK,TFT_WHITE);
        }
        
        
        tft.setTextDatum(TC_DATUM); // Centre text on x,y position
  
        int xpos = tft.width() / 2; // Half the screen width
        int ypos = 70;
      
        tft.setFreeFont(FSB24);                              // Select the font
        tft.drawString("heartBeat: ", 30, ypos, GFXFF);
        tft.drawString(temperature, xpos, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        ypos += tft.fontHeight(GFXFF);
        tft.drawString("SP 02: ", 30, ypos, GFXFF);  // Draw the text string in the selected GFX free font
        tft.drawString(humidity, xpos, ypos, GFXFF); 
         */
        previousMillis = currentMillis;
      //}
    //}
  }  
