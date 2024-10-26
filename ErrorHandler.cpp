#include "ErrorHandler.h"
#include <iostream>

using namespace std;

ErrorHandler::ErrorHandler() {}

/**
 * Colors the text with the specified color.
 * 
 * @param color The color to use.
 * @param text The text to color.
 * @return The colored text.
 */
string ErrorHandler::colorText(string color, string text) {
    string colorCode;
    if (color == "red") {
        colorCode = "\033[31m"; // Red color
    } else if (color == "yellow") {
        colorCode = "\033[33m"; // Yellow color
    } else {
        colorCode = "\033[0m"; // Default color
    }
    return colorCode + text + "\033[0m"; // Reset color
}

/**
 * Displays an error message with the specified line number.
 * 
 * @param message The error message to display.
 * @param line The line number where the error occurred.
 */
void ErrorHandler::errorWithLine(string message, int line) {
    cerr << colorText("red", "Error (line " + to_string(line) + "): " + message) << endl;
    terminate();
}

/**
 * Displays an error message.
 * 
 * @param message The error message to display.
 */
void ErrorHandler::error(string message) {
    cerr << colorText("red", "Error: " + message) << endl;
    terminate();
}

/**
 * Displays a warning message with the specified line number.
 * 
 * @param message The warning message to display.
 * @param line The line number where the warning occurred.
 */
void ErrorHandler::warningWithLine(string message, int line) {
    cerr << colorText("yellow", "Warning (line " + to_string(line) + "): " + message) << endl;
}

/**
 * Displays a warning message.
 * 
 * @param message The warning message to display.
 */
void ErrorHandler::warning(string message) {
    cerr << colorText("yellow", "Warning: " + message) << endl;
}

/**
 * Terminates the program when a fatal error occurs.
 */
void ErrorHandler::terminate() {
    exit(EXIT_FAILURE);
}