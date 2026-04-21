CXX = g++
CXXFLAGS = -std=c++17 -Wall
LIBS = $(shell pkg-config --cflags --libs sfml-all)

SRC = main.cpp
OUT = app

all:
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)