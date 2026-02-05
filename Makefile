CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic

TARGET = server_app.exe
SRCS = main.c server.c
OBJS = main.o server.o

ifeq ($(OS), Windows_NT)
	TARGET := $(TARGET)
	LDFLAGS = -lws2_32
else
	LDFLAGS =
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.c server.h
	$(CC) $(CFLAGS) -c main.c -o main.o

server.o: server.c server.h
	$(CC) $(CFLAGS) -c server.c -o server.o

clean:
	rm -f $(OBJS) $(TARGET) *.exe

run:$(TARGET)
	.\$(TARGET)
