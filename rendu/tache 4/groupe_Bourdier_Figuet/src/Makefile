CC ?= gcc

COBJS ?= client.o bmp.o couleur.o json.o
SOBJS ?= serveur.o 

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
<<<<<<< HEAD
	$(CC) -o $(SERVER) $(SOBJS)

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS)

.c.o: 
	$(CC) -c $*.c

=======
	$(CC) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS) -lm

.c.o: 
	$(CC) -c $*.c -lm
>>>>>>> 4d465675faec989407a25713119323011f242fa6
