CC=g++
CFLAGS=-Wall -Wextra -pedantic -g -fPIC -fprofile-arcs -ftest-coverage

OBJ=obj
BIN=bin
SRC=src
HDR=include
TST=test
TSB=$(TST)/bin
TSO=$(TST)/obj

SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

PNAME=pacman
TNAME=gtest

TSTS=$(wildcard $(TST)/*_test.cpp)
TSTO=$(patsubst $(TST)/%_test.cpp, $(TSO)/%.o, $(TSTS))

all: $(BIN) $(OBJ) $(PNAME)

$(PNAME): $(OBJS) main.cpp
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -I $(HDR) -c $< -o $@

$(BIN):
	mkdir -p $@

$(OBJ):
	mkdir -p $@

test: $(TSB) $(OBJ)

test: $(TSB) $(TSO) $(OBJ) $(OBJS) $(TNAME)
	./$(TSB)/$(TNAME)

$(TNAME): $(OBJS) $(TSTO)
	$(CC) $(CFLAGS) $^ -o $(TSB)/$@ -lgtest -pthread

$(TSO)/%.o: $(TST)/%_test.cpp
	$(CC) $(CFLAGS) -I $(HDR) -c $^ -o $@ -lgtest -pthread

$(TSB):
	mkdir -p $@

$(TSO):
	mkdir -p $@

gcov:
	gcov $(SRCS) main.cpp

coverage.info: gcov
	lcov --capture --directory . --output-file coverage.info

report: coverage.info
	genhtml coverage.info --output-directory out

clean:
	rm -rf $(OBJ) $(BIN) $(TSB) $(TSO) out *.gcno *.gcov coverage.info
