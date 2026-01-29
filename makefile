CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2

SRC_DIR   := src
BIN_DIR   := bin

MATCHER   := $(BIN_DIR)/matcher
VERIFIER  := $(BIN_DIR)/verifier

all: $(MATCHER) $(VERIFIER)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(MATCHER): $(SRC_DIR)/matcher.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(VERIFIER): $(SRC_DIR)/verifier.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR) *.out output.out

.PHONY: all clean
