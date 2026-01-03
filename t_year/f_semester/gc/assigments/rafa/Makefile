CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lglfw -lGLEW -lGL -lm
TARGET = build/median_filter
SRC = src/main.cpp src/shader.cpp
INCLUDES = -Iinclude

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET) images/test.jpg

clean:
	rm -f $(TARGET)

.PHONY: all run clean