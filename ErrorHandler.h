#pragma once

#include <string>

using namespace std;

class ErrorHandler {
public:
    ErrorHandler();
    static string colorText(string color, string text);
    static void errorWithLine(string message, int line);
    static void error(string message);
    static void warningWithLine(string message, int line);
    static void warning(string message);
    static void terminate();
};