#include <Arduino.h>
#include "internet.h"
#include <ezTime.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Timezone tempo;
Bounce botaoBoot = Bounce();

int dia = 0;
int mes = 0;
int ano = 0;
int hora = 0; 
int minutos[2] = {0, 0};
int segundos[2] = {0, 0};
int diaSemana = 0;
int diaAno = 0;
int formato24h = true;
bool manha = false;

const char *diaSemanaTexto[] ={
"Domingo",
"segunda",
"Terca",
"Quarta",
"Quinta", 
"sexta",
"sabado"};


const char *mesTexto[] = {
"jan"
"fev"
"mar"
"abr"
"mai"
"jun"
"jul"
"ago"
"set"
"out"
"nov"
"dez"
};
 
 void display(void);

void setup()
{
  Serial.begin(9600);
  botaoBoot.attach(0, INPUT_PULLUP);
  conectaWiFi();
  tempo.setLocation("America/Sao_Paulo");
  waitForSync();

  dia = tempo.day();
  mes = tempo.month();
  ano = tempo.year();
  hora = formato24h ? tempo.hour() : tempo.hourFormat12();
  minutos[1] = tempo.minute();
  segundos[1] = tempo.second();
  diaSemana = tempo.weekday();
  diaAno = tempo.dayOfYear();
  manha = tempo.isAM();

  lcd.init();
  lcd.backlight();
  display();
}
void loop()
{
  botaoBoot.update();

  if( botaoBoot.fell())
  {
formato24h = !formato24h;
  if (!formato24h)
  {
    lcd.setCursor(9,2);
    lcd.printf("%s",manha ? "AM" : "PM");
    lcd.setCursor(0,2);
    lcd.printf("%02d",tempo.hourFormat12());

  }
  else 
  {
    lcd.setCursor(9,2);
    lcd.print("   ");
    lcd.setCursor(0,2);
    lcd.printf("%02d", tempo.hour());
  }
  }
  void checkWiFi();
  segundos[1] = tempo.second();
  minutos[1] = tempo.minute();
  if (segundos[1] != segundos[0])
   
  {
    lcd.setCursor(6, 2);
    lcd.printf("%20d", segundos);
    segundos[0] = segundos[1];
  }

  if (minutos[0] == 59 && minutos[0])
  {

    dia = tempo.day();
    mes = tempo.month();
    ano = tempo.year();
    hora = tempo.hour();
    diaSemana = tempo.weekday();
    diaAno = tempo.dayOfYear();
    manha = tempo.isAM();
    display();
  }
  if (minutos[1] != minutos[0])
    
  {
    lcd.setCursor(3, 2);
    lcd.printf("%02d", minutos[1]);
    minutos[0]= minutos[1];
}
}
void display()
{
  
  
  lcd.setCursor(0, 0);
  lcd.printf("%02d/%s/%04d", dia, mesTexto[mes-1], ano);

  lcd.setCursor(16, 0);
  lcd.printf("%03d", diaAno);

  lcd.setCursor(0, 1);
  lcd.print(diaSemanaTexto[diaSemana - 1]);

  lcd.setCursor(0, 2);
  lcd.printf("%02d:%02d:%02d", hora, minutos[1], segundos[1]);
}
  