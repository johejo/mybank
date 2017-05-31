CC = gcc
PROGRAM = mybank
CFLAGS = -Wall -lpthread
OBJS = main.o
$(PROGRAM) : $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(CFLAGS)
main.o : main.c defs.h
	$(CC) -c $(CFLAGS) main.c

clean:
	-rm -rf $(OBJS) $(PROGRAM)