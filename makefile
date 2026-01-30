CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2

SRC_DIR   := src
BIN_DIR   := bin

MATCHER   := $(BIN_DIR)/matcher
VERIFIER  := $(BIN_DIR)/verifier
GEN       := $(BIN_DIR)/gen

all: $(MATCHER) $(VERIFIER) $(GEN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(MATCHER): $(SRC_DIR)/matcher.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(VERIFIER): $(SRC_DIR)/verifier.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(GEN): $(SRC_DIR)/gen.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR) *.out in.txt out.txt matcher_times.csv verifier_times.csv result/match.out

.PHONY: all clean example check gen taskc



## extra targets
## Part A & B: Build and run matcher and verifier on example input
## Build and run matcher on the example input
example: all
	./$(MATCHER) < data/example.in > result/match.out

# Build and run verifier on example output
check: all
	./$(MATCHER) < data/example.in > result/match.out
	( cat data/example.in; echo; cat result/match.out ) | ./$(VERIFIER)


# Part C: Generate inputs and collect matcher, verifier timing data
scale-matcher: all
	@echo "n,time" > matcher_times.csv
	@for n in 1 2 4 8 16 32 64 128 256 512; do \
		echo "Running matcher for n=$$n"; \
		./$(GEN) $$n > in.txt; \
		/usr/bin/time -f "$$n,%e" ./$(MATCHER) < in.txt > /dev/null 2>> matcher_times.csv; \
	done

scale-verifier: all
	@echo "n,time" > verifier_times.csv
	@for n in 1 2 4 8 16 32 64 128 256 512; do \
		echo "Running verifier for n=$$n"; \
		./$(GEN) $$n > in.txt; \
		./$(MATCHER) < in.txt > out.txt; \
		cat in.txt out.txt | /usr/bin/time -f "$$n,%e" ./$(VERIFIER) > /dev/null 2>> verifier_times.csv; \
	done
