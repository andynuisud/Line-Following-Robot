// MotorControl.h
#pragma once
#include "Config.h"

void setupMotor(const MotorConfig& motor);
void drive(const MotorConfig& motor, bool forward, int speed);
void stopMotor(const MotorConfig& motor);
void moveForward();
void turnLeft();
void turnRight();
void circleLeft();
void circleRight();
void stopAllMotors();
void boostForward();
