/* a blade less fan simple v.1

2013.11.4 add led controler:
    myLED.LED_Controler()
    myLED.CLEAN_LED()
*/

#include "LED_Bar.h"
LED_Bar myLED;

void setup()
{
    Serial.begin(115200);
    Serial.println("blade less fan simple v.1");
}

void loop()
{ 
  while(1)
  {
     // the set_LED_Index set the indivial LED state.
     unsigned int up[] = {0x00AF,0x0A00,0x0A00};
     unsigned int low[] = {0x0000,0X0000,0x0000};
     myLED.LED_Controler(up,low);
  
     delay(1000);
     myLED.CLEAN_LED();
     delay(1000);
    
  }
}
