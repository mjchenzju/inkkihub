/*
This is a Shake Timer .4.

－－－－－
Add Movement monitoring algorithm
Change clock_frequency to 50ms
－－－－－

Use 5 leds to tell you the time after you move the Shake-Timer. 

Use Three-axis angle sensor to monitor moving action.

digital 0 and digital 1 are communication interfaces.

digital 2: Button for display and setting
digital 3: vibrating monitor sensor
digital 4: led for 2hour
digital 5: led for 4hour
digital 6: led for 6hour
digital 7: led for 8hour
digital 8: led for 10hour

Analog  0: x
Analog  1: y
Analog  2: z
*/

#include <avr/wdt.h> 
#include <MsTimer2.h>


//Modify the parameters in this place---------------------------------------
float sensitivity = 0.3; //Moving sensitivity
float setting_mode_time_out = 5;  //Setting mode time out: 5s
float dont_catch_time = 20; // don't catch time 20s
float long_press_time = 2; //long press time 2s ,PS:long_press_time should greater than 0.5s
int clock_frequency = 50; // 50ms to refresh
//--------------------------------------------------------------------------


boolean BeginToJudgePressState = false;
int JudgePressCount = 0;
int Work_Mode = 0; // 0 = not work; 1 = work; 2 = setting; 3 ＝ uncatch ；4 = short press show
int Setting_Hours = 1; //1 = 2hours;2=4hours;3=6hours;4=8hours;5=12hours;
unsigned long Time_Count = 0;
int Short_Press_Show_Time_Count = 0;
int Work_Led_Show_Time_Count = 0;
int Setting_Time_Out_Count = 0;
int Uncatch_Time_Count = 0;
int Moving_Checking_Count = 0;
int Moving_State_Count = 0;

float ax_raw;
float ay_raw;
float az_raw;
        
void setup(){
    wdt_enable(WDTO_4S);
    Serial.begin(115200);
    Serial.println("Shake Timer 1.0.4");
    delay(10);
    
    attachInterrupt(0, ButtonStateChange, RISING); //0 is digital 2,
    //attachInterrupt(1, RestStateChange, RISING); //1 is digital 3
    delay(10);

    MsTimer2::set(clock_frequency, loop500ms); // 500ms period to check the button state
    MsTimer2::start();
    pinMode(4, OUTPUT); 
    pinMode(5, OUTPUT); 
    pinMode(6, OUTPUT); 
    pinMode(7, OUTPUT); 
    pinMode(8, OUTPUT); 
    
    ax_raw = abs((analogRead(A0)-330)/70.0);
    ay_raw = abs((analogRead(A1)-330)/70.0);
    az_raw = abs((analogRead(A2)-330)/70.0);
    
    setting_mode_time_out = setting_mode_time_out*20;
    dont_catch_time = dont_catch_time*20 - 5;
    long_press_time = long_press_time*20-10;
}

void loop(){  
    wdt_reset();
    //Timing and display the time
    
}

void JudgeMovingAction(){
    if (Work_Mode == 0){//abs()
        if (Moving_Checking_Count < 10){
            Moving_Checking_Count ++;
            if (abs(ax_raw -abs((analogRead(A0)-330)/70.0)) > sensitivity || abs(ay_raw -abs((analogRead(A1)-330)/70.0)) > sensitivity || abs(az_raw -abs((analogRead(A2)-330)/70.0)) > sensitivity){
                //Serial.println("Moving_State_Count++");
                Moving_State_Count++;
                ax_raw = abs((analogRead(A0)-330)/70.0);
                ay_raw = abs((analogRead(A1)-330)/70.0);
                az_raw = abs((analogRead(A2)-330)/70.0);

                Serial.print("ax_raw:");
                Serial.print(ax_raw);
                Serial.print(";  ");
                Serial.print("ay_raw:");
                Serial.print(ay_raw);
                Serial.print(";  ");
                Serial.print("az_raw:");
                Serial.print(az_raw);
                Serial.println(";  ");
            }

            if(Moving_State_Count >= 3){
                //Serial.println("Work_Mode changed : Working in 5");
                Moving_Checking_Count = 0;
                Moving_State_Count = 0;
                initTimerCount();
                Work_Mode = 1;
            }
            
        }
        else{
            Moving_Checking_Count = 0;
            if (Moving_State_Count >= 6){
                //Serial.println("Work_Mode changed : Working in 8");
                initTimerCount();
                Work_Mode = 1;
            }
            Moving_State_Count = 0;
        }
        
    }
}
void initTimerCount(){
    Time_Count = 0;
    Short_Press_Show_Time_Count = 0;
    Work_Led_Show_Time_Count = 0;
    Setting_Time_Out_Count = 0;
    Uncatch_Time_Count =0;
    JudgePressCount = 0;
    BeginToJudgePressState = false;
}

