
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SRC = $(wildcard src/*.cpp) $(wildcard src/WindowController/*.cpp)
TARGET = game.exe

.PHONY: all run

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)
