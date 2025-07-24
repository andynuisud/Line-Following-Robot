#pragma once
#include "Config.h"

void setupIR(const IRSensorConfig& sensor);
bool isBlack(int value);
void readIRSensors(bool& left, bool& center, bool& right);
