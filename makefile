CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS =
LIBS =

EXEC = bank_system
TEST_EXEC = bank_tests

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
TEST_SRC = $(wildcard tests/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

GTEST_DIR = /path/to/gtest
GTEST_LIBS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

.PHONY: all clean debug release test coverage

all: release

release: CXXFLAGS += -O2
release: $(EXEC)

debug: CXXFLAGS += -g
debug: $(EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

$(TEST_EXEC): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $@ $(GTEST_LIBS)

coverage:
	$(MAKE) clean
	$(MAKE) test CXXFLAGS='--coverage $(CXXFLAGS)'
	gcov $(SRC)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage

clean:
	rm -f $(EXEC) $(TEST_EXEC) $(OBJ) $(TEST_OBJ) *.gcda *.gcno *.info
