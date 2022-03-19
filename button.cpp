#include "headers/global.h"

// 1 or 0 if button is pushed
int buttonVal;

 // push button 
int checkPushed() {
    buttonVal = digitalRead(15);

    // if the driver clicks, it means that the driver needs help
    // testing of server and sendLocation function
    // if (buttonVal == 1) {
    //     sendLocation();
    // }
    // Serial.print("Button Val: " );
    // Serial.println(buttonVal);

    publishtoServer(buttonVal); 
    return buttonVal;
}