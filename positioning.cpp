#include "headers/global.h"

ADXL345 accel;

// callibration value
float callVal = 256.00;

class Position {
    public: 
        float callibrate(float val, float offset) {
            return (val + offset)/callVal;
        }
        int pitch(float x, float y, float z) {
            return atan(-1 * x / sqrt(pow(y, 2) + pow(z, 2))) * 180 / PI;
        }
        int roll(float x, float y, float z) {
            return atan(y / sqrt(pow(x, 2) + pow(z, 2))) * 180 / PI; 
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

void positioning() {
    auto [x_val, y_val, z_val] = rawPositions();

    // offset found when ADXL is flat on the ground
    int xOffset = -6;
    int yOffset = 15;
    int zOffset = -30;

    float newX = current.callibrate(x_val, xOffset);
    float newY = current.callibrate(y_val, yOffset);
    float newZ = current.callibrate(z_val, zOffset);

    float roll = current.roll(newX, newY, newZ);
    float pitch = current.pitch(newX, newY, newZ);

    // thresholds for sudden deceleration
    if (pitch < -30 && newX < - 200) {
        sendMessage(3);
        Serial.println("sudden deceleration");
    }
}

void checkPositions() {

    auto [x_val, y_val, z_val] = rawPositions();

    // uncertainty here is 30
    int lowerBound = 256 - 30;
    int higherBound = 256 + 30;

    if ((z_val > -1 * lowerBound) && (z_val < -1 * higherBound)) { // case 1 -- flipped over
        sendMessage(1);
    } else if ((fabs(x_val) > lowerBound ) && (fabs(x_val) < higherBound)) { // case 2 -- on the side
        sendMessage(2);
    }
}

void initAccel() {
    accel.initialize();
}