void loop500ms(){
    JudgePressState();
    JudgeMovingAction();
    if (Work_Mode == 1){
        UpdateDisplayInfo();
        TimerCount();
    }
    else if(Work_Mode == 2){
        if (Setting_Time_Out_Count > setting_mode_time_out){ //Setting mode time out: 5s
            Serial.println("Setting_Time_Out");
            Work_Mode = 3;
            Setting_Time_Out_Count = 0;           
            Work_Led_Show_Time_Count = 1;
        }
        else{
            Setting_Time_Out_Count++;
        }
        if (Setting_Time_Out_Count%10 == 0 && Work_Led_Show_Time_Count == 0){
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            digitalWrite(8, LOW);
            switch (Setting_Hours){
                case 1:
                    digitalWrite(4, HIGH);
                    break;
                case 2:
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    break;
                case 3:
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    break;
                case 4:
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    digitalWrite(7, HIGH);
                    break;
                case 5:
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    digitalWrite(7, HIGH);
                    digitalWrite(8, HIGH);
                    break;
            }
            Work_Led_Show_Time_Count = 1;
        }
        else if (Setting_Time_Out_Count%10 == 0 &&  Work_Led_Show_Time_Count == 1){
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            digitalWrite(8, LOW);
            Work_Led_Show_Time_Count =0;
        }
    }
    else if (Work_Mode == 3){
        Uncatch_Time_Count++;
        if (Uncatch_Time_Count < 100){
            switch (Setting_Hours){
                case 1:
                    digitalWrite(4, HIGH);
                    break;
                case 2:
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    break;
                case 3:
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    break;
                case 4:
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    digitalWrite(7, HIGH);
                    break;
                case 5:
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    digitalWrite(7, HIGH);
                    digitalWrite(8, HIGH);
                    break;
            }
            
        }
        else if (Uncatch_Time_Count == 100){ 
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            digitalWrite(8, LOW);
        }
        else if(Uncatch_Time_Count > dont_catch_time){ // don't catch time 20s
            Work_Mode = 0;
            initTimerCount();
        }

    }
    else if(Work_Mode == 4){
        if (Short_Press_Show_Time_Count < 200){
            Short_Press_Show_Time_Count = Short_Press_Show_Time_Count + 1;
        }
        else{
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            digitalWrite(8, LOW);
            Work_Mode = 0;
            initTimerCount();
        }
    }
}

void UpdateDisplayInfo(){
    //Serial.println("update the Led State.");
    //update the Led State
    switch (Setting_Hours){
        case 1:
            if (Time_Count < 144000){ // 144000 = 2hours * 60 mins * 60s * 20
                //[todo] to show
                ControlLedBlink(4);
            }
            else{
                digitalWrite(4, LOW);
                Work_Mode = 0;
                initTimerCount();
            }
            break;
        case 2:
            if (Time_Count < 288000){ // 288000 = 4hours * 60 mins * 60s * 20
                //[todo] to show
                if (Time_Count < 144000){ // 144000 = 2hours * 60 mins * 60s * 20
                    ControlLedBlink(4);
                }
                else{
                    digitalWrite(4, HIGH);
                    ControlLedBlink(5);
                }
            }
            else{
                digitalWrite(4, LOW);
                digitalWrite(5, LOW);
                Work_Mode = 0;
                initTimerCount();
            }
            break;
        case 3:
            if (Time_Count < 432000){ // 432000 = 6hours * 60 mins * 60s * 20
                //[todo] to show
                if (Time_Count < 144000){ // 144000 = 2hours * 60 mins * 60s * 20
                    ControlLedBlink(4);
                }
                else if (Time_Count < 288000){ 
                    digitalWrite(4, HIGH);
                    ControlLedBlink(5);
                }
                else{
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    ControlLedBlink(6);
                }
            }
            else{
                digitalWrite(4, LOW);
                digitalWrite(5, LOW);
                digitalWrite(6, LOW);
                Work_Mode = 0;
                initTimerCount();
            }
            break;
        case 4:
            if (Time_Count < 576000){ // 576000 = 8hours * 60 mins * 60s * 20
                //[todo] to show
                if (Time_Count < 144000){ // 144000 = 2hours * 60 mins * 60s * 20
                    ControlLedBlink(4);
                }
                else if (Time_Count < 288000){ 
                    digitalWrite(4, HIGH);
                    ControlLedBlink(5);
                }
                else if (Time_Count < 432000){ 
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    ControlLedBlink(6);
                }
                else{
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    ControlLedBlink(7);
                }
            }
            else{
                digitalWrite(4, LOW);
                digitalWrite(5, LOW);
                digitalWrite(6, LOW);
                digitalWrite(7, LOW);
                Work_Mode = 0;
                initTimerCount();
            }
            break;
        case 5:
            if (Time_Count < 864000){ // 864000 = 12hours * 60 mins * 60s * 20
                //[todo] to show
                if (Time_Count < 144000){ // 144000 = 2hours * 60 mins * 60s * 20
                    ControlLedBlink(4);
                }
                else if (Time_Count < 288000){ 
                    digitalWrite(4, HIGH);
                    ControlLedBlink(5);
                }
                else if (Time_Count < 432000){ 
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    ControlLedBlink(6);
                }
                else if (Time_Count < 576000){ 
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    ControlLedBlink(7);
                }
                else{
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    digitalWrite(6, HIGH);
                    digitalWrite(7, HIGH);
                    ControlLedBlink(8);
                }
            }
            else{
                digitalWrite(4, LOW);
                digitalWrite(5, LOW);
                digitalWrite(6, LOW);
                digitalWrite(7, LOW);
                digitalWrite(8, LOW);
                Work_Mode = 0;
                initTimerCount();
            }
            break;
    }
}

