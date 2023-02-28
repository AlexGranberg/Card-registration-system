PROG=admindoor.exe
CC=gcc
CFLAGS=-g -Wall
DEPS = SafeInput.h
OBJ = menu.o main.o SafeInput.o 
 
%.o: %.c $(DEPS)
    $(CC) -c -o $@ $< $(CFLAGS)
 
$(PROG): $(OBJ)
    $(CC) -o $@ $^ $(CFLAGS)