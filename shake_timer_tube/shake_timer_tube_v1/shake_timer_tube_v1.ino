/*
This is a Shake Timer Tube .1.

Use Tube to tell user what the time after user move the Shake-Timer. 

Use Three-axis angle sensor to monitor moving action.

digital 0 and digital 1 are communication interfaces.

digital 2: Button for display and setting
digital 3: 
digital 4: 
digital 5: 
digital 6: 
digital 7: 
digital 8: 

Analog  0: x
Analog  1: y
Analog  2: z


*/

#include <avr/wdt.h> 
#include <MsTimer2.h>

boolean BeginToJudgePressState = false;
int JudgePressCount = 0;
int Work_Mode = 0; // 0 = not work; 1 = work; 2 = setting; 3 ＝ uncatch ；4 = short press show
int Setting_Hours = 1; //1 = 2hours;2=4hours;3=6hours;4=8hours;5=12hours;
unsigned long Time_Count = 0;
int Short_Press_Show_Time_Count = 0;
int Work_Led_Show_Time_Count = 0;
int Setting_Time_Out_Count = 0;
int Uncatch_Time_Count =0;

void setup(){
    wdt_enable(WDTO_4S);
    Serial.begin(9600);
    Serial.println("Shake Timer 1.0.");
    delay(10);
    
    attachInterrupt(0, ButtonStateChange, RISING); //0 is digital 2,
    //attachInterrupt(1, RestStateChange, RISING); //1 is digital 3
    delay(10);

    MsTimer2::set(500, loop500ms); // 500ms period to check the button state
    MsTimer2::start();
    pinMode(4, OUTPUT); 
    pinMode(5, OUTPUT); 
    pinMode(6, OUTPUT); 
    pinMode(7, OUTPUT); 
    pinMode(8, OUTPUT); 
}

void loop(){  
    wdt_reset();
    //Timing and display the time
    delay(100);
    if (Work_Mode == 0){
        float ax_raw = abs(analogRead(A0)/16384.0-0.07);
        float ay_raw = abs(analogRead(A1)/16384.0-0.01);
        float az_raw = abs(analogRead(A2)/16384.0+0.08);
        Serial.print("a/g:\t");
        Serial.print(ax_raw); Serial.print("\t");
        Serial.print(ay_raw); Serial.print("\t");
        Serial.print(az_raw); Serial.print("\t");
        if (ax_raw >2 || ay_raw>2 || az_raw>2.07){
            //Serial.println("Work_Mode changed : Working");
            initTimerCount();
            Work_Mode = 1;
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
    if (Work_Mode == 1){
        UpdateDisplayInfo();
        TimerCount();
    }
    else if(Work_Mode == 2){
        if (Work_Led_Show_Time_Count == 0){
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
            Work_Led_Show_Time_Count++;
        }
        else if (Work_Led_Show_Time_Count == 1){
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            digitalWrite(8, LOW);
            Work_Led_Show_Time_Count =0;
        }
        if (Setting_Time_Out_Count >10){ //Setting mode time out: 5s
            Work_Mode = 3;
            Setting_Time_Out_Count = 0;
            Serial.println("Setting_Time_Out");
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            digitalWrite(8, LOW);
        }
        else{
            Setting_Time_Out_Count++;
        }
    }
    else if (Work_Mode == 3){
        Uncatch_Time_Count++;
        if (Uncatch_Time_Count < 10){
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
        else if (Uncatch_Time_Count==10){ //uncatch time 20s
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            digitalWrite(8, LOW);
        }
        else if(Uncatch_Time_Count > 40){
            Work_Mode = 0;
            initTimerCount();
        }

    }
    else if(Work_Mode == 4){
        if (Short_Press_Show_Time_Count < 20){
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
            if (Time_Count < 14400){ // 14400 = 2hours * 60 mins * 60s * 2
                //[todo] to show
                ControlLedBlink(4);
            }
            else{
                digitalWrite(4, LOW);
                DisplayClean();
                Work_Mode = 0;
                initTimerCount();
            }
            break;
        case 2:
            if (Time_Count < 28800){ // 28800 = 4hours * 60 mins * 60s * 2
                //[todo] to show
                if (Time_Count < 14400){ // 14400 = 2hours * 60 mins * 60s * 2
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
                DisplayClean();
                Work_Mode = 0;
                initTimerCount();
            }
            break;
        case 3:
            if (Time_Count < 43200){ // 43200 = 6hours * 60 mins * 60s * 2
                //[todo] to show
                if (Time_Count < 14400){ // 14400 = 2hours * 60 mins * 60s * 2
                    ControlLedBlink(4);
                }
                else if (Time_Count < 28800){ 
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
                DisplayClean();
                Work_Mode = 0;
                initTimerCount();
            }
            break;
        case 4:
            if (Time_Count < 57600){ // 57600 = 8hours * 60 mins * 60s * 2
                //[todo] to show
                if (Time_Count < 14400){ // 14400 = 2hours * 60 mins * 60s * 2
                    ControlLedBlink(4);
                }
                else if (Time_Count < 28800){ 
                    digitalWrite(4, HIGH);
                    ControlLedBlink(5);
                }
                else if (Time_Count < 43200){ 
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
                DisplayClean();
                Work_Mode = 0;
                initTimerCount();
            }
            break;
        case 5:
            if (Time_Count < 86400){ // 86400 = 12hours * 60 mins * 60s * 2
                //[todo] to show
                if (Time_Count < 14400){ // 14400 = 2hours * 60 mins * 60s * 2
                    ControlLedBlink(4);
                }
                else if (Time_Count < 28800){ 
                    digitalWrite(4, HIGH);
                    ControlLedBlink(5);
                }
                else if (Time_Count < 43200){ 
                    digitalWrite(4, HIGH);
                    digitalWrite(5, HIGH);
                    ControlLedBlink(6);
                }
                else if (Time_Count < 57600){ 
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
                DisplayClean();
                Work_Mode = 0;
                initTimerCount();
            }
            break;
    }
}
void DisplayClean(){
    //[todo] make all pin low
}

void ControlLedBlink(int pinNum){
    if (Work_Led_Show_Time_Count == 0){
        digitalWrite(pinNum, HIGH);
        Work_Led_Show_Time_Count++;
    }
    else if (Work_Led_Show_Time_Count == 1){
        digitalWrite(pinNum, LOW);
        Work_Led_Show_Time_Count++;
    }
    else if (Work_Led_Show_Time_Count < 3){
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
            if (JudgePressCount < 4){
                JudgePressCount = JudgePressCount + 1;
            }
            else{
                //A long press, begin to process
                Serial.println("long press, entry setting mode");
                Work_Mode = 2;
                digitalWrite(4, HIGH);
                digitalWrite(5, HIGH);
                digitalWrite(6, HIGH);
                digitalWrite(7, HIGH);
                digitalWrite(8, HIGH);
                JudgePressCount = 0;
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