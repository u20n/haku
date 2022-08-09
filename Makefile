
# v this is the same as build/inc
INC = -I./lib/core/inc
LNK = -lncurses -lpthread
G = g++ -std=c++20 -Wall

unix: $(_HEADERS)
	$(G) $(INC) main.cpp -o haku.out $(LNK)

clean:
	rm -f haku.out
