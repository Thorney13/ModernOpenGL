#include "arduinoController.h"
#include <iostream>
#include <cstdlib>

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

float ArduinoController::readPot()
{
    // We assume the Arduino sends a full line (like "512\n") representing the analog value.
    char buffer[32] = { 0 };
    int n = arduino.readSerialPort(buffer, 31);  // try to read up to 31 characters
    static float lastPot = 0.0f;
    if (n <= 0)
        return lastPot; // if nothing new, return previous value

    buffer[n] = '\0';
    int analogValue = std::atoi(buffer);  // convert to integer
    // Normalize (assumes ADC range of 0-1023)
    lastPot = static_cast<float>(analogValue) / 1023.0f;
    // Snap the value to 0 or 1 if it's very close
    if (lastPot >= 0.995f)
        return 1.0f;
    else if (lastPot <= 0.005f)
        return 0.0f;
    return lastPot;
}