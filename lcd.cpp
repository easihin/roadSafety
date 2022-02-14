#include "headers/global.h"

LiquidCrystal_I2C lcd(0x27,16,2);

void startLCD() {
   lcd.begin();
    Wire.begin();
}

void printLCD(int received) {
    lcd.clear();
    lcd.setCursor(0, 0);
    String message;

    // val 1 -- hydroplaning

    if (received == 1) {
        message = "You are at risk of hydroplaning, slow down to at least 22.5km/h"; //idk the numbers
    } else if (received == 0) {
        message = "Driving safe is a always a smart idea!";
    }

    // each message will represent something
    // char[100] value = hydroplaningstuff();
    // if value is blahblahblah, change up the message
    // string message = "steer to the _____, slow down, etc."
    // lcd.print()
    
    lcd.print(message);
}