
#include "IRremote.h"

#define remote_up 16736925
#define remote_down 16754775 
#define remote_left 16720605
#define remote_right 16761405
#define enter_key 16712445
#define one_key 16738455 
#define two_key 16750695
#define three_key 16756815
#define four_key 16724175 
#define five_key 16718055
#define six_key 16743045
#define seven_key 16716015
#define eight_key 16726215 
#define nine_key 16734885
#define zero_key 16730805

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

boolean BeginToJudgePressState = false;

// init the function--------
decode_results results;

void setup()
{
    Serial.begin(115200);   //debug serial
    delay(100);
    //Serial.println("IR Controler");
    delay(100);

    irrecv.enableIRIn(); // Start the receiver
}


void loop()
{ 
  // First Part : Receive the IR value
  if (irrecv.decode(&results)) {
    execute_Command(results.value);
    irrecv.resume(); 
  }
}

/*-------------
  run execute_Command(int command) when receive a IR value
--------------*/

void execute_Command(int command){
  switch(command){
    case one_key:{
      Serial.print('1');
      break;
    }
    case two_key:{
      Serial.print('2');
      break;
    }
    case three_key:{      
      Serial.print('3');
      break;
    }
    case four_key:{
      Serial.print('4');
      break;
    }
    case enter_key:{
      Serial.print('e');
      break;
    }
    case remote_up:{
      //Raise the temperature
      Serial.print('u');
      break;
    }
    case remote_down:{
      //Reduce the temperature
      break;
    }
    case remote_left:{
      //Raise the wind speed
      break;
    }
    case remote_right:{
      //Reduce the wind speed
      break;
    }
  }
}
