#ifndef ARDUINOSERIAL_ARDUINOINTERFACE_H
#define ARDUINOSERIAL_ARDUINOINTERFACE_H

#include "string"
#include <string>
#include <iostream>
#include <chrono>
#include <future>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>



/**
 * Async input code
 */

/**
 * Used for async cin stuff
 */
std::future<std::string> future;
bool futureActive = false;

/**
 * Get std string from cin
 * @return user input
 */
static std::string getCin() {
    std::string input;
    std::cin >> input;
    return input;
}

/**
 * Nonblocking cin
 * @param out[out] user input
 * @return if data was received
 */
bool asyncInput(std::string &out) {
    if (!futureActive) {
        future = std::async(getCin);
        futureActive = true;
        return false;
    }
    if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        out = future.get();
        futureActive = false;
        return true;
    }
    return false;
}




/**
 * Serial LIB
 */


#define ARDUINO_WAIT_TIME 2000

class Serial {
public:
    //Serial comm handler
    HANDLE hSerial;
    //Connection status
    bool connected;
    //Get various information about the connection
    COMSTAT status;
    //Keep track of last error
    DWORD errors;

public:
    //Initialize Serial communication with the given COM port
    explicit Serial(const char *portName);

    //Close the connection
    ~Serial();

    int Available() {
        return ClearCommError(this->hSerial, &this->errors, &this->status);
    }

    //Read data in a buffer, if nbChar is greater than the
    //maximum number of bytes available, it will return only the
    //bytes available. The function return -1 when nothing could
    //be read, the number of bytes actually read.
    int ReadData(char *buffer, unsigned int nbChar);

    //Writes data from a buffer through the Serial connection
    //return true on success.
    bool WriteData(const char *buffer, unsigned int nbChar);

    //Check if we are actually connected
    bool IsConnected();
};

Serial::Serial(const char *portName) {
    //We're not yet connected
    this->connected = false;

    //Try to connect to the given port throuh CreateFile
    this->hSerial = CreateFile(portName,
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

    //Check if the connection was successfull
    if (this->hSerial == INVALID_HANDLE_VALUE) {
        //If not success full display an Error
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {

            //Print Error if neccessary
            printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        } else {
            printf("ERROR!!!");
        }
    } else {
        //If connected we try to set the comm parameters
        DCB dcbSerialParams = {0};

        //Try to get the current
        if (!GetCommState(this->hSerial, &dcbSerialParams)) {
            //If impossible, show an error
            printf("failed to get current m_serial parameters!\n");
        } else {
            //Define m_serial connection parameters for the arduino board
            dcbSerialParams.BaudRate = CBR_9600;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;
            //Setting the DTR to Control_Enable ensures that the Arduino is properly
            //reset upon establishing a connection
            dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

            //Set the parameters and check for their proper application
            if (!SetCommState(hSerial, &dcbSerialParams)) {
                printf("ALERT: Could not set Serial Port parameters\n");
            } else {
                //If everything went fine we're connected
                this->connected = true;
                //Flush any remaining characters in the buffers
                PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
                //We wait 2s as the arduino board will be reseting
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }

}

Serial::~Serial() {
    //Check if we are connected before trying to disconnect
    if (this->connected) {
        //We're no longer connected
        this->connected = false;
        //Close the m_serial handler
        CloseHandle(this->hSerial);
    }
}

int Serial::ReadData(char *buffer, unsigned int nbChar) {
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //Check if there is something to read
    if (this->status.cbInQue > 0) {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if (this->status.cbInQue > nbChar) {
            toRead = nbChar;
        } else {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if (ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL)) {
            return bytesRead;
        }

    }

    //If nothing has been read, or that an error was detected return 0
    return 0;

}


bool Serial::WriteData(const char *buffer, unsigned int nbChar) {
    DWORD bytesSend;

    //Try to write the buffer on the Serial port
    if (!WriteFile(this->hSerial, (void *) buffer, nbChar, &bytesSend, 0)) {
        //In case it don't work get comm error and return false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    } else
        return true;
}

bool Serial::IsConnected() {
    //Simply return the connection status
    return this->connected;
}


/**
 * Provides a serial abstraction that is easy to work with
 *
 * @class Arduino
 */
class Arduino {
private:
    std::string lineBuff;
    static const int m_bufSize = 2048;
    char m_buf[m_bufSize] = "";       // Overkill
    Serial *m_serial;
public:
    /**
     * Create and connect to the arduino
     * @param port com port to connect to (ie "COM35")
     */
    explicit Arduino(const char *port) {
        std::string portStr = R"(\\.\)" + std::string(port);
        m_serial = new Serial(portStr.c_str());
    }

    /**
     * Non-blocking read, returns empty string if nothing was available
     * @return
     */
    std::string read() {
        memset(&m_buf, '\0', m_bufSize);
        if (m_serial->Available()) {
            m_serial->ReadData(m_buf, m_bufSize - 1);
        }
        return m_buf;
    }

    /**
     * Send a string to the arduino
     * @param msg message to send
     */
    void write(const std::string &msg) const {
        m_serial->WriteData(msg.c_str(), msg.length());
    }

    /**
     * If the com port was opened properly
     * @return
     */
    bool connected() const {
        return m_serial->IsConnected();
    }

    /**
     * Reads a line starting with a flag and ending in a newline
     * @param output[out] buffer to save data
     * @param startFlag[in] flag to look for
     * @return if new data was saved in output
     */
    bool readLine(std::string &output, const std::string &startFlag = "") {
        // Read any new data
        lineBuff += read();

        // Clip off anything before a start delimiter
        if (!startFlag.empty()) {
            int flagLoc = lineBuff.find(startFlag);
            if (flagLoc != std::string::npos) {
                lineBuff = lineBuff.substr(flagLoc);
            } else {
                lineBuff = "";
                return false;
            }
        }

        // Remove a full line from the buffer if there is one
        int endLoc = lineBuff.find('\n');
        if (endLoc != std::string::npos) {
            output = lineBuff.substr(0, endLoc + 1);
            lineBuff = lineBuff.substr(endLoc + 1);
            return true;
        }
        return false;
    }


};

void waitForInput(Arduino &arduino, const std::string& arduinoMessage) {
    std::string userInput;
    std::string arduinoInput;
    while (userInput != "continue" && arduinoInput != arduinoMessage) {
        asyncInput(userInput);
        arduino.readLine(arduinoInput, "$");
    }
}

#endif //ARDUINOSERIAL_ARDUINOINTERFACE_H
