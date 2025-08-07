#pragma once
#include "serialPort.h"

class ArduinoController {
public:
    ArduinoController(const char* portName);
    int readState();
    float readPot();         // analog reading
private:
    SerialPort arduino;
    int lastState; // Store the last valid state
};