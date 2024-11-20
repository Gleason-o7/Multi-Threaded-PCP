CFLAGS = -std=c99 -pthread -Wall -Wextra

SRCS = main.c buffer.c
OBJS = $(SRCS:.c=.o) 

.PHONY: all
all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) main
