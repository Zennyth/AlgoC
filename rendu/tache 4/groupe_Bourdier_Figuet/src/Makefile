CC ?= gcc

COBJS ?= client.o bmp.o couleur.o json.o
SOBJS ?= serveur.o 

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	$(CC) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS) -lm

.c.o: 
	$(CC) -c $*.c -lm
