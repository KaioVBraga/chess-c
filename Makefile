CXX		  := gcc

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

# LIBRARIES	:=
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

# $(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
# 	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $^ -o $@

clean:
	-rm $(BIN)/*
