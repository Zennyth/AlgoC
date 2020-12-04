/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"
#include "bmp.h"
#include "json.h"

void analyse(char *pathname, char *data) {
  //compte de couleurs
  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
  //strcpy(data, "{code:\"couleurs\",valeurs:[");
  char nbCouleurs[100];
  printf("Votre nombre de couleurs (max 30): ");
  fgets(nbCouleurs, 1024, stdin);
  int n = atoi(nbCouleurs);
  char temp_string[15] = "30,";
  if (n != 30) {
    sprintf(temp_string, "%i,", n);
  }
  strcat(data, temp_string);
  
  //choisir 30 couleurs
  for (count = 1; count < (n+1) && cc->size - count >0; count++) {
    if(cc->compte_bit ==  BITS32) {
      sprintf(temp_string, "\"#%02x%02x%02x\",", cc->cc.cc24[cc->size-count].c.rouge,cc->cc.cc32[cc->size-count].c.vert,cc->cc.cc32[cc->size-count].c.bleu);
    }
    if(cc->compte_bit ==  BITS24) {
      sprintf(temp_string, "\"#%02x%02x%02x\",", cc->cc.cc32[cc->size-count].c.rouge,cc->cc.cc32[cc->size-count].c.vert,cc->cc.cc32[cc->size-count].c.bleu);
    }
    strcat(data, temp_string);
  }
  data[strlen(data)-1] = '\0';
  //enlever le dernier virgule 
}

/* 
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */

int envoie_recois_message(char *pathname) {
  
  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Exemple d'entré pour couleurs
  //char typeMessage[100] = "\"couleurs\"";
  char typeMessage[100] = "";
  printf("Votre type de message (max 1000 caracteres): ");
  fgets(typeMessage, 1024, stdin);
  strtok(typeMessage, "\n");
  char message[500] = "";
  if(strcmp(typeMessage, "couleurs") == 0 || strcmp(typeMessage, "balises") == 0 || strcmp(typeMessage, "plot") == 0) {
    analyse(pathname, message);
    sprintf(data, "{\"code\":\"%s\",\"valeurs\":[%s]}", typeMessage, message);
  } else {
    // Demandez à l'utilisateur d'entrer un message
    // Exemple d'entré pour couleurs
    //char message[100] = "10,\"#123456\",\"#123456\",\"#123456\",\"#123456\",\"#123456\"";
    printf("Votre message %s (max 1000 caracteres): ", message);
    fgets(message, 1024, stdin);
    strtok(message, "\n");
    if(strcmp(typeMessage, "calcul") == 0) {
      sprintf(data, "{\"code\":\"%s\",\"valeurs\":[%s]}", typeMessage, message);
    } else {
      sprintf(data, "{\"code\":\"%s\",\"valeurs\":[\"%s\"]}", typeMessage, message);
    }
  }

  struct Json res = parse(strdup(data));

  if (strcmp(res.code, "\"error\"") == 0) {
    print_array(res);
    perror("erreur convertion json");
    return -1;
  } else {
    // Si l'entré utilisateur est bien convertissable en json alors
    int socketfd;
    int bind_status;

    struct sockaddr_in server_addr, client_addr;

    /*
    * Creation d'une socket
    */
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( socketfd < 0 ) {
      perror("socket");
      exit(EXIT_FAILURE);
    }

    //détails du serveur (adresse et port)
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //demande de connection au serveur
    int connect_status = connect(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if ( connect_status < 0 ) {
      perror("connection serveur");
      exit(EXIT_FAILURE);
    }
    int write_status = write(socketfd, data, strlen(data));
    if ( write_status < 0 ) {
      perror("erreur ecriture");
      exit(EXIT_FAILURE);
    }

    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // lire les données de la socket
    int read_status = read(socketfd, data, sizeof(data));
    if ( read_status < 0 ) {
      perror("erreur lecture ");
      return -1;
    }

    printf("%s\n", data);
  }
 
  return 0;
}

int envoie_couleurs(int socketfd, char *pathname) {
  char data[1024];
  memset(data, 0, sizeof(data));
  analyse(pathname, data);
  int write_status = write(socketfd, data, strlen(data));
  if ( write_status < 0 ) {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }
  return 0;
}

int main(int argc, char **argv) {
  int socketfd;
  int bind_status;

  struct sockaddr_in server_addr, client_addr;

  /*
   * Creation d'une socket
   */
  /*
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if ( socketfd < 0 ) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  //détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  //demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if ( connect_status < 0 ) {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }
  */
  envoie_recois_message(argv[1]);
  //envoie_couleurs(socketfd, argv[1]);
  close(socketfd);
}
