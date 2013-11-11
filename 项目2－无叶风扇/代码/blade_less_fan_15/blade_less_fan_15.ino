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
/*
unsigned int re_dai_yu_lin_data[] = {0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa,   0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa, 0x0000,0x0000,0x00aa};
//unsigned int re_dai_yu_lin_data[] = {0x0000,0x00aa,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0X0012,0x00aa,   0x0000,0x00aa,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0X0012,0x00aa};
unsigned int ha_er_bin_data[] =     {0x0012,0x0000,0x0031, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0X0000,0x0012,   0x0012,0x0000,0x0031, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0X0000,0x0012};
unsigned int cao_yuan_data[] =      {0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0002,0x00aa, 0x0000,0X0023,0x0011, 0x0000,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0002,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0000,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x0000,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0002,0x00aa, 0x0000,0X0023,0x0011, 0x0000,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0002,0x00aa, 0x0000,0X0023,0x0011, 0x0012,0X0032,0x0011, 0x0000,0x00aa,0x00aa,   0x0000,0X0012,0x00aa, 0x0000,0X0000,0x0011, 0x0012,0X0000,0x0011, 0x0000,0x0000,0x00aa};
unsigned int ma_er_dai_fu_data[] =  {0x0012,0X0000,0x0000, 0x00aa,0X0023,0x0000, 0x0000,0x0012,0x0012, 0x0000,0x0012,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0000,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0000,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0001,   0x0012,0X0000,0x0010, 0x00a0,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0000,0X0000,0x0012, 0x00aa,0X0023,0x0000, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0000,   0x0012,0X0000,0x0000, 0x00aa,0X0023,0x0000, 0x0000,0x0012,0x0012, 0x0000,0x0012,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0000,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0012,0X0000,0x0012, 0x00aa,0X0000,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0001,   0x0012,0X0000,0x0010, 0x00a0,0X0023,0x0012, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0031,   0x0000,0X0000,0x0012, 0x00aa,0X0023,0x0000, 0x0012,0x0012,0x0012, 0x0012,0x0000,0x0000};
*/
unsigned long re_dai_yu_lin_data[] = 
{
0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,

0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,

0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,
0xFF1000,0xFF1000,0xFF1000,0xFF1000,
};

unsigned long ha_er_bin_data[] =     
{
0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,

0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,

0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,
0x0097F1,0x0097F1,0x0097F1,0x0097F1,


};
unsigned long cao_yuan_data[] =
{

0xC79A79,0xC9957D,0xCA8F7D,0xCE8A7F,
0xD1837F,0xD17E7F,0xD47781,0xD77280,
0xC3A278,0xC2A676,0xBFAC72,0xBCB16F,
0xBDB76B,0xB8BB60,0xB8BF55,0xB4C343,

0xB0C739,0xADCD1C,0xADCD1C,0xB0C739,
0xB4C343,0xB8BF55,0xB8BB60,0xBDB76B,
0xBCB16F,0xBFAC72,0xC2A676,0xC3A278,
0xC79A79,0xC9957D,0xCA8F7D,0xCE8A7F,

0xD1837F,0xD17E7F,0xD47781,0xD77280,
0xD96981,0xD7597F,0xD5467C,0xD33278,
0xD01C73,0xD00270,0xD00270,0xD01C73,
0xD33278,0xD5467C,0xD7597F,0xD96981,




};

