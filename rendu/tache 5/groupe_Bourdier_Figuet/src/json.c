/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * 
 * Json librairy minify
 *
 */

#define _GNU_SOURCE //to avoid c99 related warnings
#include "json.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>

// Display the json 
void print_array(struct Json j1)
{
  printf("{\n");
  printf("\t\"id\": %s,\n", j1.id);
  printf("\t\"code\": %s,\n", j1.code);
  printf("\t\"valeurs\": [\n");
	for (int i = 0; i < NUMBER_OF_STRING; i++)
	{
    if(j1.valeurs[i][0] != '\0') {
      printf("\t\t%s,\n", j1.valeurs[i]);
    }
	}
  printf("\t]\n");
  printf("}\n");
}

// Convert json to str
char * toString(struct Json j1) {
  static char raw[255];
  sprintf(raw, "{\"id\":%s,\"code\":%s,\"valeurs\":[", j1.id, j1.code);
  for (int i = 0; i < NUMBER_OF_STRING; i++)
	{
    if(j1.valeurs[i][0] != '\0') {
      if(i > 0) {
        strcat(raw, ",");
      }
      strcat(raw, j1.valeurs[i]);
    }
	}
  strcat(raw, "]}");
  return raw;
}

// Validate a string in json format
bool validator(char element[]) {
  bool res = true;
  if(element[0] == '"' && element[strlen(element) - 1] == '"') {
    //Valide pour une string
    //printf("str => %s\n", element);
    if(element[1] == '"' || element[strlen(element) - 2] == '"') {
      res = false;
    }
  } else {
    int num = atoi(element);
    if(num == 0 && element[0] != '0') {
      res = false;
      //String sans ""
      //printf("error => %s\n", element);
    } else {
      //Nombre
      //printf("number => %s\n", element);
      res = true;
    }
  }
  return res;
}

// Check and convert string into a json object
struct Json parse(char src[])
{
  struct Json json = { "", "", { "" }};
  char delim[] = ":,{[]}";
  char *ptr = strtok(src, delim);
  int i = 1;
  
  while(ptr != NULL) {
    if(validator(ptr) == true){
      // Pour chaque valeur valide dans le string (src)
      if(i == 1) { // indice pour la propriété id
        if(strcmp(ptr, "\"id\"") != 0) {
          strcpy(json.id, "\"error\"");
          strcpy(json.valeurs[0], "\"Vous n'avez pas défini la propiété id !\"");
          break;
        }
      } else if(i == 2) { // indice pour l'id
        char *id = strdup(ptr);
        strcpy(json.id, id);
      } else if(i == 3) { // indice pour la propriété code
        if(strcmp(ptr, "\"code\"") != 0) {
          char *code = strdup(ptr);
          strcpy(json.code, "\"error\"");
          strcpy(json.valeurs[0], "\"Vous n'avez pas défini la propiété code !\"");
          break;
        }
      } else if(i == 4) { // indice pour le code
        if(strcmp(ptr, "\"nom\"") == 0 || strcmp(ptr, "\"message\"") == 0 || strcmp(ptr, "\"couleurs\"") == 0 || strcmp(ptr, "\"balises\"") == 0 || strcmp(ptr, "\"calcul\"") == 0 || strcmp(ptr, "\"plot\"") == 0 ) {
          char *code = strdup(ptr);
          strcpy(json.code, code);
        } else {
          char *code = "\"error\"";
          strcpy(json.valeurs[0], "\"Vous valeur de code est incorrect !\"");
          strcpy(json.valeurs[1], "\"Valeurs disponible :\"");
          strcpy(json.valeurs[2], "\"nom\"");
          strcpy(json.valeurs[3], "\"message\"");
          strcpy(json.valeurs[4], "\"couleurs\"");
          strcpy(json.valeurs[5], "\"balises\"");
          strcpy(json.valeurs[6], "\"calcul\"");
          strcpy(json.valeurs[7], "\"plot\"");
          strcpy(json.code, code);
          break;
        }
      } else if(i == 5) { // indice pour la propriété valeurs
        char *temp = strdup(ptr);
        if(strcmp(ptr, "\"valeurs\"") != 0) {
          char *code = strdup(ptr);
          strcpy(json.code, "\"error\"");
          strcpy(json.valeurs[0], "\"Vous n'avez pas défini la propiété valeurs !\"");
          break;
        }
      }
      else if(i >= 6) { // indice pour les valeurs
        char *temp = strdup(ptr);
        strcpy(json.valeurs[i-6], temp);
      }
    } else {
      char *code = "\"error\"";
      strcpy(json.code, code);
      strcpy(json.valeurs[0], "\"Définition du json incorrect !\"");
      break;
    }
    ptr = strtok(NULL, delim);
    i++;
  }
  return json;
}