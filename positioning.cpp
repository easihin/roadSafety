#include "headers/global.h"

ADXL345 accel;

using namespace std;

// callibration value
float callVal = 256.00;

class Position {
    public: 
        float callibrate(float val, float offset) {
            return (val + offset);
        }
        int pitch(float x, float y, float z) {
            return atan(-1 * x / sqrt(pow(y, 2) + pow(z, 2))) * 180 / PI;
        }
        int roll(float x, float y, float z) {
            return atan(y / sqrt(pow(x, 2) + pow(z, 2))) * 180 / PI; 
        }
        float angle(float property) {
            float temp = 0.94 * temp + 0.06 * property;
            return temp;
        }
};

Position current;

// raw data from adxl
std::tuple<int, int, int> rawPositions() {
    int rawX = accel.getAccelerationX();
    int rawY = accel.getAccelerationY();
    int rawZ = accel.getAccelerationZ();

    return {rawX, rawY, rawZ};
}

void checkPositions() {
    auto [xVal, yVal, zVal] = rawPositions();

    int xOffset = -10;
    int yOffset = 100;
    int zOffset = 13;

    float newX = current.callibrate(xVal, xOffset);
    float newY = current.callibrate(yVal, yOffset);
    float newZ = current.callibrate(zVal, zOffset);

    float roll = current.roll(newX/callVal, newY/callVal, newZ/callVal);
    float pitch = current.pitch(newX/callVal, newY/callVal, newZ/callVal);

    float rollF = current.angle(roll);
    float pitchF = current.angle(pitch);

    int lowerBound = 256 - 50;
    int higherBound = 256 + 50;
    
    // if flipped
    if (fabs(pitchF > 1.5) || (!(newZ > lowerBound) && !(newZ < higherBound))) {
      int i = 1;
      isSafe(i);
    }

    // extreme deceleration
    if (newY < -100 || fabs(rollF) > 1.5) {
      int i = 2;
      isSafe(i);
     }

    Serial.print("pitchF: ");
    Serial.println(pitchF);
    Serial.print("rollF: ");
    Serial.println(rollF);

}

void initAccel() {
    accel.initialize();
}

// 10 second timer
void isSafe(int i) {
  int seconds = 0;
  bool toRun = true;
  int message = 3;
  while (toRun == true) {
      printLCD(message);
      delay(1000);
      
      seconds++;
      cout << seconds << " sec " << endl;
 
      if (seconds >= 10) {
        message = 4;
        sendMessage(i);
        Serial.println("not safe");
     } else if (checkPushed() == 1) {
        toRun = false;
        Serial.println("safe");
     }
   }
}