unsigned long ma_er_dai_fu_data[] =  
{
0xB86999,0xB26FA2,0xAC73A6,0xA179AD,
0x9F7CB2,0x9582BA,0x8E83BB,0x8788C1,
0x808AC8,0x788DCC,0x7190D3,0x6893D7,
0x6195DE,0x5297E2,0x4097E4,0x3096E8,

0x1E96EC,0x0196F0,0x0196F0,0x1E96EC,
0x3096E8,0x4097E4,0x5297E2,0x6195DE,
0x6893D7,0x7190D3,0x788DCC,0x808AC8,
0x8788C1,0x8E83BB,0x9582BA,0x9F7CB2,

0xA179AD,0xAC73A6,0xB26FA2,0xB86999,
0xBE5F98,0xC14C90,0xC73A86,0xC8287E,
0xCB1778,0xCE0470,0xCE0470,0xCB1778,
0xC8287E,0xC73A86,0xC14C90,0xBE5F98,

};
unsigned int RGBData[144];
//unsigned int RGBData2[144];
unsigned long iTestD;
unsigned int iTestD2;
void AllDataIn(unsigned char iM)
{
  unsigned char iIn;
  //unsigned char *iInP;
  switch(iM)
  {
    case 1:
      for(iIn=0;iIn<48;iIn=iIn+1)
      {        
        iTestD =(re_dai_yu_lin_data[iIn]&0xFF0000);    
        RGBData[iIn*3+1] =(unsigned char)(iTestD>>16);  
       iTestD2=RGBData[iIn*3];        
          
        iTestD =(re_dai_yu_lin_data[iIn]&0x00FF00);  
        RGBData[iIn*3] =(unsigned char)( iTestD>>8);  
        iTestD2=RGBData[iIn*3+1]; 
        
        iTestD =(re_dai_yu_lin_data[iIn]&0x0000FF);        
        RGBData[iIn*3+2] =(unsigned int)(iTestD); 
        iTestD2=RGBData[iIn*3+2]; 
        
      }

    break;
     case 2:
     for(iIn=0;iIn<48;iIn=iIn+1)
      {        
        iTestD =(ha_er_bin_data[iIn]&0xFF0000);    
        RGBData[iIn*3+1] =(unsigned char)(iTestD>>16);  
       iTestD2=RGBData[iIn*3];        
          
        iTestD =(ha_er_bin_data[iIn]&0x00FF00);  
        RGBData[iIn*3] =(unsigned char)( iTestD>>8);  
        iTestD2=RGBData[iIn*3+1]; 
        
        iTestD =(ha_er_bin_data[iIn]&0x0000FF);        
        RGBData[iIn*3+2] =(unsigned int)(iTestD); 
        iTestD2=RGBData[iIn*3+2]; 
        
      }

    break;
    case 3:
    for(iIn=48;0<iIn;iIn=iIn-1)
    //for(iIn=0;iIn<48;iIn=iIn+1)
      {        
        iTestD =(cao_yuan_data[iIn-1]&0xFF0000);    
    //RGBData[(48-iIn)*3+1] =(unsigned char)(iTestD>>16);  
    RGBData[iIn*3+1] =0xFF;  
       iTestD2=RGBData[iIn*3];        
          
        iTestD =(cao_yuan_data[iIn-1]&0x00FF00);  
        RGBData[(48-iIn)*3] =(unsigned char)( iTestD>>8);  
        iTestD2=RGBData[iIn*3+1]; 
        
        iTestD =(cao_yuan_data[iIn-1]&0x0000FF);        
        RGBData[(48-iIn)*3+2] =(unsigned int)(iTestD); 
        iTestD2=RGBData[iIn*3+2]; 
        
      }

    break;
    case 4:
    for(iIn=48;0<iIn;iIn=iIn-1)
    //for(iIn=0;iIn<48;iIn=iIn+1)
      {        
        iTestD =(ma_er_dai_fu_data[iIn-1]&0xFF0000);    
    //RGBData[(48-iIn)*3+1] =(unsigned char)(iTestD>>16);  
   RGBData[iIn*3+1] =0xFF;  
       iTestD2=RGBData[iIn*3];        
          
        iTestD =(ma_er_dai_fu_data[iIn-1]&0x00FF00);  
        RGBData[(48-iIn)*3] =(unsigned char)( iTestD>>8);  
        iTestD2=RGBData[iIn*3+1]; 
        
        iTestD =(ma_er_dai_fu_data[iIn-1]&0x0000FF);        
        RGBData[(48-iIn)*3+2] =(unsigned int)(iTestD); 
        iTestD2=RGBData[iIn*3+2]; 
        
      }

    break;
    case 5:
    for(iIn=0;iIn<48;iIn=iIn+1)
      {
        RGBData[iIn*3+1] =0xFF;
        RGBData[iIn*3] =0xFF;        
        RGBData[iIn*3+2] =0xFF;
      }

      break;
  }


}
//--------------------------------------------------------------------------

