CC=gcc

CFLAGS= -Wall -Wextra -std=c11 -g `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -lSDL2_image -lm
VFLAGS= --track-origins=yes --leak-check=full --show-leak-kinds=all -v
DEPS = exam_v2.h
OBJS = exam_v2.o checks.o board.o gameLog.o gui.o input.o utilities.o
NAME = othello
all: othello

%o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)



create: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	rm -f $(NAME)
	rm -f *.o

remake: clean create

debug:
	valgrind $(VFLAGS) ./$(NAME)

rebug: clean create debug

play:
	./$(NAME)

