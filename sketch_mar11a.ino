#include "twinsGLCD.h"
twinsGLCD glcd(A0,A1,A2,8,7,6,5,4,9);
#define btnNext A6
#define btnPrev A7
#define opto1   2
#define buzzer  A4
#define motor A4
#define reset A7
#define motorOn  digitalWrite(motor,HIGH)
#define motorOff digitalWrite(motor,LOW)
#define Reset    digitalWrite(reset,HIGH)
char kata [40];
int ton,toff;
int flagRun=0;

float lPress1=0;
int flagRunExecution;
  
void setup() {
  // put your setup code here, to run once:
glcd.init();
glcd.setFontSize(2);
Serial.begin(9600);
pinMode(buzzer,1);
 pinMode(motor,1);
 pinMode(opto1,OUTPUT);
 pinMode(btnNext,INPUT_PULLUP);
 pinMode(btnPrev,INPUT_PULLUP);
 glcd.setCursor(0,0);
}
int a;
int lastPutaran=-1,lastKoma=-1;
int flagBuzz;
int flagBuzzer=0;
int lastRun=0;
int counterAtas,counterBawah,counterCombine;
void loop() {
  // put your main code here, to run repeatedly:
glcd.rutinDisplay();

if(lastPutaran!=ton || flagRun!=lastRun){
  lastPutaran=ton;
  lastRun=flagRun;
   glcd.setCursor(0,2);
   glcd.setFontSize(1);
   sprintf(kata,"%5d",(int)ton);
   glcd.print(kata);
   
   glcd.setCursor(0,30);
   glcd.setFontSize(1);
   sprintf(kata,"%5d",(int)toff);
   glcd.print(kata);
   
   glcd.setCursor(60,5);
   glcd.setFontSize(1);
   sprintf(kata,"Reset");
   
   glcd.setCursor(60,30);
   glcd.setFontSize(2);
   if(flagRun)
     sprintf(kata,"Start");
   else{
     sprintf(kata,"Stop");
   }   
   glcd.print(kata);
}

if ((btnNextPressed) && (btnPrevPressed))
      {
      counterCombine++;
      delay(1);
      }
      else if(btnNextPressed){
      counterAtas++;
      delay(1);
      }
      else if(btnPrevPressed){
      counterBawah++;
      delay(1);
      }
     else{
      if(counterCombine>1000){
         
      }
      else if(counterCombine >200){
         
      }
      else if(counterAtas >1000){
        ton+=1000;
        if(ton>10000)
        ton=0;
      }
      else if(counterAtas >200){
      motorOff;
      flagRun=0;  
      }
      else if (counterBawah >1000){
        toff+=1000;
        if(toff>10000)
        toff=0;
      }
      else if (counterBawah >200){
      flagRun^=1;
      if(flagRun){
      flagRunExecution=1;
//    buzzerTime=millis(); 
      }
     }
}

if(flagRun==1){
  if(flagRunExecution){
    motorOn;
    delay(ton);
    motorOff;
    delay(toff);
  }
  else{
    motorOff;
  }
}

      counterAtas=0;
      counterBawah=0;
      counterCombine=0;

}



unsigned char btnNextPressed(){
  if(analogRead(btnNext)<200){
      lPress1=0;
      while(analogRead(btnNext)<200){
        lPress1++;
        delay(1);
        if(lPress1>1000){ break; } 
        if(analogRead(btnPrev)<200) return(3);
      }
      if(lPress1>1000)return(2);
      else {return(1);}
   }
  return(0);  
}


unsigned char btnPrevPressed(){
  if(analogRead(btnPrev)<200){
      lPress1=0;
      while(analogRead(btnPrev)<200){
        lPress1++;
        delay(1);
        if(lPress1>1000){ break; } 
        if(analogRead(btnNext)<200)return(3);
      }
      if(lPress1>1000)return(2);
      else {return(1);}
  }
  return(0);  
}
