# File:   Makefile
# Author: Darcy Maddren
# Date:   29 September 2020
# Descr:  Makefile for Encrypt-Decrypt-Message

# Definitions.
CFLAGS = -g -std=c99 -Wall -Werror


# Main target.
agents: agents.o
	gcc agents.o -o agents

# Intermediate targets
agents.o: agents.c agents.h
	gcc $(CFLAGS) -c agents.c

# Run the program ('make program')
program: 
	./agents

# Clean up target ('make clean')
clean:
	rm *.o

