CC=g++
CFLAGS=-Wall -Wextra -pedantic -g
CFALLEGRO=-lallegro-5 -lallegro_font-5 -lallegro_image-5

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
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ $(CFALLEGRO)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -I $(HDR) -c $< -o $@ $(CFALLEGRO)

$(BIN):
	mkdir $@

$(OBJ):
	mkdir $@

test: $(TSB) $(OBJ)

test: $(TSB) $(TSO) $(OBJ) $(OBJS) $(TNAME)
	./$(TSB)/$(TNAME)

$(TNAME): $(OBJS) $(TSTO)
	$(CC) $(CFLAGS) $^ -o $(TSB)/$@ -lgtest -pthread

$(TSO)/%.o: $(TST)/%_test.cpp
	$(CC) $(CFLAGS) -I $(HDR) -c $^ -o $@ -lgtest -pthread

$(TSB):
	mkdir $@

$(TSO):
	mkdir $@

clean:
	rm -rf $(OBJ) $(BIN) $(TSB) $(TSO) out
