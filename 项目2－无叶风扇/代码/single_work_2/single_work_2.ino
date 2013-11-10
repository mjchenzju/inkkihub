/* Grove - LED Bar demo v1
/  by http://www.seeedstudio.com/
/   
*/
#include "LED_Bar.h"
LED_Bar myLED;
unsigned int re_dai_yu_lin_up[]  = {0x00aa,0x000a,0x0000};
unsigned int re_dai_yu_lin_low[] = {0x0000,0X0000,0x0000};
void setup()
{
  // the set_LED_Index set the indivial LED state.
  //for example:the 0b000001101010101, the "1101010101" means:
  //LED10------ON;
  //LED9------ON;
  //LED8------OFF;
  //LED7------ON;
  //LED6------OFF; 
  //LED5------ON;
  //LED4------0FF;
  //LED3------ON;
  //LED2------OFF;
  //LED1------ON;
  // while the first "00000" is reserved.
 //LED.set_LED_Index(0b000001101010101);
 Serial.begin(115200);   //debug serial
  delay(3000);
}
void loop()
{ 
  Serial.println(1);
   myLED.LED_Controler(re_dai_yu_lin_up,re_dai_yu_lin_low);
   delay(3000);
  
}
