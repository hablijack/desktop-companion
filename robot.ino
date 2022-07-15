#include <Wire.h>
#include "SH1106Wire.h" 
#include "eyes.h"

SH1106Wire display(0x3c, SDA, SCL); 

void setup() {
  Serial.begin(9600);
  Serial.println("Booting");
  display.init();
  display.setContrast(255);
  display.flipScreenVertically();
}

int xp=16;
int mood=1;
    //0 = happy
    //1 = default
    //2 = annoyed
    //3 = angry
    //4 = frustrated
    //5 = sad
  

void loop() {
  int n;
  static int xd=0;
  static int wait=0;
  static int step=0;
  int x1,x2;
  if (wait>0) {
    wait--;
    delay(1);
  } else {
    x1= xd+ (xp>16? (16+2*(xp-16)):xp);
    x2=46+xd+ (xp<16? (-16+(xp*2))  :xp);
    switch (step){
      case 0:
       display.clear();
       if (xp<6) { 
         display.drawXbm(x1, 8, 32, 32, peyes[mood][2][0]);
         display.drawXbm(x2, 8, 32, 32, peyes[mood][1][1]);
       } else if (xp<26) {
         display.drawXbm(x1, 8, 32, 32, peyes[mood][0][0]);
         display.drawXbm(x2, 8, 32, 32, peyes[mood][0][1]);   
       } else {
         display.drawXbm(x1, 8, 32, 32, peyes[mood][1][0]); 
         display.drawXbm(x2, 8, 32, 32, peyes[mood][2][1]);
       }
       display.display();
       wait=random(250, 1000);
       n=random(0,7);
       if (n==6) {
          step=1;
       } else {
          step=2;
       }
       break;
      case 1:
       display.clear();
       display.drawXbm(x1, 8, 32, 32, wink_eye);
       display.drawXbm(x2, 8, 32, 32, wink_eye);
       display.display();
       wait=100;
       step=0;
       break;
      case 2:
       n=random(0,10);
       if (n<5) xd--;
       if (n>5) xd++;
       if (xd<-4) xd=-3;
       if (xd>4) xd=3; 
       wait=0;
       step=0;
       break;
    }
  }
  if (n==2) xp=(xp<=0?0:xp-1); 
  if (n==4) xp=(xp>=32?32:xp+1);
}
