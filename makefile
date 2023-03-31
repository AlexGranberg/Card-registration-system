PROG=admindoor.exe
CC=gcc 
CFLAGS=-g -Wall -Werror
DEPS = SafeInput.h
OBJ = functions.o main.o SafeInput.o cardFunctions.o fileFunctions.o
 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
 
$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)