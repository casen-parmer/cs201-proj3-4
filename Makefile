CXX      := clang++
CXXFLAGS := -g -Wall -Wextra -std=c++20 \
            -I./code -I./code/classes -I./code/structures -I./code/tools \
            -I/opt/homebrew/opt/sfml/include
LDFLAGS  := -L/opt/homebrew/opt/sfml/lib \
            -lsfml-graphics -lsfml-window -lsfml-system

SRCS := code/main.cpp \
        $(wildcard code/classes/*.cpp) \
        $(wildcard code/structures/*.cpp) \
        $(wildcard code/tools/*.cpp)

build:
	mkdir -p output
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o output/main

start: build
	./output/main

run: build
	./output/main

clean:
	rm -rf output