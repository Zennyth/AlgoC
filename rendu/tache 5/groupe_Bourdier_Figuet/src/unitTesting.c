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

int NUMBER_OF_TEST = 0;
int NUMBER_OF_SUCESSFULL_TEST = 0;


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
    memset(result,0,sizeof(result));
    

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

void print_test(char * data, char * response, char * status, char * type) {
  printf("==========================================================================\n");
  printf("Start Test ! (%s)\n", type);
  printf("Sent data : %s\n", data);
  printf("Received data: %s\n", response);
  printf("Test Status : %s\n", status);
}

void test_validation(int socketfd) {
  char data[1024]="{\"id\":\"Zennyth\",\"code\":\"message\",\"valeurs\":[\"hello\"]}";
  char response[1024];
  char status[10];
  strcpy(response, sendMessage(socketfd, data));
  if(strcmp(data, response) == 0) {
    strcpy(status,"Success");
    NUMBER_OF_SUCESSFULL_TEST++;
  } else {
    strcpy(status,"Failed");
  }
  NUMBER_OF_TEST++;
  print_test(data, response, status, "validation JSON");
}

void test_code(char * code, bool expected) {
  char data[1024];
  bool res = false;
  char status[10];
  sprintf(data, "{\"id\":\"Zennyth\",\"code\":%s,\"valeurs\":[\"test\"]}", code);
  struct Json json = parse(strdup(data));
  if(strcmp(json.code, code) == 0) {
    res = true;
  }
  if(res == expected) {
    strcpy(status,"Success");
    NUMBER_OF_SUCESSFULL_TEST++;
  } else {
    strcpy(status,"Failed");
  }
  NUMBER_OF_TEST++;
  print_test(data, toString(json), status, "validation des différents codes");
}

void test_codes() {
  test_code("\"calcul\"", true);
  test_code("\"message\"", true);
  test_code("\"nom\"", true);
  test_code("\"plot\"", true);
  test_code("\"couleurs\"", true);
  test_code("\"balises\"", true);
  test_code("\"autre\"", false);
}

void test_validate(char * data, bool expected) {
  bool res = false;
  char status[10];
  struct Json json = parse(strdup(data));
  if(strcmp(toString(json), data) == 0) {
    res = true;
  }
  if(res == expected) {
    strcpy(status,"Success");
    NUMBER_OF_SUCESSFULL_TEST++;
  } else {
    strcpy(status,"Failed");
  }
  NUMBER_OF_TEST++;
  print_test(data, toString(json), status, "rawString => Parsing => toString validation");
}

void test_validates() {
  test_validate("{\"id\":\"Zennyth\",\"code\":\"message\",\"valeurs\":[\"test\"]}", true);
  test_validate("{\"id\":\"Zennyth\",\"code\":\"message\",\"valeurs\":[1,2,3]}", true);
}

void test_value(char * data, char * result, bool expected, int socketfd) {
  bool res = false;
  char status[10];
  char response[1024] = "";

  //struct Json json = parse(strdup(data));
  strcpy(response, strdup(sendMessage(socketfd, data)));
  
  if(strcmp(response, result) == 0) {
    res = true;
  }
  if(res == expected) {
    strcpy(status,"Success");
    NUMBER_OF_SUCESSFULL_TEST++;
  } else {
    strcpy(status,"Failed");
  }
  NUMBER_OF_TEST++;
  print_test(data, response, status, "rawString => Parsing => toString validation");
}

void test_values(int socketfd) {
  test_value("{\"id\":\"Bourdier\",\"code\":\"calcul\",\"valeurs\":[\"minimum\",2,89,23,56]}","{\"id\":\"Bourdier\",\"code\":\"calcul\",\"valeurs\":[23,56]}",true,socketfd);
  test_value("{\"id\":\"Bourdier\",\"code\":\"calcul\",\"valeurs\":[\"maximum\",2,2398,560,8999,234]}","{\"id\":\"Bourdier\",\"code\":\"calcul\",\"valeurs\":[2398,8999]}",true,socketfd);
  test_value("{\"id\":\"Bourdier\",\"code\":\"calcul\",\"valeurs\":[\"moyenne\",0,5,10]}","{\"id\":\"Bourdier\",\"code\":\"calcul\",\"valeurs\":[5.00]}",true,socketfd);
  test_value("{\"id\":\"Bourdier\",\"code\":\"calcul\",\"valeurs\":[\"ecarttype\",0,5,10]}","{\"id\":\"Bourdier\",\"code\":\"calcul\",\"valeurs\":[4.08]}",true,socketfd);
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

    test_validation(socketfd);
    test_codes();
    test_validates();
    test_values(socketfd);
    char ratio[10];
    sprintf(ratio, "%i/%i", NUMBER_OF_SUCESSFULL_TEST, NUMBER_OF_TEST++);
    printf("==========================================================================\n");
    printf("Resume : \n");
    printf("Ration of successful tests : %s\n", ratio);
    printf("==========================================================================\n");
    
    close(socketfd);
}