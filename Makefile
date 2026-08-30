CC := gcc
CXX := g++
CFLAGS := -Wall -Wextra
CXXFLAGS := -Wall -Wextra -std=c++17
PYTHON := python3

C_DIR := playgroundC
CPP_DIR := playgroundC++
PY_DIR := playgroundPython

# Auto-discover every problem file in each language folder, so adding a new
# problem just works - nothing to edit here.
#
# C and Python: one file per problem, directly in the language folder
# (e.g. playgroundC/twoSum.c).
#
# C++: each problem lives in its own subfolder (e.g. playgroundC++/ATM/,
# playgroundC++/recursiveStringReversal/), since some problems need more
# than one file (a .h alongside the .cpp) or a tests/ subfolder. The
# subfolder name doesn't have to match the .cpp filename (ATM/atm.cpp
# is a real example), so binaries are named after the .cpp file itself.
C_SRCS := $(wildcard $(C_DIR)/*.c)
CPP_SRCS := $(shell find $(CPP_DIR) -mindepth 2 -maxdepth 2 -name '*.cpp' -not -path '*/tests/*')
PY_SRCS := $(wildcard $(PY_DIR)/*.py)

C_BINS := $(patsubst $(C_DIR)/%.c,$(C_DIR)/bin/%,$(C_SRCS))
CPP_BINS := $(foreach src,$(CPP_SRCS),$(CPP_DIR)/bin/$(basename $(notdir $(src))))

# --- Tests ---
DOCTEST_INC := $(CPP_DIR)/third_party
CPP_TEST_SRC := $(CPP_DIR)/ATM/tests/test_atm.cpp
CPP_TEST_BIN := $(CPP_DIR)/bin/test_atm
C_TEST_SRC := $(C_DIR)/tests/test_recursiveStringReversal.c
C_TEST_BIN := $(C_DIR)/bin/test_recursiveStringReversal

.PHONY: all build run clean test test-c test-cpp test-python

all: build

build: $(C_BINS) $(CPP_BINS)

$(C_DIR)/bin/%: $(C_DIR)/%.c
	@mkdir -p $(C_DIR)/bin
	$(CC) $(CFLAGS) -o $@ $<

# One build rule generated per discovered C++ source file, so ATM/atm.cpp
# -> bin/atm, recursiveStringReversal/recursiveStringReversal.cpp ->
# bin/recursiveStringReversal, etc, regardless of subfolder naming.
define CPP_BUILD_RULE
$(CPP_DIR)/bin/$(basename $(notdir $(1))): $(1)
	@mkdir -p $(CPP_DIR)/bin
	$(CXX) $(CXXFLAGS) -o $$@ $$<
endef
$(foreach src,$(CPP_SRCS),$(eval $(call CPP_BUILD_RULE,$(src))))

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

$(CPP_TEST_BIN): $(CPP_TEST_SRC) $(CPP_DIR)/ATM/atm.cpp
	@mkdir -p $(CPP_DIR)/bin
	$(CXX) $(CXXFLAGS) -I $(DOCTEST_INC) -o $@ $(CPP_TEST_SRC)

test-python:
	@echo "--- Python tests ---"
	@$(PYTHON) -m unittest discover -s $(PY_DIR)/tests -p "test_*.py" -v

clean:
	rm -rf $(C_DIR)/bin $(CPP_DIR)/bin
	find $(PY_DIR) -name '__pycache__' -exec rm -rf {} +
