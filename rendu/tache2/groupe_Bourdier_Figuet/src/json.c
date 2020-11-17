/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#define _GNU_SOURCE //to avoid c99 related warnings
#include "json.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>

void print_array(struct Json j1)
{
  printf("{\n");
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

struct Json parse(char src[])
{
  printf("Parse : \n");
  struct Json json = { "", { "" }};
  char delim[] = "\":,{[]}";
  if(src[0] == '{' && src[strlen(src) - 1] == '}') {
    char valeurs[30][100];
    int i = 0;
    char *ptr = strtok(src, delim);
    ptr = strtok(NULL, delim);
    char *code = strdup(ptr);
    strcpy(json.code, code);
    ptr = strtok(NULL, delim);
    ptr = strtok(NULL, delim);
    while(ptr != NULL) {
      char *temp = strdup(ptr);
      strcpy(json.valeurs[i], temp);
      i = i + 1;
      ptr = strtok(NULL, delim);
    }
  }
  return json;
}