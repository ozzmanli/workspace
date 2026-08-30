CC := gcc
CXX := g++
CFLAGS := -Wall -Wextra
CXXFLAGS := -Wall -Wextra -std=c++17
PYTHON := python3

C_DIR := playgroundC
CPP_DIR := playgroundC++
PY_DIR := playgroundPython

# Auto-discover every problem file in each language folder, so adding a new
# problem (e.g. playgroundC/twoSum.c) just works - nothing to edit here.
C_SRCS := $(wildcard $(C_DIR)/*.c)
CPP_SRCS := $(wildcard $(CPP_DIR)/*.cpp)
PY_SRCS := $(wildcard $(PY_DIR)/*.py)

C_BINS := $(patsubst $(C_DIR)/%.c,$(C_DIR)/bin/%,$(C_SRCS))
CPP_BINS := $(patsubst $(CPP_DIR)/%.cpp,$(CPP_DIR)/bin/%,$(CPP_SRCS))

# --- Tests ---
DOCTEST_INC := $(CPP_DIR)/third_party
CPP_TEST_SRC := $(CPP_DIR)/tests/test_sandbox.cpp
CPP_TEST_BIN := $(CPP_DIR)/bin/test_sandbox
C_TEST_SRC := $(C_DIR)/tests/test_recursiveStringReversal.c
C_TEST_BIN := $(C_DIR)/bin/test_recursiveStringReversal

.PHONY: all build run clean test test-c test-cpp test-python

all: build

build: $(C_BINS) $(CPP_BINS)

$(C_DIR)/bin/%: $(C_DIR)/%.c
	@mkdir -p $(C_DIR)/bin
	$(CC) $(CFLAGS) -o $@ $<

$(CPP_DIR)/bin/%: $(CPP_DIR)/%.cpp
	@mkdir -p $(CPP_DIR)/bin
	$(CXX) $(CXXFLAGS) -o $@ $<

run: build
	@for b in $(C_BINS); do echo "--- $$b ---"; ./$$b; done
	@for b in $(CPP_BINS); do echo "--- $$b ---"; ./$$b; done
	@for p in $(PY_SRCS); do echo "--- $$p ---"; $(PYTHON) $$p; done

test: test-c test-cpp test-python

test-c: $(C_TEST_BIN)
	@echo "--- C tests ---"
	@./$(C_TEST_BIN)

$(C_TEST_BIN): $(C_TEST_SRC) $(C_DIR)/recursiveStringReversal.c
	@mkdir -p $(C_DIR)/bin
	$(CC) $(CFLAGS) -o $@ $(C_TEST_SRC)

test-cpp: $(CPP_TEST_BIN)
	@echo "--- C++ tests ---"
	@./$(CPP_TEST_BIN)

$(CPP_TEST_BIN): $(CPP_TEST_SRC) $(CPP_DIR)/sandbox.cpp
	@mkdir -p $(CPP_DIR)/bin
	$(CXX) $(CXXFLAGS) -I $(DOCTEST_INC) -o $@ $(CPP_TEST_SRC)

test-python:
	@echo "--- Python tests ---"
	@$(PYTHON) -m unittest discover -s $(PY_DIR)/tests -p "test_*.py" -v

clean:
	rm -rf $(C_DIR)/bin $(CPP_DIR)/bin
	find $(PY_DIR) -name '__pycache__' -exec rm -rf {} +
