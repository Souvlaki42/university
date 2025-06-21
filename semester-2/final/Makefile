CXX := g++
SRC := $(wildcard *.cpp)
OUT := output

CXXFLAGS := -std=c++17
LDFLAGS := -lncursesw
DEBUG_FLAGS := -g -Wall -Wextra -Wno-unused
RUN_FLAGS := map1.txt

.PHONY: all debug run drun clean

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

debug:
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT) $(RUN_FLAGS)

drun: debug
	./$(OUT) $(RUN_FLAGS)

clean:
	rm -f $(OUT)