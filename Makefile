
LNK = -lncurses -L./lib/
G = g++ -std=c++20 -Wall

unix: $(_HEADERS)
	$(G) main.cpp -o hku.out $(LNK)
