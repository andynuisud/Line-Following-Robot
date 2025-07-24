#include "MotorControl.h"

void setupMotor(const MotorConfig& motor) {
    pinMode(motor.in1, OUTPUT);
    pinMode(motor.in2, OUTPUT);
    pinMode(motor.pwm, OUTPUT);
}

void drive(const MotorConfig& motor, bool forward, int speed) {
    digitalWrite(motor.in1, forward);
    digitalWrite(motor.in2, !forward);
    analogWrite(motor.pwm, speed);
}

void stopMotor(const MotorConfig& motor) {
    digitalWrite(motor.in1, LOW);
    digitalWrite(motor.in2, LOW);
    analogWrite(motor.pwm, 0);
}

void moveForward() {
    drive(leftMotor, true, baseSpeedLeft);
    drive(rightMotor, true, baseSpeedRight);
    delay(settleDelay);
}

void turnLeft() {
    stopMotor(leftMotor);
    drive(rightMotor, true, turnSpeed);
    delay(turnDelay);
}

void turnRight() {
    drive(leftMotor, true, turnSpeed);
    stopMotor(rightMotor);
    delay(turnDelay);
}

void circleLeft() {
    drive(leftMotor, false, baseSpeedLeft);
    drive(rightMotor, true, baseSpeedRight);
    delay(settleDelay);
}

void circleRight() {
    drive(leftMotor, true, baseSpeedLeft);
    drive(rightMotor, false, baseSpeedRight);
    delay(settleDelay);
}

void stopAllMotors() {
    stopMotor(leftMotor);
    stopMotor(rightMotor);
    delay(settleDelay);
}

void boostForward() {
    drive(leftMotor, true, 255);
    drive(rightMotor, true, 255);
    delay(boostDuration);
    drive(leftMotor, true, baseSpeedLeft);
    drive(rightMotor, true, baseSpeedRight);
}
