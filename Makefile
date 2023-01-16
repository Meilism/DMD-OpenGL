all: main.cpp
	g++ -g -Wall -std=c++17 -I./include -L./lib main.cpp -o main.exe -lglfw3 -lglad -lgdi32
	.\main