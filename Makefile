CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
SRC = $(wildcard src/*.cpp)
TARGET = game.exe

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)