CXX := g++
SRC := $(wildcard *.cpp)
OUT := output

CXXFLAGS := -std=c++17
LDFLAGS := -lncursesw
DEBUG_FLAGS := -g -Wall -Wextra -Wno-unused
RUN_FLAGS := map1.txt

# .PHONY: makes sure that make doesn't confuse these commands with target cpp files.
.PHONY: all debug run drun clean leaks calls heap

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

debug:
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT) $(RUN_FLAGS)

drun: debug
	./$(OUT) $(RUN_FLAGS)

# ---------------------------------------------------------------------------
# === VALGRIND PROFILING TOOLS ===
# These targets run your app with Valgrind to check for performance issues.
# They all depend on the 'debug' build to get meaningful line numbers.
# ---------------------------------------------------------------------------

# Target to check for memory leaks and invalid memory access.
# This gives you allocation/deallocation counts at the end.
leaks: debug
	@echo "--- Running Valgrind Memcheck to find memory leaks... ---"
	valgrind --leak-check=full ./$(OUT) $(RUN_FLAGS)

# Target to profile function calls to count copies, moves, etc.
calls: debug
	@echo "--- Running Valgrind Callgrind to count function calls... ---"
	valgrind --tool=callgrind ./$(OUT) $(RUN_FLAGS)
	@echo "--- Callgrind finished. A 'callgrind.out.PID' file was created. ---"
	@echo "--- Analyze it by running: callgrind_annotate callgrind.out.PID ---"
	@echo "--- (Replace PID with the number in the generated filename)      ---"


# Target to profile heap memory usage over the lifetime of the app.
# Perfect for seeing the impact of std::vector resizing.
heap: debug
	@echo "--- Running Valgrind Massif to profile heap usage... ---"
	valgrind --tool=massif ./$(OUT) $(RUN_FLAGS)
	@echo "--- Massif finished. A 'massif.out.PID' file was created. ---"
	@echo "--- Analyze it by running: ms_print massif.out.PID       ---"
	@echo "--- (Replace PID with the number in the generated filename) ---"

clean:
	rm -f $(OUT) callgrind.out.* massif.out.*