void ControlLedBlink(int pinNum){
    if (Work_Led_Show_Time_Count == 0){
        digitalWrite(pinNum, HIGH);
        Work_Led_Show_Time_Count++;
    }
    else if (Work_Led_Show_Time_Count == 10){
        digitalWrite(pinNum, LOW);
        Work_Led_Show_Time_Count++;
    }
    else if (Work_Led_Show_Time_Count < 30){
        Work_Led_Show_Time_Count++;
    }
    else{
        Work_Led_Show_Time_Count = 0;
    }
}

void TimerCount(){
    Time_Count = Time_Count + 1;
}

void JudgePressState(){
    if (BeginToJudgePressState == true){
        if (digitalRead(2)){
            //begin to judge long press by count
            if (JudgePressCount < long_press_time){ //long press time 2.5s
                JudgePressCount = JudgePressCount + 1;
            }
            else{
                //A long press, begin to process
                Serial.println("long press, entry setting mode");
                Work_Mode = 2;
                /*
                digitalWrite(4, HIGH);
                digitalWrite(5, HIGH);
                digitalWrite(6, HIGH);
                digitalWrite(7, HIGH);
                digitalWrite(8, HIGH);
                */
                JudgePressCount = 0;
                Work_Led_Show_Time_Count = 0;
                Setting_Time_Out_Count = 0;
                initTimerCount();
                BeginToJudgePressState = false;
            }
        }
        else{
            //A short press, begin to process
            Serial.println("short press");
            if (Work_Mode == 0 || Work_Mode == 3){
                Work_Mode = 4;
                switch (Setting_Hours){
                    case 1:
                        digitalWrite(4, HIGH);
                        break;
                    case 2:
                        digitalWrite(4, HIGH);
                        digitalWrite(5, HIGH);
                        break;
                    case 3:
                        digitalWrite(4, HIGH);
                        digitalWrite(5, HIGH);
                        digitalWrite(6, HIGH);
                        break;
                    case 4:
                        digitalWrite(4, HIGH);
                        digitalWrite(5, HIGH);
                        digitalWrite(6, HIGH);
                        digitalWrite(7, HIGH);
                        break;
                    case 5:
                        digitalWrite(4, HIGH);
                        digitalWrite(5, HIGH);
                        digitalWrite(6, HIGH);
                        digitalWrite(7, HIGH);
                        digitalWrite(8, HIGH);
                        break;
                }
            }
            else if(Work_Mode == 2){
                Setting_Time_Out_Count = 0;
                if (Setting_Hours < 5){
                    Setting_Hours++;
                }
                else{
                    Setting_Hours=1;
                }
            }
            JudgePressCount = 0;
            BeginToJudgePressState = false;
        }
    }
}

void ButtonStateChange(){
    //Serial.println("Button on");
    if (digitalRead(2)){
        //make a timer interruption to judge short press or long press.
        BeginToJudgePressState = true;
    }
}
/*
void RestStateChange(){
    //Serial.println("Rest State Change");
    // when Work_Mode is 4(short press show), don't catch moving action.
    if (Work_Mode  == 0 ){ 
        //Serial.println("Work_Mode changed : Working");
        initTimerCount();
        Work_Mode = 1;
    }
}
*/
