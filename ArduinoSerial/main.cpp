#include "ArduinoInterface.h"
#include <string>
#include <iostream>

int main() {
    Arduino arduino("COM35");           // Blocking w/timeout. Use

    if (!arduino.connected()) {               // Check connection
        exit(0);
    }

    arduino.write("$START\r\n");
    waitForInput(arduino, "$CONT2\r\n");

    std::cout << "asdf\n";
//    std::string userInput;
//    std::string arduinoInput;
//
//    // Run for a while
//    while (userInput != "end") {
//        // If the user enters something, send to arduino
//        if (asyncInput(userInput)) {
//            std::cout << "User entered: " << userInput << std::endl;
//            arduino.write(userInput + "\r\n");
//        }
//
//        // Check for data from the arduino
//        if(arduino.readLine(arduinoInput, "$")) {
//            std::cout << "Data from arduino: " << arduinoInput << std::endl;
//        }
//
//
//        std::string a;
//        while(!arduino.readLine(a));
//    }

    return 0;
}






