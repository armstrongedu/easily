
#include "Armstrong.h"
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if(hc.dist() > 30){
    Forward(255);
  }else{
    Stop();
   delay(60);
   Backward(100);
   delay(2000);
   rotateRight(255); 
    
  }
}

