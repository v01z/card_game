#* GNU General Public License v3.0 */
#******************************************************************************
#*
#* Name: Makefile 
#* Compiling/installing instructions for card_game project 
#*
#* Copyright (C) 2021, binary_cat, v01z@mail.ru
#*
#*****************************************************************************/

TARGET=card_game

CC=g++

DEBUG=-g

OPT=-O0

WARN=-Wall

CCFLAGS=$(DEBUG) $(OPT) $(WARN) -pipe

LD=g++

OBJS=    main.o task3.o


all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) 
    
main.o: main.cpp
	$(CC) -c $(CCFLAGS) main.cpp -o main.o

task3.o: task3.cpp
	$(CC) -c $(CCFLAGS) task3.cpp -o task3.o

clean:
	rm -rf *.o $(TARGET)

run:
	./$(TARGET)

install:
	echo 'Doesnt ready to do this yet'
