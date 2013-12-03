
#include <Arduino.h>

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

unsigned char Display_word_init[4][4] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char Display_word_shiwei[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0x3F,0x3F,0x33,0x33,0xF3,0xF3,0x00,
};

unsigned char Display_word_gewei[4][4] = {
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x00,0xFF,0xFF,0x33,0x33,0x3F,0x3F,0x00,
};

unsigned char Display_word_shifenwei[2][4] = {
0x03,0x03,0x00,0x7F,0x41,0x41,0x7F,0x00,
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

int Work_Mode = 0;

unsigned int Temperature = 260;


void setup()
{
    Serial.begin(115200);   //debug serial
    delay(100);
    Serial.println("blade less fan simple v.7");
    delay(100);
    Serial1.begin(115200);  //IR Serial
    delay(100);
    
    Init_LED_Array(); 
    
}

void loop()
{
	if(Work_Mode == 0){
		Init_LED_Array();
	}
	else{
		display();
	}
	while (Serial.available() > 0){
	    char temp =char(Serial.read());
	    if(temp == '-'){
	    	Temperature = Temperature - 5;
	    }
	    else if(temp == '+'){
	    	Temperature = Temperature + 5;
	    }
	    else if(temp == '4'){
	    	Temperature = 300;
	    }
	    else if(temp == '5'){
	    	Temperature = 180;
	    }
	    else if(temp == '0'){
	    	Temperature = 220;
	    }
	    else if(temp == '2'){
	    	Temperature = 260;
	    }
	    else if(temp == 'k'){
	    	Work_Mode = 1;
	    }
	    else if(temp == 'g'){
	    	Work_Mode = 0;
	    }
	    update_Temperature_info();
  	}
}

void display(){
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
                    Send_Byte(Display_word_shiwei[j][k]);
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
					Send_Byte(Display_word_shiwei[j][k]);			//行数据
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
                    Send_Byte(Display_word_gewei[j][k]);
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
					Send_Byte(Display_word_gewei[j][k]);			//行数据
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
                    Send_Byte(Display_word_shifenwei[j][k]);
                                        
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
  
  unsigned char j,k;
  for(j = 0 ; j <4  ; j++){
    for(k =  0; k < 4 ; k++){
        Display_word_shiwei[j][k] = Display_word_init[j][k];
    }
  }
    for(j = 0 ; j <4  ; j++){
    for(k =  0; k < 4 ; k++){
        Display_word_gewei[j][k] = Display_word_init[j][k];
    }
  }
    for(j = 0 ; j <2  ; j++){
    for(k =  0; k < 4 ; k++){
        Display_word_shifenwei[j][k] = Display_word_init[j][k];
    }
  }
  display();
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

void update_Temperature_info(){
  //Serial.println("update_Temperature_info");
  unsigned char j,k;
  switch (int(Temperature/100)){
    case 1:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_1[j][k];
        }
      }
      break;
    case 2:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_2[j][k];
        }
      }
      break;
    case 3:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_3[j][k];
        }
      }
      break;
    case 4:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_4[j][k];
        }
      }
      break;
    case 5:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_5[j][k];
        }
      }
      break;
    case 6:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_6[j][k];
        }
      }
      break;
    case 7:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_7[j][k];
        }
      }
      break;
    case 8:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_8[j][k];
        }
      }
      break;
    case 9:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_9[j][k];
        }
      }
      break;
    case 0:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shiwei[j][k] = word_0[j][k];
        }
      }
      break;
  }
  switch (int(Temperature-Temperature/100*100)/10){
    case 1:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_1[j][k];
        }
      }
      break;
    case 2:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_2[j][k];
        }
      }
      break;
    case 3:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_3[j][k];
        }
      }
      break;
    case 4:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_4[j][k];
        }
      }
      break;
    case 5:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_5[j][k];
        }
      }
      break;
    case 6:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_6[j][k];
        }
      }
      break;
    case 7:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_7[j][k];
        }
      }
      break;
    case 8:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_8[j][k];
        }
      }
      break;
    case 9:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_9[j][k];
        }
      }
      break;
    case 0:
      for(j = 0 ; j <4  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_gewei[j][k] = word_0[j][k];
        }
      }
      break;
  }
  switch (int(Temperature-Temperature/10*10)){
    case 5:
      for(j = 0 ; j <2  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shifenwei[j][k] = l_word_5[j][k];
        }
      }
      break;
    case 0:
      for(j = 0 ; j <2  ; j++){
        for(k =  0; k < 4 ; k++){
            Display_word_shifenwei[j][k] = l_word_0[j][k];
        }
      }
      break;
  }
}




