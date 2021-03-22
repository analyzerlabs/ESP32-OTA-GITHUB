
unsigned long previousMillis = 0;
unsigned long previousMillis_2 = 0;
const long interval = 600000;
const long mini_interval = 10000;
#include "imagenes.h"
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
int volumen=400;
int frecuencia = 15;
int Menu=0;
int ventana=0;
int oxigenacion = 85;
bool refresh = true;
struct Button {
  const uint8_t PIN;
  bool pressed;
};

Button button_boot = {
  0,
  false
};
unsigned long int t1,t0;
int t_i_e[2]={1250,1500};
int flag_angulo=0;

Button more =  {14, false};
Button enter = {27, false};
Button less =  {26, false};

String FirmwareVer = {
  "6.0"
};


int calculoFrecuencia(){
  int aux = int(60000.00/frecuencia);
  return (aux);  
}
int calculoVolumen(){
  int aux = int(volumen*178.00/600);
  return (aux);  
}  


int contador_pasos = 0 ;
int r = 1 ; 
int direccion = 1;
int t_step=0;

void Respira(){
  contador_pasos = contador_pasos + r;
  if(contador_pasos >= volumen  || contador_pasos <=0){
      direccion = 1 - direccion;
      r = r *(-1);
      digitalWrite(3,direccion);     
    }
  t_step = 60000/frecuencia;
  t_step = t_step / (4* volumen);
  digitalWrite(1,HIGH);
  delay(t_step);
  digitalWrite(1,LOW);
  delay(t_step);
 }
 
