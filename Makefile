flags := -g -Wall -Wextra -fanalyzer

build:
	clang++ code/main.cpp -I./code -std=c++20 \
	-I/opt/homebrew/opt/sfml/include \
	-L/opt/homebrew/opt/sfml/lib \
	-lsfml-graphics -lsfml-window -lsfml-system \
	-o output/main

start: build
	./output/main

run: build
	./output/main

clean:
	rm -rf output