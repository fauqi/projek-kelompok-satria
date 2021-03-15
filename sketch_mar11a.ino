#include "twinsGLCD.h"
twinsGLCD glcd(A0, A1, A2, 8, 7, 6, 5, 4, 9);
#define btnNext A6
#define btnPrev A7
#define opto1 2
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
// int ton,toff;
// int flagRun=0;

// float lPress1=0;
// int flagRunExecution;

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
      glcd.setCursor(0, 2);
      glcd.setFontSize(2);
      if (flagRun == 1)
      {
        glcd.print("STOP");
      }
      else
      {
        glcd.print("START");
      }
    }

    else if (state == 1)
    {
      glcd.clear();
      glcd.setCursor(0, 2);
      glcd.setFontSize(1);
      sprintf(kata, "%5d", (int)Ton);
      glcd.print(kata);

      glcd.setCursor(0, 30);
      glcd.setFontSize(1);
      sprintf(kata, "%5d", (int)Toff);
      glcd.print(kata);
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
      flagRun^=1;
      updateLCD=1;
    }
    else if (flagHasil == 6)
    {
      
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

  // if(flag==0)
  // {
  //   Serial.println(flagRun);
  //   if(flagRun==1)
  //   Serial.println("motor on");
  //   else
  //   Serial.println("motor off");

  //   if(analogRead(btnNext) <500 && analogRead(btnPrev)<500)
  //   {

  //     int Bcounter=0;
  //     for(;;)
  //     {
  //       if(analogRead(btnNext) >500 || analogRead(btnPrev)>500)break;
  //       Bcounter++;
  //       Serial.println(Bcounter);
  //       if(Bcounter>1000)
  //       {
  //        // Serial.println("flagnya jadi 1");
  //         flag=1;
  //         break;

  //       }
  //       //Serial.println("didalam for");
  //       delay(1);
  //     }
  //   }
  //   if(analogRead(btnNext) <500)
  //   {
  //     if(flagRun==1)flagRun=0;
  //     else flagRun=1;
  //     while(analogRead(btnNext) <500);
  //   }
  // }

  // else if(flag==1)
  // {
  //       if(analogRead(btnNext) <500 && analogRead(btnPrev)<500)
  //   {

  //     int Bcounter=0;
  //     for(;;)
  //     {
  //       if(analogRead(btnNext) >500 || analogRead(btnPrev)>500)break;
  //       Bcounter++;
  //       Serial.println(Bcounter);
  //       if(Bcounter>1000)
  //       {
  //         Serial.println("flagnya jadi 0");
  //         flag=0;
  //         break;

  //       }
  //       //Serial.println("didalam for");
  //       delay(1);
  //     }
  //   }
  //   if(analogRead(btnNext) <500)
  //   {
  //     Ton+=1;
  //     while(analogRead(btnNext) <500);
  //     if(Ton>10)Ton=0;
  //   }
  //    if(analogRead(btnPrev) <500)
  //   {
  //     Toff+=1;
  //     while(analogRead(btnPrev) <500);
  //     if(Toff>10)Toff=0;
  //   }

  //   Serial.println(Ton);
  //   Serial.println(Toff);
  //   //Serial.println("flagnya dah 1");

  // }

  // if(digitalRead(btnNext) == 0 && digitalRead(btnPrev)==0)
  // {
  //   Serial.println(digitalRead(btnNext));
  //   Serial.println(digitalRead(btnPrev));
  //   int i=0;
  //   // for (;;)
  //   // {
  //   //   i++;
  //   //   if (i>2000)
  //   //   {

  //   //     motorNyala();
  //   //     //Serial.println("tunggu");
  //   //     break;
  //   //   }
  //   //   //Serial.println("tunggu");
  //   //  //Serial.println("tunggu");
  //   //  delay(1);
  //   // }

  // }
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

// int settingMode()
// {

// }
// if(lastPutaran!=ton || flagRun!=lastRun){
//   lastPutaran=ton;
//   lastRun=flagRun;
//    glcd.setCursor(0,2);
//    glcd.setFontSize(1);
//    sprintf(kata,"%5d",(int)ton);
//    glcd.print(kata);

//    glcd.setCursor(0,30);
//    glcd.setFontSize(1);
//    sprintf(kata,"%5d",(int)toff);
//    glcd.print(kata);

//    glcd.setCursor(60,5);
//    glcd.setFontSize(1);
//    sprintf(kata,"Reset");

//    glcd.setCursor(60,30);
//    glcd.setFontSize(2);
//    if(flagRun)
//      sprintf(kata,"Start");
//    else{
//      sprintf(kata,"Stop");
//    }
//    glcd.print(kata);
// }

// if ((btnNextPressed) && (btnPrevPressed))
//       {
//       counterCombine++;
//       delay(1);
//       }
//       else if(btnNextPressed){
//       counterAtas++;
//       delay(1);
//       }
//       else if(btnPrevPressed){
//       counterBawah++;
//       delay(1);
//       }
//      else{
//       if(counterCombine>1000){

//       }
//       else if(counterCombine >200){

//       }
//       else if(counterAtas >1000){
//         ton+=1000;
//         if(ton>10000)
//         ton=0;
//       }
//       else if(counterAtas >200){
//       motorOff;
//       flagRun=0;
//       }
//       else if (counterBawah >1000){
//         toff+=1000;
//         if(toff>10000)
//         toff=0;
//       }
//       else if (counterBawah >200){
//       flagRun^=1;
//       if(flagRun){
//       flagRunExecution=1;
// //    buzzerTime=millis();
//       }
//      }
// }

// if(flagRun==1){
//   if(flagRunExecution){
//     motorOn;
//     delay(ton);
//     motorOff;
//     delay(toff);
//   }
//   else{
//     motorOff;
//   }
// }

//       counterAtas=0;
//       counterBawah=0;
//       counterCombine=0;

// }

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
