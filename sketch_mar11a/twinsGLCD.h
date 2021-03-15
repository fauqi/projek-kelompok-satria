#ifndef twinsGLCD_h
#define twinsGLCD_h

#include "Arduino.h"
#include <avr/pgmspace.h>

class twinsGLCD
{
  public: 
  twinsGLCD(int rs, int rw, int e, int d4, int d5, int d6, int d7 ,int ps8, int rst);
  twinsGLCD(int rs, int rw, int e, int d4, int d5, int d6, int d7, int rst);
  void print(char *a);
  void write(char a);
  
  void setCursor(int x, int y);
  void setFontSize(int size);
  void setBold(int a);
  void clear(void);
  void clearRow(unsigned char row);
  void drawLine(char line);
  void display(void);
  void writeCommand(char c);
  void writeData(char c);
  void data(char c);
  void init(void);
    void draw(char *pict, int x, int y);  
  void rutinDisplay(void);
  void drawProgmem(int a,int x, int y);
  void writeCustom(unsigned char *ini);
  void setRotate(int a);
  void writeBuff(int X, int Y, unsigned char nilai);
  
  private:
  int _xCursor;
  int _yCursor;
  int _fontsize;
  int _bold;
  int _rs;
  int _rw;
  int _en;
  int _d4;
  int _d5;
  int _d6;
  int _d7;
  int _ps8;
  int _rst;
  int isPS8;
  int _rotate;
  
};


#endif
