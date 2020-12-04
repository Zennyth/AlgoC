#define _GNU_SOURCE //to avoid c99 related warnings
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "client.h"
#include "bmp.h"
#include "json.h"


bool unit_testing_connection() {
  return true;
}

bool unit_testing_validate() {
  return true;
}

bool unit_testing_analyse() {
  return true;
}

bool unit_testing_code() {
  return true;
}

bool unit_testing() {
  bool res = true;
  if(unit_testing_connection() != true) {
    printf("Problème concernant la connexion.");
    res = false;
  }
  if(unit_testing_validate() != true) {
    printf("Problème concernant la validation des messages Json.");
    res = false;
  }
  if(unit_testing_analyse() != true) {
    printf("Problème concernant l'analyse des messages Json.");
    res = false;
  }
  if(unit_testing_code() != true) {
    printf("Problème concernant la propriété code.");
    res = false;
  }
  return res;
}

char * sendMessage(int socketfd, char * data) {
    static char result[1024] = "";
    printf("print : %s\n", data);

    int write_status = write(socketfd, data, strlen(data));
    if ( write_status < 0 ) {
      perror("erreur ecriture");
      exit(EXIT_FAILURE);
    }

    char result1[1024];
    // la réinitialisation de l'ensemble des données
    memset(result1, 0, sizeof(result1));

    // lire les données de la socket
    int read_status = read(socketfd, result1, sizeof(result1));
    if ( read_status < 0 ) {
      perror("erreur lecture ");
    }
    strcat(result, result1);
    return result;
}

void main() {
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

    char data[1024]="{\"id\":\"Zennyth\",\"code\":\"message\",\"valeurs\":[\"hello\"]}";
    char response[1024];
    printf("%s\n", response);
    strcpy(response, sendMessage(socketfd, data));
    printf("%s\n", response);
    unit_testing();
    printf("bonjour unit Testing");
    close(socketfd);
}