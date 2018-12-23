CC = gcc
CFLAGS = -Wall -Wextra -O3

all: main clean

debug: CFLAGS += -DDEBUG
debug: all

main: utils.o benchmark.o args.o main.c
	$(CC) $(CFLAGS) utils.o skipper.o input_args.o md5.o benchmark.o main.c -o benchmark.out

benchmark.o: utils.o md5.o benchmark.h benchmark.c
	$(CC) $(CFLAGS) -l utils.o -lskipper.o -c benchmark.h benchmark.c

md5.o: utils.o md5/md5.c md5/md5.h md5/skipper.h md5/skipper.c
	$(CC) $(CFLAGS) -l utils.o -c md5/md5.h md5/md5.c md5/skipper.h md5/skipper.c

utils.o: utils/utils.c utils/utils.h
	$(CC) $(CFLAGS) -c utils/utils.h utils/utils.c

args.o: args/input_args.h args/input_args.c utils.o
	$(CC) $(CFLAGS) -l utils.o -c args/input_args.h args/input_args.c

clean:
	rm *.o; rm *.gch; rm ./*/*.gch;