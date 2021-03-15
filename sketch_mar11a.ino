#include "twinsGLCD.h"
twinsGLCD glcd(A0, A1, A2, 8, 7, 6, 5, 4, 9);
#define btnNext A6
#define btnPrev A7
#define opto1 A2
#define buzzer A4
#define motor A4
#define reset A7
#define motorOn digitalWrite(motor, HIGH)
#define motorOff digitalWrite(motor, LOW)
#define Reset digitalWrite(reset, HIGH)

char kata[40];
int flagRun = 0;
int flag = 0;
int Ton = 0;
int Toff = 0;
int prevMillis = 0;
unsigned int tick = millis();
int counterBawah, counterAtas, counterCombine;
int flagHasil = 0;
int flagBuzz = 0;
int counter = 0;
int counterPrx = 0;


// float lPress1=0;
 int flagRunExecution;

void setup()
{
  // put your setup code here, to run once:
  glcd.init();
  glcd.setFontSize(2);
  Serial.begin(9600);
  pinMode(buzzer, 1);
  pinMode(motor, 1);
  pinMode(opto1, OUTPUT);
  pinMode(btnNext, INPUT_PULLUP);
  pinMode(btnPrev, INPUT_PULLUP);
  glcd.setCursor(0, 0);
  glcd.setCursor(0, 2);
  glcd.setFontSize(1);
  sprintf(kata, "%5d", (int)Ton);
  glcd.print(kata);

  glcd.setCursor(0, 30);
  glcd.setFontSize(1);
  sprintf(kata, "%5d", (int)Toff);
  glcd.print(kata);
  flagBuzz = 100;
}
// int a;
// int lastPutaran=-1,lastKoma=-1;
// int flagBuzz;
// int flagBuzzer=0;
// int lastRun=0;
// int counterAtas,counterBawah,counterCombine;

int lastState = 10;
int state = 0;
int updateLCD = 0;
void loop()
{
  // put your main code here, to run repeatedly:

  if (state != lastState || updateLCD == 1)
  {
    glcd.setCursor(0, 2);
    glcd.setFontSize(1);
    sprintf(kata, "menu %2d", (int)state);
    glcd.print(kata);
    lastState = state;
    updateLCD = 0;

    if (state == 0)
    {
      glcd.clear();
      int kondisiSensor = analogRead(opto1);
      if (kondisiSensor<100){
        counterPrx++;
        glcd.setCursor(0,30);
        glcd.setFontSize(2);
        sprintf(kata,"%3d",counterPrx);
        glcd.print(kata);
      }
      glcd.setCursor(60, 2);
      glcd.setFontSize(2);
      if (flagRun)
      {
        glcd.print("START");
      }
      else
      {
        glcd.print("STOP");
      }
    }
    
    else if (state == 1)
    {
      glcd.clear();
      glcd.setCursor(0, 2);
      glcd.setFontSize(2);
      sprintf(kata, "%5d", (int)Ton);
      glcd.print(kata);

      glcd.setCursor(0, 30);
      glcd.setFontSize(2);
      sprintf(kata, "%5d", (int)Toff);
      glcd.print(kata);
    }
  }
    
   if(flagRun){
     if(flagRunExecution==1){
        motorOn;
        delay(Ton);
        motorOff;
        delay(Toff);
     }
     else if(flagRunExecution==0){
       motorOff;
     }
   }
    
  if (millis() - tick >= 1)
  {
    tick = millis();
    rutinButton();
    if (flagBuzz > 0)
    {
      digitalWrite(buzzer, 1);
      flagBuzz--;
    }
    else
    {
      digitalWrite(buzzer, 0);
    }
  }
  glcd.rutinDisplay();

  switch (state)
  {
  case 0: //menu standby
    if (flagHasil == 1)
    {
      state = 1;
    }
      else if (flagHasil == 4)
    {
      flagRunExecution^=1;
      updateLCD=1;
    }
    else if (flagHasil == 6)
    {
      counter=0;
      updateLCD=1;
    }
    break;

  case 1: //menu setting
    if (flagHasil == 1)
    {
      state = 0;
    }
    else if (flagHasil == 4)
    {
      Ton+=1000;
      updateLCD=1;
    }
    else if (flagHasil == 6)
    {
      Toff+=1000;
      updateLCD=1;

    }

    break;
  }

  
}

void rutinButton()
{

  if ((btnNextPressed()) && btnPrevPressed())
  {
    counterCombine++;
  }
  else if (btnNextPressed())
  {
    counterAtas++;
  }
  else if (btnPrevPressed())
  {
    counterBawah++;
  }
  else
  {
    if (counterCombine > 1000)
    {
      flagHasil = 1;
    }
    else if (counterCombine > 50)
    {
      flagHasil = 2;
    }
    else if (counterAtas > 1000)
    {
      flagHasil = 3;
    }
    else if (counterAtas > 50)
    {
      flagHasil = 4;
    }
    else if (counterBawah > 1000)
    {
      flagHasil = 5;
    }
    else if (counterBawah > 50)
    {
      flagHasil = 6;
    }
    else if (counterBawah == 0 && counterAtas == 0 && counterCombine == 0)
    {
      flagHasil = 0;
    }

    counterBawah = 0;
    counterCombine = 0;
    counterAtas = 0;
  }

  if (counterAtas > 1000 || counterBawah > 1000 || counterCombine > 1000)
  {
    flagBuzz = 100;
  }
}



unsigned char btnNextPressed()
{
  if (analogRead(btnNext) < 500)
  {
    return 1;
  }
  return (0);
}

unsigned char btnPrevPressed()
{
  if (analogRead(btnPrev) < 500)
  {
    return 1;
  }
  return (0);
}