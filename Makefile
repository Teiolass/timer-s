CC = g++
FLAGS_LIB = -lsfml-graphics -lsfml-system -lsfml-window `pkg-config --cflags --libs libnotify`
FLAGS = -Wall

FILES = timer.cpp

out: $(FILES)
	$(CC) -o timer $(FLAGS) $(FLAGS_LIB) $(FILES)

.PHONY: clean

clean:
	rm out
