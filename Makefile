


CC = gcc


CFLAGS = -Wall


OUTPUT = echo_server


SRC = echo.c


all:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC) -lws2_32


clean:
	del $(OUTPUT).exe
