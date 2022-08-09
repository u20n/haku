
# v this is the same as build/inc
LNK = -lncurses -lpthread
G = g++
W = -Wall

unix: $(_HEADERS)
	$(G) -std=c++20 $(W) main.cpp -o haku.out $(LNK)

clean:
	rm -f haku.out
