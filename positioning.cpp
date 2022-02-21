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

    // offset found when ADXL is flat on the ground
    int xOffset = -6;
    int yOffset = 15;
    int zOffset = -30;

    float newX = current.callibrate(xVal, xOffset);
    float newY = current.callibrate(yVal, yOffset);
    float newZ = current.callibrate(zVal, zOffset);

    float roll = current.roll(newX, newY, newZ);
    float pitch = current.pitch(newX, newY, newZ);

    float rollF = current.angle(roll);
    float pitchF = current.angle(pitch);

    int lowerBound = 256 - 50;
    int higherBound = 256 + 50;

    if (fabs(rollF > 40) || (!(zVal > lowerBound) && !(zVal > higherBound))) {
        sendMessage(1);
    }

    Serial.print("rollF: ");
    Serial.println(rollF);

    Serial.print("zVal: ");
    Serial.println(zVal);
}

void initAccel() {
    accel.initialize();
}