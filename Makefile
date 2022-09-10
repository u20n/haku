default: linux
# v this is the same as build/inc
LNK = -lncurses -lpthread
G = g++
W = -Wall
CF = -std=c++20 $(W) -MMD -MP

B = bin/

## all headers
HDR = $(wildcard inc/*.hpp)
SRC = $(wildcard src/*.cpp)
OBJ = $(wildcard bin/*.o)

## build objects
## - generate *fresh* dependency
## - build object (from dependency file)

OBUILD:
	$(foreach f,$(SRC),\
		$(G) -c $(CF) $(W) $f -o $(B)$(lastword $(subst /, , $(basename $f))).o $(LNK); \
	)

linux: OBUILD $(HDR) 
	$(G) $(CF) -std=c++20 $(W) $(OBJ) main.cpp -o haku.out $(LNK)

clean:
	rm -f haku.out
	rm -f bin/*.o
