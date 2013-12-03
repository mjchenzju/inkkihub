
#include <Arduino.h>

int led = 13;

int LEDARRAY_LAT = 8;
int LEDARRAY_CLK = 9;
int LEDARRAY_DI = 10;

unsigned char temp = 0xfe;

unsigned char Display_word[4][4] = {
{0x3E,0x02,0x02,0x00},/*"L",0*/
{0x1C,0x22,0x22,0x1C},/*"O",1*/
{0x00,0x3C,0x06,0x3C},/*"V",2*/
{0x00,0x3E,0x2A,0x2A},/*"E",3*/
};

unsigned char Display_word3[5][4] = {
0x03,0x03,0x00,0x7F,0x41,0x41,0x7F,0x00,
0x03,0x03,0x00,0x79,0x49,0x49,0x4F,0x00,
0x03,0x03,0x00,0x7F,
};

unsigned char l_word_0[2][4] = {
0x03,0x03,0x00,0x7F,0x41,0x41,0x7F,0x00,
};

unsigned char l_word_5[2][4] = {
0x03,0x03,0x00,0x79,0x49,0x49,0x4F,0x00,
};

unsigned char word_0[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0xFF,0xFF,0x03,0x03,0xFF,0xFF,0x00
};

unsigned char word_1[4][4] = {
0x00,0x00,0x00,0x03,0x03,0x03,0x00,0x00,
0x00,0x00,0x00,0x03,0xFF,0xFF,0x03,0x00,
};

unsigned char word_2[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0x3F,0x3F,0x33,0x33,0xF3,0xF3,0x00,
};

unsigned char word_3[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0x33,0x33,0x33,0x33,0xFF,0xFF,0x00,
};

unsigned char word_4[4][4] = {
0x00,0x03,0x03,0x00,0x00,0x03,0x03,0x00,
0x00,0xF0,0xF0,0x30,0x30,0xFF,0xFF,0x00,
};

unsigned char word_5[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0xF3,0xF3,0x33,0x33,0x3F,0x3F,0x00,
};
unsigned char word_6[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0xFF,0xFF,0x33,0x33,0x3F,0x3F,0x00,
};
unsigned char word_7[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
};
unsigned char word_8[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0xFF,0xFF,0x33,0x33,0xFF,0xFF,0x00,
};
unsigned char word_9[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0xF3,0xF3,0x33,0x33,0xFF,0xFF,0x00,
};
void setup()
{
    pinMode(led, OUTPUT);
    
    Init_LED_Array(); 
    
     Serial.begin(115200);
    
}

void loop()
{
   display(1);
}



void display(int num){
  unsigned char j,k;
  LEDARRAY_LAT = 8;
  LEDARRAY_CLK = 9;
  LEDARRAY_DI = 10;
  
			temp = 0x7f;
			for(j = 0 ; j <2  ; j++)		//显示前两个字母
			{
				for(k =  0; k < 4 ; k++)		//一个字母4BYTE
				{
                                        Send_Byte(0xFF);			//列选择
                                        Send_Byte(0x00);
					Send_Byte(temp);			//列选择
                                        Send_Byte(word_0[j][k]);
                                        
                                        digitalWrite(LEDARRAY_LAT, HIGH);					//锁存数据
					//delayMicroseconds(1);
					digitalWrite(LEDARRAY_LAT, LOW);
					//delayMicroseconds(1);
					temp = (temp>>1)|0x80;
				}
			}
                        temp = 0x7f;
			for(j = 2 ; j < 5 ; j++)		//显示前两个字母
			{
				for(k = 0 ; k < 4 ; k++)		//一个字母4BYTE
				{
					Send_Byte(temp);			//列选择
					Send_Byte(word_0[j][k]);			//行数据
                                        Send_Byte(0xff);			//列选择
                                        Send_Byte(0x00);
					digitalWrite(LEDARRAY_LAT, HIGH);					//锁存数据
					//delayMicroseconds(1);
					digitalWrite(LEDARRAY_LAT, LOW);
					//delayMicroseconds(1);
					temp = (temp>>1)|0x80;
				}
			}
    LEDARRAY_LAT = 5;
    LEDARRAY_CLK = 6;
    LEDARRAY_DI = 7;
  
			temp = 0x7f;
			for(j = 0 ; j <2  ; j++)		//显示前两个字母
			{
				for(k =  0; k < 4 ; k++)		//一个字母4BYTE
				{
                                        Send_Byte(0xFF);			//列选择
                                        Send_Byte(0x00);
					Send_Byte(temp);			//列选择
                                        Send_Byte(word_1[j][k]);
                                        
                                        digitalWrite(LEDARRAY_LAT, HIGH);					//锁存数据
					//delayMicroseconds(1);
					digitalWrite(LEDARRAY_LAT, LOW);
					//delayMicroseconds(1);
					temp = (temp>>1)|0x80;
				}
			}
                        temp = 0x7f;
			for(j = 2 ; j < 5 ; j++)		//显示前两个字母
			{
				for(k = 0 ; k < 4 ; k++)		//一个字母4BYTE
				{
					Send_Byte(temp);			//列选择
					Send_Byte(word_1[j][k]);			//行数据
                                        Send_Byte(0xff);			//列选择
                                        Send_Byte(0x00);
					digitalWrite(LEDARRAY_LAT, HIGH);					//锁存数据
					//delayMicroseconds(1);
					digitalWrite(LEDARRAY_LAT, LOW);
					//delayMicroseconds(1);
					temp = (temp>>1)|0x80;
				}
			}
                        LEDARRAY_LAT = 2;
                        LEDARRAY_CLK = 3;
                        LEDARRAY_DI = 4;
  
			temp = 0x7f;
			for(j = 0 ; j <2  ; j++)		//显示前两个字母
			{
				for(k =  0; k < 4 ; k++)		//一个字母4BYTE
				{
					Send_Byte(temp);			//列选择
                                        Send_Byte(l_word_0[j][k]);
                                        
                                        digitalWrite(LEDARRAY_LAT, HIGH);					//锁存数据
					delayMicroseconds(1);
					digitalWrite(LEDARRAY_LAT, LOW);
					delayMicroseconds(1);
					temp = (temp>>1)|0x80;
				}
			}
}


//****************************************************
//Init
//****************************************************
void Init_LED_Array()
{
  pinMode(LEDARRAY_LAT,OUTPUT); 
  pinMode(LEDARRAY_CLK,OUTPUT);
  pinMode(LEDARRAY_DI,OUTPUT);
  pinMode(5,OUTPUT); 
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(2,OUTPUT); 
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  
}

//****************************************************
//发送一个字节数据
//****************************************************
void Send_Byte( unsigned char dat)
{
	unsigned char i;
        digitalWrite(LEDARRAY_CLK, LOW);
	//delayMicroseconds(1);	
        digitalWrite(LEDARRAY_LAT, LOW);
	//delayMicroseconds(1);

	for( i = 0 ; i < 8 ; i++ )
	{
		if( dat&0x01 )
		{
                        digitalWrite(LEDARRAY_DI, HIGH);	
		}
		else
		{
                        digitalWrite(LEDARRAY_DI, LOW);
		}
		
                digitalWrite(LEDARRAY_CLK, HIGH);				//上升沿发送数据
		//delayMicroseconds(1);
		digitalWrite(LEDARRAY_CLK, LOW);
                //delayMicroseconds(1);
				
		dat >>= 1;			
	}		
}






