/*
This is a Shake Timer 1.0.

Use 5 leds to tell you the time after you move the Shake-Timer. 

digital 0 and digital 1 are communication interfaces.

digital 2: Button for display and setting
digital 3: vibrating monitor sensor
digital 4: led for 2hour
digital 5: led for 4hour
digital 6: led for 6hour
digital 7: led for 8hour
digital 8: led for 10hour

*/

#include <avr/wdt.h> 
#include <MsTimer2.h>

const int buttonPin = 2;
int buttonState = 0;         // variable for reading the pushbutton status
boolean BeginToJudgePressState = false;
int JudgePressCount = 0;

void setup(){
    wdt_enable(WDTO_4S);
    Serial.begin(9600);
    Serial.println("Shake Timer 1.0.");
    //attachInterrupt(0, ButtonStateChange, RISING); //0 is digital 2,
    attachInterrupt(1, RestStateChange, RISING); //1 is digital 3
    MsTimer2::set(50, loop500ms); // 500ms period to check the button state
    MsTimer2::start();
}

void loop(){  
    wdt_reset();
    //Timing and display the time

}

void loop500ms(){
    JudgePressState();
    UpdateDisplayInfo();
}

void UpdateDisplayInfo(){
    Serial.println("update the Led State.");
    //update the Led State
}

void JudgePressState(){
    if (BeginToJudgePressState == true){
        buttonState = digitalRead(buttonPin);
        if (buttonState){
            //begin to judge long press by count
            if (JudgePressCount < 4){
                JudgePressCount = JudgePressCount + 1;
            }
            else{
                //A long press, begin to process

                BeginToJudgePressState = false;
            }
        }
        else{
            //A short press, begin to process

            BeginToJudgePressState = false;
        }
    }
}
/*
void ButtonStateChange(){
    Serial.println("Button on");
    //delay(5); // To avoid accidentally triggered
    buttonState = digitalRead(buttonPin);
    if (buttonState){
        //make a timer interruption to judge short press or long press.
        BeginToJudgePressState = true;
    }
}
*/
void RestStateChange(){
    Serial.println("Rest State Change");
}
