# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -I/C:/msys64/ucrt64/include

# Linker flags
LDFLAGS = -L/C:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lole32 -lcomdlg32

# Target executable
TARGET = main

# Source files
SRC = Coding/main.cpp Coding/tinyfiledialogs.c

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET)