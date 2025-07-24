#include "IRSensors.h"

void setupIR(const IRSensorConfig& sensor) {
    pinMode(sensor.vccPin, OUTPUT);
    digitalWrite(sensor.vccPin, HIGH);
}

bool isBlack(int value) {
    return value > threshold;
}

void readIRSensors(bool& left, bool& center, bool& right) {
    left = isBlack(analogRead(irLeft.analogPin));
    center = isBlack(analogRead(irCenter.analogPin));
    right = isBlack(analogRead(irRight.analogPin));
}
