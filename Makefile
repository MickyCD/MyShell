CC = gcc
CFLAGS = -Wall -Wextra -g

MyShell: MyShell.c
	$(CC) $(CFLAGS) MyShell.c -o MyShell

clean:
	rm -f MyShell