 
#include <Arduino.h>

int led = 13;

int LEDARRAY_LAT = 2;
int LEDARRAY_CLK = 3;
int LEDARRAY_DI = 4;

unsigned char temp = 0xfe;

unsigned char Display_word[4][4] = {
{0x3E,0x02,0x02,0x00},/*"L",0*/
{0x1C,0x22,0x22,0x1C},/*"O",1*/
{0x00,0x3C,0x06,0x3C},/*"V",2*/
{0x00,0x3E,0x2A,0x2A},/*"E",3*/
};

unsigned char Display_word3[10][4] = {
0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,

0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,

0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,

0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,

0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,
};


unsigned char word_0[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E,
0x66,0x66,0x66,0x66,0x66,0x66,0x7E,0x7E
};

unsigned char word_1[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,
0x30,0x30,0x30,0x30,0x30,0x30,0x78,0x78
};

unsigned char word_2[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E,
0x60,0x60,0x7E,0x7E,0x06,0x06,0x7E,0x7E
};

unsigned char word_3[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E,
0x60,0x60,0x7E,0x7E,0x60,0x60,0x7E,0x7E,
};

unsigned char word_4[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x66,
0x66,0x66,0x7E,0x7E,0x60,0x60,0x60,0x60
};

unsigned char word_5[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E,
0x06,0x06,0x7E,0x7E,0x60,0x60,0x7E,0x7E
};
unsigned char word_6[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E,
0x06,0x06,0x7E,0x7E,0x66,0x66,0x7E,0x7E
};
unsigned char word_7[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E,
0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60
};
unsigned char word_8[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E,
0x66,0x66,0x7E,0x7E,0x66,0x66,0x7E,0x7E
};
unsigned char word_9[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E,
0x66,0x66,0x7E,0x7E,0x60,0x60,0x7E,0x7E,
};
void setup()
{
    pinMode(led, OUTPUT);
    
    Init_LED_Array(); 
    
     Serial.begin(115200);
    
}

void loop()
{
       excute_1();
}



void display(int num){
  unsigned char j,k;
  switch (num){
    case 1:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_1[j][k];
        }
      }
      break;
    case 2:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_2[j][k];
        }
      }
      break;
    case 3:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_3[j][k];
        }
      }
      break;
      case 4:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_4[j][k];
        }
      }
      break;
      case 5:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_5[j][k];
        }
      }
      break;
      case 6:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_6[j][k];
        }
      }
      break;
      case 7:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_7[j][k];
        }
      }
      break;
      case 8:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_8[j][k];
        }
      }
      break;
      case 9:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_9[j][k];
        }
      }
      break;
      case 0:
      for(j = 0 ; j <4  ; j++){
	for(k =  0; k < 4 ; k++){
            Display_word[j][k] = word_0[j][k];
        }
      }
      break;
  }
  
}

void excute_1(){
                        unsigned char i,j,k;
                        
                        for(i=0; i<4; i++)
                        {
      			    temp = 0x80;
    			    //for(j = 0 ; j < 5  ; j++)		//显示Two Row
    			    {
    			//	for(k =  0; k < 4 ; k++)		//一个字母4BYTE
    				{
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[9][j]);
                                         
    				}
                                {
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[8][j]);
                                         
    				} 
                                {
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[7][j]);
                                         
    				}
                                {
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[6][j]);
                                         
    				}
                                {
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[5][j]);
                                         
    				}
    				{
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[4][j]);
                                         
    				}
                                {
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[3][j]);
                                         
    				} 
                                {
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[2][j]);
                                         
    				}
                                {
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[1][j]);
                                         
    				}
                                {
    					Send_Byte(temp);			//列选择
                                        Send_Byte(Display_word3[0][j]);
                                         
    				}
                                digitalWrite(LEDARRAY_LAT, HIGH);         //锁存数据
                                delayMicroseconds(1);
                                digitalWrite(LEDARRAY_LAT, LOW);
                                delayMicroseconds(10);
                                temp = (temp>>1) & 0X7f;
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
  
}

//****************************************************
//发送一个字节数据
//****************************************************
void Send_Byte( unsigned char dat)
{
	unsigned char i;
        digitalWrite(LEDARRAY_CLK, LOW);
	delayMicroseconds(1);	
        digitalWrite(LEDARRAY_LAT, LOW);
	delayMicroseconds(1);

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






