CC = gcc
CFLAGS = -Wall -Wextra -O3

all: main clean

debug: CFLAGS += -DDEBUG -g
debug: all

main: utils.o md5.o breaker.o benchmark.o args.o main.c
	$(CC) $(CFLAGS) utils.o skipper.o input_args.o md5.o benchmark.o breaker.o main.c -o benchmark.out

benchmark.o: skipper.o benchmark.h benchmark.c
	$(CC) $(CFLAGS) -c benchmark.h benchmark.c

breaker.o:
	$(CC) $(CFLAGS) -c breaker.h breaker.c

skipper.o:
	$(CC) $(CFLAGS) -c md5/skipper.h md5/skipper.c 

md5.o:
	$(CC) $(CFLAGS) -c md5/md5.h md5/md5.c

utils.o:
	$(CC) $(CFLAGS) -c utils/utils.h utils/utils.c

args.o:
	$(CC) $(CFLAGS) -c args/input_args.h args/input_args.c

clean:
	rm *.o; rm *.gch; rm ./*/*.gch;
