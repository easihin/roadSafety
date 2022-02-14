#include "headers/global.h"

ADXL345 accel;

int xOffset, yOffset, zOffset;
float newX, newY, newZ;
float pitch, roll, yaw;

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
        // yaw doesn't really work :(
        int yaw(float x, float y, float z) {
            return atan(sqrt(pow(x, 2) + pow(y, 2)) / z) * 180/ PI; 
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

int positioning() {
    auto [x_val, y_val, z_val] = rawPositions();

    Serial.println("x = " + x_val);
    Serial.print("y = " + y_val);

    // offset found when ADXL is flat on the ground
    xOffset = -6;
    yOffset = 15;
    zOffset = -30;

    // I callibrated when ADXL was flat on the ground. It should be 0.00, 0.00, 1.00
    newX = current.callibrate(x_val, xOffset);
    newY = current.callibrate(y_val, yOffset);
    newZ = current.callibrate(z_val, zOffset);

    // yaw might not work but we'll see
    roll = current.roll(newX, newY, newZ);
    pitch = current.pitch(newX, newY, newZ);
    yaw = current.yaw(newX, newY, newZ);

    // Serial.print("roll: " );
    // Serial.print(roll);
    // Serial.print("  pitch: ");
    // Serial.print(pitch);
    // Serial.print("  yaw: ");
    // Serial.print(yaw);
    // Serial.println(" ");
    
    // Serial.print("x = ");
    // Serial.println(newX);
    // Serial.print("y = ");
    // Serial.println(newY);
    // Serial.print("z = ");
    // Serial.println(newZ);
}

void checkPositions() {

    auto [x_val, y_val, z_val] = rawPositions();

    // uncertainty here is 30
    int lowerBound = 256 - 30;
    int higherBound = 256 + 30;
    int fullSubmersion = 700; // this is a guess, I gotta check again
    
    int message = 0;

    if (z_val > lowerBound || z_val < higherBound) { // case 1 -- flipped over
        message = 1;
    } else if (fabs(y_val) > lowerBound || fabs(y_val) < higherBound) { // case 2 -- on the side
        message = 2;
    } else if (getWaterValue() >= fullSubmersion) {  // case 3 -- submerged
        // check if it's not a flood through some fancy error checking that I haven't figured out ;-;
        // maybe check if the speed has gone to a halt (but then what if theres a traffic jam)
        // then maybe check if the z is going down or smth
        message = 3;
    }
    sendMessage(message); 
}

void initAccel() {
    accel.initialize();
}