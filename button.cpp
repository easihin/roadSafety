#include "headers/global.h"

// 1 or 0 if button is pushed
int buttonVal;

 // push button 
int checkPushed() {
    buttonVal = digitalRead(15);

    publishtoServer(buttonVal); 
    return buttonVal;
}
