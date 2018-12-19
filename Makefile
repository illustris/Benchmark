CC = gcc
CFLAGS = -Wall -Wextra -O3

all: benchmark

debug: CFLAGS += -DDEBUG
debug: all

benchmark: utils.o md5.o args.o benchmark.c
	$(CC) $(CFLAGS) utils.o md5.o skipper.o input_args.o benchmark.c -o benchmark.out

md5.o: utils.o md5/md5.c md5/md5.h md5/skipper.h md5/skipper.c
	$(CC) $(CFLAGS) -l utils.o -c md5/md5.h md5/md5.c md5/skipper.h md5/skipper.c

utils.o: utils/utils.c utils/utils.h
	$(CC) $(CFLAGS) -c utils/utils.h utils/utils.c

args.o: args/input_args.h args/input_args.c utils.o
	$(CC) $(CFLAGS) -c args/input_args.h args/input_args.c -l utils.o

clean:
	rm *.o; cd md5; rm *.gch; cd ../utils; rm *.gch; cd ../args; rm *.gch; cd ../;