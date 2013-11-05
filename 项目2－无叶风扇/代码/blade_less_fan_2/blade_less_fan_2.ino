/* a blade less fan simple v.2

v1 2013.11.4 add led controler:
    myLED.LED_Controler()
    myLED.CLEAN_LED()
    
v2 2013.11.4 add IR Function
*/

#include "LED_Bar.h"
#include "Less_Fan_Function.h"

#include <IRremote.h>
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

LED_Bar myLED;
Less_Fan_Function myFunction;
void setup()
{
    Serial.begin(115200);
    Serial.println("blade less fan simple v.2");
    
    irrecv.enableIRIn(); // Start the receiver
}

void loop()
{ 
  // Receive the IR value
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    //myFunction.dump(&results);
    execute_Command(results.value);
    irrecv.resume(); 
  }
}

void execute_Command(int command){
  switch(command){
    case one_key:{
      unsigned int up[] = {0x00aa,0x0000,0x0000};
      unsigned int low[] = {0x0000,0X0000,0x0000};
      myLED.LED_Controler(up,low);
      break;
    }
    case two_key:{
      unsigned int up[] = {0x0000,0x00aa,0x0000};
      unsigned int low[] = {0x0000,0X0000,0x0000};
      myLED.LED_Controler(up,low);
      break;
    }
    case three_key:{
      unsigned int up[] = {0x0000,0x0000,0x00aa};
      unsigned int low[] = {0x0000,0X0000,0x0000};
      myLED.LED_Controler(up,low);
      break;
    }
    case four_key:{
      unsigned char a; 
      for (a=0;a<155;a = a +5){
        unsigned int up[] = {0x0000,0x00aa-a,0x0000};
        unsigned int low[] = {0x0000,0X0000,0x0000};
        myLED.LED_Controler(up,low);
        delay(15);
      }
      break;
    }
    case remote_down:{
      myLED.CLEAN_LED();
      break;
    }
  }
}
