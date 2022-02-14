#include "headers/global.h"

// 1 or 0 if button is pushed
int buttonVal;

 // push button 
int checkPushed() {
    buttonVal = digitalRead(15);
    // Serial.print("Button Val = ");
    // Serial.println(buttonVal);
    if (buttonVal == 1) {
        sendLocation();
    }
    publishtoServer(buttonVal); 
    return buttonVal;
}