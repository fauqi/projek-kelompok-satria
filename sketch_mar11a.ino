#include "twinsGLCD.h"
#include "EEPROM.h"

twinsGLCD glcd(A0, A1, A2, 8, 7, 6, 5, 4, 9);
#define btnNext A6
#define btnPrev A7
#define opto1 A3
#define opto2 2
#define buzzer A4
#define motor 12
#define reset A7
#define motorOn digitalWrite(motor, HIGH)
#define motorOff digitalWrite(motor, LOW)
#define Reset digitalWrite(reset, HIGH)

char kata[40];
int flagStepRun = 0;
int bufferTimeRun = 0;
unsigned long tickRun = 0;
int Ton = 0;
int Toff = 0;
int prevMillis = 0;
unsigned long tick = millis();
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
  pinMode(opto1, INPUT_PULLUP);
  pinMode(opto2, INPUT_PULLUP);
  pinMode(btnNext, INPUT_PULLUP);
  pinMode(btnPrev, INPUT_PULLUP);
  glcd.setCursor(0, 0);
  glcd.setCursor(0, 2);
  glcd.setFontSize(1);
  sprintf(kata, "%5d", (int)Ton);
  glcd.print(kata);
  Ton = EEPROM.read(0) * 100;
  Toff = EEPROM.read(1) * 1000;

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
int lastSensor = 0;
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
      glcd.setFontSize(1);
      glcd.setCursor(0, 2);
      sprintf(kata, "Ton :%4d", Ton);
      glcd.print(kata);
      glcd.setCursor(0, 10);
      sprintf(kata, "Toff:%4d", Toff);
      glcd.print(kata);

      glcd.setCursor(0, 30);
      glcd.setFontSize(2);
      sprintf(kata, "%3d", counterPrx);
      glcd.print(kata);
      glcd.setCursor(70, 2);
      glcd.setFontSize(2);

      if (!flagRunExecution)
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
      glcd.setFontSize(1);
      glcd.setCursor(0, 0);
      glcd.print("Ton");

      glcd.setCursor(0, 30);
      glcd.print("Toff");

      glcd.setCursor(0, 10);
      glcd.setFontSize(2);
      sprintf(kata, "%5d", (int)Ton);
      glcd.print(kata);

      glcd.setCursor(0, 40);
      glcd.setFontSize(2);
      sprintf(kata, "%5d", (int)Toff);
      glcd.print(kata);
    }
  }

  if (flagRunExecution == 1)
  {
    if (millis() - tickRun > 100)
    { //100ms

        Serial.println(flagStepRun);

      if (flagStepRun)
      { //on
        motorOn;
        bufferTimeRun -= 100;
      }
      else
      { //off
        motorOff;
        bufferTimeRun -= 100;
      }

      if (bufferTimeRun <= 0)
      {
        flagStepRun ^= 1;
        if (flagStepRun == 1)
        {
          bufferTimeRun = Ton;
        }
        else
        {
          bufferTimeRun = Toff;
        }
      }
      tickRun = millis();
    }
  }
  else{
    motorOff;
  }

  if (millis() - tick >= 1)
  {
    tick = millis();
    rutinButton();
    if (flagHasil != 0)
    {
      Serial.println(flagHasil);
      Serial.println(state);
    }

    // koding buzzer millis
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

  if (state == 0)
  { //menu standby
    if (flagHasil == 1)
    {
      state = 1;
      if (Ton < 0)
        Ton = 0;
      if (Toff < 0)
        Toff = 0;
    }
    else if (flagHasil == 4)
    {
      flagRunExecution ^= 1;
      updateLCD = 1;
    }
    else if (flagHasil == 6)
    {
      counterPrx = 0;
      updateLCD = 1;
    }

    int kondisiSensor = digitalRead(opto1);
    if (lastSensor != kondisiSensor)
    {
      if (kondisiSensor == 1)
      {
        counterPrx++;

        updateLCD = 1;
      }
      lastSensor = kondisiSensor;
    }
  }

  else if (state == 1)
  { //menu setting
    if (flagHasil == 1)
    {
      state = 0;
      EEPROM.write(0, Ton / 100);
      EEPROM.write(1, Toff / 1000);
    }
    else if (flagHasil == 4)
    {
      Ton += 100;
      if (Ton > 4000)
        Ton = 0;
      updateLCD = 1;
    }
    else if (flagHasil == 6)
    {
      Toff += 1000;
      if (Toff > 10000)
      {
        Toff = 0;
      }
      updateLCD = 1;
    }
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