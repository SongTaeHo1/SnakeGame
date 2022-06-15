all: snakeGame

snakeGame: main.cpp Map.cpp Snake.cpp
	g++ -o snakeGame main.cpp Map.cpp Snake.cpp -lncurses

clean:
		rm -rf *.o snakeGame
