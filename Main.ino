#include "Config.h"
#include "MotorControl.h"
#include "IRSensors.h"

MotorConfig leftMotor = {2, 3, 9};
MotorConfig rightMotor = {6, 5, 10};
IRSensorConfig irLeft = {A2, 49};
IRSensorConfig irCenter = {A1, 51};
IRSensorConfig irRight = {A0, 53};

const int threshold = 500;
const int baseSpeedLeft = 100;
const int baseSpeedRight = 140;
const int turnSpeed = 90;
const int turnDelay = 50;
const int settleDelay = 100;
const unsigned long turnStuckTimeout = 2000;
const unsigned long boostDuration = 200;

unsigned long turnStartTime = 0;
bool isTimingTurn = false;
TurnDirection lastTurn = NONE;

void handleLostLine() {
    stopAllMotors();
    delay(100);
    if (lastTurn == LEFT) circleLeft();
    else circleRight();
}

void setup() {
    setupMotor(leftMotor);
    setupMotor(rightMotor);
    setupIR(irLeft);
    setupIR(irCenter);
    setupIR(irRight);
    Serial.begin(9600);
}

void loop() {
    bool leftBlack, centerBlack, rightBlack;
    readIRSensors(leftBlack, centerBlack, rightBlack);

    bool allBlack = leftBlack && centerBlack && rightBlack;
    bool allWhite = !leftBlack && !centerBlack && !rightBlack;
    bool turning = (leftBlack || rightBlack) && !centerBlack;

    if (allBlack) {
        stopAllMotors();
        delay(1000);
        return;
    }

    if (allWhite) {
        handleLostLine();
        return;
    }

    if (turning) {
        if (!isTimingTurn) {
            isTimingTurn = true;
            turnStartTime = millis();
        } else if (millis() - turnStartTime >= turnStuckTimeout) {
            boostForward();
            turnStartTime = millis();
        }
    } else {
        isTimingTurn = false;
    }

    if (centerBlack && leftBlack && !rightBlack) {
        lastTurn = LEFT;
        turnLeft();
    } else if (centerBlack && rightBlack && !leftBlack) {
        lastTurn = RIGHT;
        turnRight();
    } else if (centerBlack && !leftBlack && !rightBlack) {
        moveForward();
    } else if (leftBlack && !centerBlack && !rightBlack) {
        lastTurn = LEFT;
        turnLeft();
    } else if (rightBlack && !centerBlack && !leftBlack) {
        lastTurn = RIGHT;
        turnRight();
    } else {
        if (lastTurn == LEFT) circleLeft();
        else circleRight();
    }

    delay(50);
}
