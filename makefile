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
	rm -rf $(BIN_DIR) *.out output.out in.txt out.txt

.PHONY: all clean example check gen taskc

## extra targets
# Build and run matcher on the example input
example: all
	./$(MATCHER) < data/example.in > output.out

# Build and run verifier on example output
check: all
	./$(MATCHER) < data/example.in > out.txt
	cat data/example.in out.txt | ./$(VERIFIER)
