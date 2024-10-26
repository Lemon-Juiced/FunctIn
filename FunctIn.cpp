#include "ErrorHandler.h"
#include "Tokenizer.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

/**
 * The main function of the FunctIn interpreter.
 * 
 * The interpreter works in multiple steps:
 * 1. Set up an error handler
 * 2. Parse the command line arguments for the source file
 * 3. Parse and tokenize the source file
 * 4... TODO (imports, functions, etc.)
 */
int main(int argc, char* argv[]) {

    // Step 1.
    // Set up the ErrorHandler
    ErrorHandler errorHandler;

    // Step 2.
    // Check if the source file was provided (if not, display an error message)
    if (argc < 2) errorHandler.error("No source file provided.");

    // Since we know a file was passed, make sure its extension is .funct
    string sourceFile = argv[1];
    if (sourceFile.substr(sourceFile.find_last_of(".") + 1) != "funct") errorHandler.error("Invalid file extension. Expected .funct.");

    // Create a file stream for the source file
    ifstream fileStream(sourceFile);
    if (!fileStream.is_open()) errorHandler.error("Failed to open source file.");

    // Dump the file contents line-by-line into strings per line and place them in a map with the line number as the key
    map<int, string> sourceLines;
    string line;
    int lineNumber = 1;
    while (getline(fileStream, line)) {
        sourceLines[lineNumber] = line;
        lineNumber++;
    }

    // Step 3.
    // Tokenize the source file
    Tokenizer tokenizer;
    map<int, vector<Token>> tokens;
    for (const auto& [lineNumber, line] : sourceLines) {
        tokens[lineNumber] = tokenizer.tokenize(line);
    }

    // Step 4.
    // Interpret the tokens
    Interpreter interpreter(errorHandler);
    interpreter.interpret(tokens);

    return 0;
}