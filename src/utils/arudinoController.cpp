#include "arduinoController.h"
#include <iostream>

ArduinoController::ArduinoController(const char* portName)
    : arduino(portName), lastState(0)
{
    // Optionally, add error handling or initialization messages here
}

int ArduinoController::readState()
{
    char buffer[2] = { 0 };
    int n = arduino.readSerialPort(buffer, 1);
    while(n > 0) {
        buffer[n] = '\0';
        //std::cout << "ArduinoController received: " << buffer[0] << std::endl;
        if (buffer[0] == '1')
            lastState = 1;
        else if (buffer[0] == '0')
            lastState = 0;
        // Try reading again in case multiple bytes are waiting
        n = arduino.readSerialPort(buffer, 1);
    }
    return lastState;
}