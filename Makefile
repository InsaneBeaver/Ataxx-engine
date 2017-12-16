CXX = g++
TARGET = ataxx.exe
OBJECTS = bin/eval.o bin/search.o bin/board.o bin/main.o

%.o: ../src/%.cpp
	$(CXX) -std=gnu++11 -O3 -c $^ -o $@

all: $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
	
clear:
	del bin\*.o