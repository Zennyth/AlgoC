CC ?= gcc

COBJS ?= client.o bmp.o couleur.o json.o
SOBJS ?= serveur.o 
UOBJS ?= unitTesting.o bmp.o couleur.o json.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client
UNITTESTING = unitTesting

all: $(SERVER) $(CLIENT) $(UNITTESTING)

$(SERVER): $(SOBJS)
	$(CC) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS) -lm

$(UNITTESTING): $(UOBJS)
	$(CC) -o $(UNITTESTING) $(UOBJS) -lm

.c.o: 
	$(CC) -c $*.c -lm
