CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
LDFLAGS = -lws2_32

TARGET = server_app.exe
SRCS = main.c server.c
OBJS = main.o server.o

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo LINK: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.c server.h
	@echo CC: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

server.o: server.c server.h
	@echo CC: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

clean:
	rm -f $(OBJS) $(TARGET)

