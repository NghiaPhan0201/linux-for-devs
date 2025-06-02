CC = gcc
CFLAGS = -Iinclude -Wall
SRC = src
OBJ = obj
BIN = bin

$(shell mkdir -p $(OBJ) $(BIN))

SERVER_OBJS = $(OBJ)/tcp_server.o $(OBJ)/server_main.o
CLIENT_OBJS = $(OBJ)/tcp_client.o $(OBJ)/client_main.o

all: $(BIN)/server $(BIN)/client

$(BIN)/server: $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $@

$(BIN)/client: $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)

.PHONY: all clean
