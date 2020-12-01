#ifndef __JSON_H__
#define __JSON_H__

#define NUMBER_OF_STRING 30
#define MAX_STRING_SIZE 100

#include <stdio.h>
#include <stdlib.h>

/* 
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */

// Source file
typedef struct Json {
  char code[15];
  char valeurs[NUMBER_OF_STRING][MAX_STRING_SIZE];
} Json;

void print_array(struct Json);
struct Json parse(char *);

#endif