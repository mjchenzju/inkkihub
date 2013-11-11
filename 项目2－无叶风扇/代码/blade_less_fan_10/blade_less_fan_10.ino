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

unsigned int re_dai_yu_lin_data[] = {0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa};
//unsigned int re_dai_yu_lin_data[] = {0x0000,0x00aa,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0X0012,0x00aa,   0x0000,0x00aa,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0X0012,0x00aa};
unsigned int ha_er_bin_data[] =     {0x0012,0x0000,0x0031, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0X0000,0x0012,   0x0012,0x0000,0x0031, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0X0000,0x0012};
unsigned int cao_yuan_data[] =      {0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0002,0x00aa, 0x0000,0X0023,0x0011, 0x0000,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0002,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0000,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x0000,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0002,0x00aa, 0x0000,0X0023,0x0011, 0x0000,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0002,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0000,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x0000,0x00aa};
unsigned int ma_er_dai_fu_data[] =  {0x0012,0X0000,0x0000, 0x00aa,0X0023,0x0000, 0x0000,0x0012,0x0012, 0x0000,0x0012,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0000,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0000,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0001,   0x0012,0X0000,0x0010, 0x00a0,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0000,0X0000,0x0012, 0x00aa,0X0023,0x0000, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0000,   0x0012,0X0000,0x0000, 0x00aa,0X0023,0x0000, 0x0000,0x0012,0x0012, 0x0000,0x0012,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0000,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0000,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0001,   0x0012,0X0000,0x0010, 0x00a0,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0000,0X0000,0x0012, 0x00aa,0X0023,0x0000, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0000};

//--------------------------------------------------------------------------

boolean BeginToJudgePressState = false;
int JudgePressCount = 0;
int Work_Mode = 0; //0 = not work; 1 = first run after work; 2 ＝ work
int Display_Command = 1;
int Display_State = 0;

LED_Bar myLED;
Timer t;

void setup()
{
    myLED.CLEAN_LED();

    Serial.begin(115200);   //debug serial
    delay(100);
    Serial.println("blade less fan simple v.7");
    delay(100);
    Serial1.begin(115200);  //IR Serial
    delay(100);
    Serial2.begin(115200);  //wifi Serial
    delay(100);
    Serial3.begin(115200);  //Voice Serial
    delay(100);
    
    
    attachInterrupt(0, BlockingStateChange, HIGH); //0 is digital 2，

    t.every(100, loop50ms,(void*)1);

    long_press_time = long_press_time*10-5;
    
    Serial.println("init succ");
    
}

void loop50ms(void* context){
  JudgePressState();
  
  if (Work_Mode != 0){
    UpdateDisplayInfo(1);
  }  
  if (Work_Mode == 1){
    //this is the first run after change to work mode
    //[todo]play the voice
    Work_Mode = 2; 
  }
  else if(Work_Mode == 0){
    //close the led module and Led screen
    UpdateDisplayInfo(0);
    //[todo]close everything

  }

}

void loop()
{ 
  t.update();
  
  while (Serial1.available() > 0){
    char temp =char(Serial1.read());
    if (Work_Mode != 0){
      process_Serial_Command(temp);
    }
    else if (temp == 'e'){
      execute_Command(enter_key);
    }
  }
  // Second Prat ： Receive the Serial2 value from wifi module
  while (Serial2.available() > 0){
    char temp =char(Serial2.read());
    if (Work_Mode != 0){
      process_Serial_Command(temp);
    }
    else if (temp == 'e'){
      execute_Command(enter_key);
    }
  }

  while (Serial.available() > 0){
    char temp =char(Serial.read());
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
    case '5':{
      execute_Command(five_key);
      break;
    }
    case '6':{
      execute_Command(six_key);
      break;
    }
    case '7':{
      execute_Command(seven_key);
      break;
    }
    case '8':{
      execute_Command(eight_key);
      break;
    }
    case '9':{
      execute_Command(nine_key);
      break;
    }
    case '0':{
      execute_Command(zero_key);
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
      myLED.LED_Controler_by_raw_data(re_dai_yu_lin_data);
      break;
    }
    case two_key:{
      myLED.LED_Controler_by_raw_data(ha_er_bin_data);
      break;
    }
    case three_key:{      
      myLED.LED_Controler_by_raw_data(cao_yuan_data);
      break;
    }
    case four_key:{
      myLED.LED_Controler_by_raw_data(ma_er_dai_fu_data);
      break;
    }
    case five_key:{
      myLED.LED_Controler(ha_er_bin_up,ha_er_bin_low);
      break;
    }
    case six_key:{
      Serial3.print(6);
      break;
    }
    case seven_key:{
      Serial3.print(7);
      break;
    }
    case eight_key:{
      myLED.LED_Controler(ha_er_bin_up,ha_er_bin_low);
      break;
    }
    case nine_key:{
      myLED.LED_Controler(ha_er_bin_up,ha_er_bin_low);
      break;
    }
    case zero_key:{
      myLED.LED_Controler(ha_er_bin_up,ha_er_bin_low);
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

void UpdateDisplayInfo(int _com){
  if (_com == 0){
     myLED.CLEAN_LED();
     Display_State = 0;
  }
  else{
    if (Display_State == 0){
      execute_Command(Display_Command);
      Display_State = 1;
    }
  }
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

