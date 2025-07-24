#pragma once

#include <Arduino.h>

struct MotorConfig {
    uint8_t in1, in2, pwm;
};

struct IRSensorConfig {
    uint8_t analogPin;
    uint8_t vccPin;
};

enum TurnDirection { NONE, LEFT, RIGHT };

// Motor and sensor configuration
extern MotorConfig leftMotor;
extern MotorConfig rightMotor;
extern IRSensorConfig irLeft;
extern IRSensorConfig irCenter;
extern IRSensorConfig irRight;

// Constants
extern const int threshold;
extern const int baseSpeedLeft;
extern const int baseSpeedRight;
extern const int turnSpeed;
extern const int turnDelay;
extern const int settleDelay;
extern const unsigned long turnStuckTimeout;
extern const unsigned long boostDuration;
