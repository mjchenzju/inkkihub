#include "LED_Bar.h"
#include <Arduino.h>

LED_Bar::LED_Bar(void)
{
//  _clk=clk;
//  _dat=dat;
  DDR_Data |= BIT_Data;
  DDR_Clk |= BIT_Clk;
 // pinMode(_clk,OUTPUT);  //Data pin
//  pinMode(_dat,OUTPUT);  //CLK pin
}
void LED_Bar::LED_Controler(unsigned int rgb_upper[], unsigned int rgb_lower[]){
  unsigned char i=0; 
  unsigned char k=1; 
  unsigned char j=1; 
  unsigned char l=0;
  for (i=0;i<2;i++){
    for(j=1;j<2;j++){//(LED_NUM/2.0+1)
      send16bitData(CmdMode);
     /*
     for (k=1;k<5;k++){
        for(l=0;l<3;l++){
          send16bitData((rgb_upper[l]-rgb_lower[l])/(2*LED_NUM/j/k));
        }
      }
      */
      for(j=0;j<12;j++)       
      send16bitData(ON);    
      latchData();
    }
  }
}

void LED_Bar::CLEAN_LED(void)
//indexto : range 1~10.for example: 5, the 1~5 would be light 
{
  unsigned char i; 
  for (i=0;i<LED_NUM;i++){
    unsigned char j;
    send16bitData(CmdMode);    
    for(j=0;j<12;j++)       
    send16bitData(SHUT);       
    latchData();
  }
}


void LED_Bar::set_LED_Index(unsigned int index)
//index: range 0b000000000000~0b001111111111, 1 stands light whlie 0 stands off;
{
  unsigned char i;
  send16bitData(CmdMode); 
  for (i=0;i<12;i++)
  {
    if (index&0x0001)
    send16bitData(ON);
    else
    send16bitData(SHUT);
    index= index>>1;
  }
  latchData();
}
void LED_Bar::set_LED_Index(unsigned int index1,unsigned int index2)
//index: range 0b000000000000~0b001111111111, 1 stands light whlie 0 stands off;
{
  unsigned char i;
  for (unsigned char j =0;j<2;j++)
  {
      send16bitData(CmdMode); 
      if (j==0)
      {
      for (i=0;i<12;i++)
        {
          if (index1&0x0001)
          send16bitData(ON);
          else
          send16bitData(SHUT);
         index1= index1>>1;
        }
      }
      if (j==1)
      {
      for (i=0;i<12;i++)
        {
          if (index2&0x0001)
          send16bitData(ON);
          else
          send16bitData(SHUT);
         index2= index2>>1;
        }
      }
  }
      latchData();
}
void LED_Bar::set_LED_Range(unsigned int indexTo)
//indexto : range 1~10.for example: 5, the 1~5 would be light 
{
  unsigned char i;
  
   send16bitData(CmdMode); 
  for(i=0;i<12;i++)
  {
    if(i<indexTo)
    {
      send16bitData(ON);
    }
    else 
    {
      send16bitData(SHUT);
    }
     // indexTo=indexTo>>1;
  }
   
  latchData();
}
void LED_Bar::set_LED_Range(unsigned int indexTo1,unsigned int indexTo2)
//indexto : range 1~10.for example: 5, the 1~5 would be light 
{
  unsigned char i;
  
  for (unsigned char j =0;j<2;j++)
  {
    send16bitData(CmdMode); 
   if (j==0)
    {
    for(i=0;i<12;i++)
        {
        if(i<indexTo1)
        {
          send16bitData(ON);
        }
        else 
        {
          send16bitData(SHUT);
         }
        }
    }
    if (j==1)
    {
       for(i=0;i<12;i++)
        {
        if(i<indexTo2)
        {
          send16bitData(ON);
        }
        else 
        {
          send16bitData(SHUT);
         }
        }
    }
   
  }
  latchData();
}
void LED_Bar::set_LED1(void)
//indexto : range 1~10.for example: 5, the 1~5 would be light 
{
  unsigned char i;
  
  
    send16bitData(CmdMode);    
    //for(i=0;i<12;i++) 
    for(i=0;i<12;i=i+3) 
   {   
     send16bitData(ON);send16bitData(ON);send16bitData(ON);
   }    
    latchData();
}
void LED_Bar::set_LED2(void)
//indexto : range 1~10.for example: 5, the 1~5 would be light 
{
  unsigned char i;
  
  
    send16bitData(CmdMode);    
    for(i=0;i<12;i++)       
    send16bitData(SHUT);       
    latchData();
}
void LED_Bar::send16bitData(unsigned int data)
{
  for(unsigned char m=0;m<16;m++)
    {
        if(data&0x8000)
        {
            PORT_Data |= BIT_Data;
        }
        else
        {
            PORT_Data &=~ BIT_Data;
        }

        PORT_Clk ^= BIT_Clk;
        data <<= 1;
    }
}
void LED_Bar::latchData(void)
{
    Serial.println("latchData");
    PORT_Data &=~ BIT_Data;
    delayMicroseconds(10);
    for(unsigned char m=0;m<8;m++)
    {
        PORT_Data ^= BIT_Data;
    }
}
