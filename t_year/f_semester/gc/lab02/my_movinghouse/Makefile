CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lglfw -lGLEW -lGL

TARGET = build/main
SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