boolean BeginToJudgePressState = false;
int JudgePressCount = 0;
int Work_Mode = 0; //0 = not work; 1 = first run after work; 2 ＝ work
int Display_Command = 1;
int Display_State = 0;
int Display_Mode = 0;

LED_Bar myLED;
Timer t;

#include "TM1637.h"
#define CLK 3//pins definitions for TM1637 and can be changed to other ports       
#define DIO 2
TM1637 tm1637(CLK,DIO);
unsigned int TimeDisp[5];
int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

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
    
    
    attachInterrupt(2, BlockingStateChange, HIGH); //0 is digital 2，

    t.every(100, loop50ms,(void*)1);

    long_press_time = long_press_time*10-5;
    
    tm1637.init();
    tm1637.set(BRIGHT_DARKEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
    
    TimeDisp[0] = NumTab[2];
    TimeDisp[1] = NumTab[6];
    TimeDisp[2] = 0x01;
    TimeDisp[3] = NumTab[0];
    TimeDisp[4] = NumTab[0];
      
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
    tm1637.set(BRIGHT_DARKEST);
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
  unsigned char iIn2;
  Display_Command = command;
  switch(command){
    case one_key:{
      Display_Mode = 1;
      execute_Display_Command(Display_Mode);
    }
    break;
    case two_key:{
      Display_Mode = 2;
      execute_Display_Command(Display_Mode);
      break;
    }
    case three_key:{     
      Display_Mode = 3;
      execute_Display_Command(Display_Mode);
      break;
    }
    case four_key:{
      Display_Mode = 4;
      execute_Display_Command(Display_Mode);
      break;
    }
    case five_key:{
      if (Display_Mode < 4){
        Display_Mode++;
        execute_Display_Command(Display_Mode);
      }
      else{
        Display_Mode = 1;
        execute_Display_Command(Display_Mode);
      }
        Serial.println(Display_Mode);
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
      break;
    }
    case nine_key:{
      break;
    }
    case zero_key:{
      break;
    }
    case enter_key:{
      ChangeDeviceState();
      break;
    }
    case remote_up:{
      //Raise the temperature
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
        if (digitalRead(21)==0){
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
      //execute_Command(Display_Command);
      execute_Display_Command(Display_Mode);
      Display_State = 1;
    }
    TimeDisp[0] = NumTab[2];
    TimeDisp[1] = NumTab[6];
    TimeDisp[2] = 0x01;
    TimeDisp[3] = NumTab[0];
    TimeDisp[4] = NumTab[0];
    execute_Tem_Display_Command(TimeDisp);
  }
}


/*-------------
  run BlockingStateChange() when Infrared blocking sensor's state changed
--------------*/

void BlockingStateChange(){
  Serial.println("BlockingStateChange");
  if (digitalRead(21)==0){
        BeginToJudgePressState = true;
  }
}

void ChangeDeviceState(){
  Serial.println("ChangeDeviceState");
  if (Work_Mode == 0){
    Work_Mode = 1;
    Display_Command = one_key;
    Display_Mode = 1;
  }
  else{
    Work_Mode = 0;
  }
}

void execute_Display_Command(int _com){
  unsigned char iIn2;
  switch(_com){
    case 1:{
      AllDataIn(1);
      Display_Mode = 1;
      myLED.LED_Controler_by_raw_data(RGBData);
    }
    break;
    case 2:{
      AllDataIn(2);
      Display_Mode = 2;
      myLED.LED_Controler_by_raw_data(RGBData);
      break;
    }
    case 3:{     
     AllDataIn(3); 
     Display_Mode = 3;
      myLED.LED_Controler_by_raw_data(RGBData);
      break;
    }
    case 4:{
      AllDataIn(4);
      Display_Mode = 4;
      myLED.LED_Controler_by_raw_data(RGBData);
      break;
    }
  }
}

void execute_Tem_Display_Command(unsigned int TimeDisp[]){
    tm1637.set(BRIGHT_TYPICAL);
    tm1637.display(0,TimeDisp[0]);
    tm1637.display(1,TimeDisp[1]);
    if (TimeDisp[2]==0x0000){
      tm1637.point(POINT_OFF);
    }
    else{
      tm1637.point(POINT_ON);
    }
    tm1637.display(2,TimeDisp[3]);
    tm1637.display(3,TimeDisp[4]);
}
