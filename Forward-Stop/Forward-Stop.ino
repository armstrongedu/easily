
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
  }
}
