# Compiler
CXX = g++

# Source files
SRC = FunctIn.cpp ErrorHandler.cpp Token.cpp Tokenizer.cpp Interpreter.cpp

# Output executable
OUT = FunctIn

# Detect OS
ifeq ($(OS),Windows_NT)
	OUT := $(OUT).exe
endif

# Build target
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) -o $@ $^

# Clean target
clean:
	rm -f FunctIn FunctIn.exe