CXX = g++
TARGET = ataxx.exe
OBJECTS = bin/eval.o bin/search_tree.o bin/board.o bin/main.o bin/transposition_table.o bin/interface.o 

%.o: ../src/%.cpp
	$(CXX) -std=gnu++11 -O3 -Wall -c $^ -o $@

all: $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
	
clear:
	del bin