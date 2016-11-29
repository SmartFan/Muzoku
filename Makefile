NAME=Muzoku
CC=gcc
FLAGS=-c -O3 -std=c11 -static -w -finline-functions -m64

all: dancing_links.o muzoku.o muzoku_game.o 
	$(CC) -o $(NAME) dancing_links.o muzoku.o muzoku_game.o -lpthread

dancing_links.o:
	$(CC) dancing_links.c $(FLAGS)

muzoku.o:
	$(CC) muzoku.c $(FLAGS)

muzoku_game.o:
	$(CC) muzoku_game.c $(FLAGS)

clean:
	rm -f $(NAME) *.o *.log
