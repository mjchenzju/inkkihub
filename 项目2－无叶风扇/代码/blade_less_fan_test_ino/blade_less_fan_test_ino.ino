/* a blade less fan simple v.test

v1 2013.11.4 add led controler:
    myLED.LED_Controler()
    myLED.CLEAN_LED()
    
v2 2013.11.4 add IR Function
*/
#include "LED_Bar.h"
#include "Timer.h"

//Modify the parameters in this place---------------------------------------
float long_press_time = 3; //long press time 3s ,PS:long_press_time should greater than 0.5s
int clock_frequency = 50; // 50ms to refresh
unsigned int re_dai_yu_lin_up[]  = {0x00aa,0x000a,0x0000};
unsigned int re_dai_yu_lin_low[] = {0x0000,0X0000,0x0000};
unsigned int ha_er_bin_up[] = {0x0000,0x00aa,0x0000};
unsigned int ha_er_bin_low[] = {0x0000,0X0000,0x0000};
unsigned int cao_yuan_up[] = {0x000a,0x0000,0x00aa};
unsigned int cao_yuan_low[] = {0x0000,0X0000,0x0000};
unsigned int ma_er_dai_fu_up[] = {0x000a,0x000a,0x00aa};
unsigned int ma_er_dai_fu_low[] = {0x0000,0X0000,0x0000};
//--------------------------------------------------------------------------

boolean BeginToJudgePressState = false;
int JudgePressCount = 0;
int Work_Mode = 0; //0 = not work; 1 = first run after work; 2 ＝ work
int Display_Command = 1;

LED_Bar myLED;
Timer t;

void setup()
{
    myLED.CLEAN_LED();

    Serial.begin(115200);   //debug serial
    delay(100);
    Serial.println("blade less fan simple v.test");
    delay(100);
    Serial2.begin(115200);  //wifi Serial
    delay(100);
    
    attachInterrupt(0, BlockingStateChange, HIGH); //0 is digital 2，
    
    t.every(50, loop50ms,(void*)1);

    long_press_time = long_press_time*20-10;
}

void loop50ms(void* context){
  JudgePressState();
  
  if (Work_Mode != 0){
    UpdateDisplayInfo();
  }  
  if (Work_Mode == 1){
    //this is the first run after change to work mode
    //[todo]play the voice
    Work_Mode = 2; 
  }
  else if(Work_Mode == 0){
    //close the led module and Led screen
    myLED.CLEAN_LED();
    //[todo]close everything

  }

}

void loop()
{ 
  t.update();
  
  // Second Prat ： Receive the Serial2 value from wifi module
  while (Serial2.available() > 0){
    char temp =char(Serial2.read());
    //Serial.print(char(temp));
    if (Work_Mode != 0){
      process_Serial_Command(temp);
    }
    else if (temp == 'e'){
      execute_Command(enter_key);
    }
  }
  
  while (Serial.available() > 0){
    char temp =char(Serial.read());
    //Serial.print(char(temp));
    if (Work_Mode != 0){
      process_Serial_Command(temp);
    }
    else if (temp == 'e'){
      execute_Command(enter_key);
    }
  }
  
}

/*-------------
  run process_Serial_Command(char serial_command) when receive a Serial2 value from wifi module
--------------*/

void process_Serial_Command(char serial_command){
  switch(serial_command){
    case '1':{
      execute_Command(one_key);
      break;
    }
    case '2':{
      execute_Command(two_key);
      break;
    }
    case '3':{
      execute_Command(three_key);
      break;
    }
    case '4':{
      execute_Command(four_key);
      break;
    }
    case 'e':{
      execute_Command(enter_key);
      break;
    }
    case 'u':{
      execute_Command(remote_up);
      break;
    }
    case 'd':{
      execute_Command(remote_down);
      break;
    }
    case 'l':{
      execute_Command(remote_left);
      break;
    }
    case 'r':{
      execute_Command(remote_right);
      break;
    }
  }
}

/*-------------
  run execute_Command(int command) when receive a IR value
--------------*/

void execute_Command(int command){
  Display_Command = command;
  switch(command){
    case one_key:{
      myLED.LED_Controler(re_dai_yu_lin_up,re_dai_yu_lin_low);
      break;
    }
    case two_key:{
      myLED.LED_Controler(ha_er_bin_up,ha_er_bin_low);
      break;
    }
    case three_key:{      
      myLED.LED_Controler(cao_yuan_up,cao_yuan_low);
      break;
    }
    case four_key:{
      myLED.LED_Controler(ma_er_dai_fu_up,ma_er_dai_fu_low);
      break;
    }
    case enter_key:{
      ChangeDeviceState();
      break;
    }
    case remote_up:{
      //Raise the temperature
      myLED.set_LED_Index(0b000100100100100);
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

void JudgePressState(){
    if (BeginToJudgePressState == true){
        if (digitalRead(2)==0){
            //begin to judge long press by count
            if (JudgePressCount < long_press_time){ //long press time 2.5s
                JudgePressCount = JudgePressCount + 1;
            }
            else{
                //A long press, begin to process
                Serial.println("long press, change the device state");
                ChangeDeviceState();
                JudgePressCount = 0;
                BeginToJudgePressState = false;
            }
        }
        else{
            //A short press, begin to process
            Serial.println("short press");
            
            JudgePressCount = 0;
            BeginToJudgePressState = false;
        }
    }
}

void UpdateDisplayInfo(){
  execute_Command(Display_Command);
}


/*-------------
  run BlockingStateChange() when Infrared blocking sensor's state changed
--------------*/

void BlockingStateChange(){
  Serial.println("BlockingStateChange");
  if (digitalRead(2)==0){
        BeginToJudgePressState = true;
  }
}

void ChangeDeviceState(){
  Serial.println("ChangeDeviceState");
  if (Work_Mode == 0){
    Work_Mode = 1;
    Display_Command = one_key;
  }
  else{
    Work_Mode = 0;
  }
}
