#include "headers/global.h"

LiquidCrystal_I2C lcd(0x27,16,2);

String message;

void startLCD() {
   lcd.begin();
   Wire.begin();
}

// if nothing bad is happening
void safeDriving(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("All Safe!");
}

void printLCD(int received) {
    lcd.clear();
    lcd.setCursor(0, 0);

    // val 1 -- hydroplaning risk
    if (received == 1) {
        message = "Slow Down!";
    } else if (received == 2) {
        message = "Wet Road";
    } else if (received == 3) {
        message = "Hold Button";
    } else if (received == 4) {
        message = "Help!";
    }
    
    lcd.print(message);
}
