flags := -g -Wall -Wextra -fanalyzer

all:
	clang++ main.cpp -std=c++20 \
	-I/opt/homebrew/opt/sfml/include \
	-L/opt/homebrew/opt/sfml/lib \
	-lsfml-graphics -lsfml-window -lsfml-system \
	-o main

start: all
	./main

run: all
	./main

clean:
	rm -rf main main.dSYM
