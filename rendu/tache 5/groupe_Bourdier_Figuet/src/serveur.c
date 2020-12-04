/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serveur.h"
#include "json.h"
#include "json.c"
#include "bmp.h"
#include <errno.h>
#define SOCKET_ERROR -1

// Import que l'on a fait 
#include <math.h>

int intComparator ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}
/*
// Fonction de tri du tableau 
int * sort(const char res[30][100]){
  int i = 2;
  int min = atoi(res[i]);
  int tab[NUMBER_OF_STRING];
  
  for (i ; i < NUMBER_OF_STRING; i++)
	{
    if(res[i][0] != '\0') {
      int nb = atoi(res[i]);
      tab[i-2] = nb;
    } 
	}
  
  qsort(tab,sizeof tab / sizeof tab[0] - 4,sizeof tab[0], intComparator);
  for (int j = 0 ; j < sizeof tab / sizeof tab[0] ; j++)
  {
    int nb2 = tab[j];
    if (nb2 != 0)
    {
      if(tab[j] != '\0') {
        printf("%d\n", tab[j]); 
      }
    }  
  }
  return tab;
}*/

// Fonction qui retourne le minimumtabtab
struct Json minimum(const char res[30][100]){
  //int tab[NUMBER_OF_STRING] = sort(res);
  char tabtab[NUMBER_OF_STRING];
  struct Json tabreturn = {"calcul",{""}};
  int nbval = atoi(res[2]);
  /*
  for (int i = 0; i < nbval; i++)
  {
    strcpy(tabreturn.valeurs[i],itoa(tab[i],tabtab,10));
  }*/
  return tabreturn;

  /*int i = 1;
  int min = atoi(res[i]);
  for (i ; i < NUMBER_OF_STRING; i++)
	{
    if(res[i][0] != '\0') {
      int nb = atoi(res[i]);
      if ( min < nb )
        min = min;
      else
        min = nb;
    }
	}
  return min;*/
}

// Fonction qui retourne le maximum
int maximum(const char res[30][100]){
  int i = 1;
  int max = atoi(res[i]);
  for (i ; i < NUMBER_OF_STRING; i++)
	{
    if(res[i][0] != '\0') {
      int nb = atoi(res[i]);
      if ( max > nb )
        max = max;
      else
        max = nb;
    }
	}
  return max;
}

// Fonction qui retourne la moyenne
float moyenne(const char res[30][100]){
  int i = 1;
  float moy;
  float somme = 0;
  for (i ; i < NUMBER_OF_STRING; i++)
	{
    if(res[i][0] != '\0') {
      int nb = atoi(res[i]);
      somme = somme + nb;
      moy = somme / i;
    }
	}
  return moy;
}

// Fonction qui retourne l'ecarttype
float ecarttype(const char res[30][100]){
  int i = 1;
  float moy = moyenne(res);
  float somme = 0;
  float ecarttype;
  for (i ; i < NUMBER_OF_STRING; i++)
	{
    if(res[i][0] != '\0') {
      int nb = atoi(res[i]);
      somme = somme + pow(nb - moy,2);
      ecarttype = sqrt(somme/i);
    }
	}
  return ecarttype;
}


void plot(struct Json data) {
  
  //Extraire le compteur et les couleurs RGB 
  FILE *p = popen("gnuplot -persist", "w");
  printf("Plot");
  int count = 1;
  int n;
  char *saveptr = NULL;
  int nb = atoi(data.valeurs[0]);
  fprintf(p, "set xrange [-15:15]\n");
  fprintf(p, "set yrange [-15:15]\n");
  fprintf(p, "set style fill transparent solid 0.9 noborder\n");
  fprintf(p, "set title 'Top %i colors'\n", nb);
  fprintf(p, "plot '-' with circles lc rgbcolor variable\n");
  for(count = 1; count < sizeof data.valeurs / sizeof data.valeurs[0]; count++) {
    if(data.valeurs[count][0] != '\0') {
      printf("%s\n", data.valeurs[count]);
      fprintf(p, "0 0 10 %i %i 0x%s\n", (int) (count-1)*360/nb, (int) count*360/nb, data.valeurs[count]);
    }
  }
  fprintf(p, "e\n");
  printf("Plot: FIN\n");
  pclose(p);
}

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data) {
  int data_size = write (client_socket_fd, (void *) data, strlen(data));
      
  if (data_size < 0) {
    perror("erreur ecriture");
    return(EXIT_FAILURE);
  }
}

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int client_socket_fd) {
  struct sockaddr_in client_addr;
  char data[1024];

  int client_addr_len = sizeof(client_addr);

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  //lecture de données envoyées par un client
  int data_size = read (client_socket_fd, (void *)data, sizeof(data));
      
  if (data_size < 0) {
    perror("erreur lecture");
    return(EXIT_FAILURE);
  } else if (data_size == 0) {
    return 2;
  }
  struct Json res = parse(strdup(data));
  if (strcmp(res.code, "\"error\"") == 0) {
    perror("erreur convertion json");
    return(EXIT_FAILURE);
  }

  /*
   * extraire le code des données envoyées par le client. 
   * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
   */
  
  struct Json response = {"", "", {""}};
  strcpy(response.id, res.id);
  strcpy(response.code, res.code);
  
  if(strcmp(res.code, "\"nom\"") == 0 || strcmp(response.code, "\"message\"") == 0) {
    // Partie de nom et message
    strcpy(response.valeurs[0], res.valeurs[0]);
  } else if(strcmp(res.code, "\"couleurs\"") == 0 || strcmp(res.code, "\"balises\"") == 0) {
    // Partie de balises et couleurs
    char file[30] = "./files/";
    strcat(file, res.code);
    strcat(file, ".txt");
    // Ouvrir un fichier (couleurs.txt ou balises)
    FILE *fp;
    fp = fopen(file, "a");
    int i;
    for ( i = 0; i < sizeof res.valeurs / sizeof res.valeurs[0]; i++ ) {
      if(res.valeurs[i][0] != '\0') {
        // Pour chaque valeur non vide
        char line[30] = "";
        strcpy(line, res.valeurs[i]);
        strcat(line, "\n");
        // On écrit dans le fichier
        fputs(line, fp);
      }
    }
    fclose(fp);
    strcpy(response.valeurs[0], "\"enregistré\"");
  } else if(strcmp(res.code, "\"calcul\"") == 0) {
    // Partie de calcul
    char str[100];
    int i1 = atoi(res.valeurs[1]);
    int i2 = atoi(res.valeurs[2]);
    if (strchr(res.valeurs[0], '+') != NULL)
        sprintf(str, "%i", (i1 + i2));
    else if (strchr(res.valeurs[0], '-') != NULL)
        sprintf(str, "%i", (i1 - i2));
    else if (strcmp(res.valeurs[0], "\"minimum\"") == 0)
      {
      //sprintf(str, "%i", minimum(res.valeurs));
      printf("%s",toString(minimum(res.valeurs)));
      }
    else if (strcmp(res.valeurs[0], "\"maximum\"") == 0)
        sprintf(str, "%i", maximum(res.valeurs));
    else if (strcmp(res.valeurs[0], "\"moyenne\"") == 0)
        sprintf(str, "%.2f", moyenne(res.valeurs));
    else if (strcmp(res.valeurs[0], "\"ecarttype\"") == 0)
        sprintf(str, "%.2f", ecarttype(res.valeurs)); 
    else
        sprintf(str, "%i", (i1 * i2));
    strcpy(response.valeurs[0], str);
  } else if(strcmp(res.code, "\"plot\"") == 0) {
    // Partie de plot 
    plot(res);
    strcpy(response.valeurs[0], "\"plot\"");
  } else {
    // Partie erreur
    printf("Error : Pas de code valide !\n");
    strcpy(response.valeurs[0], "\"Pas de code valide !\"");
  }
  
  char file[30] = "./files/log.txt";
  // Ouvrir le fichier log.txt
  FILE *fp;
  fp = fopen(file, "a");
  int i;
  char line[150] = "";
  strcat(line, toString(res));
  strcat(line, "\n");
  fputs(line, fp);
  fclose(fp);
  renvoie_message(client_socket_fd, toString(response));
  //fermer le socket  
  //close(socketfd); 
}

int main() {
  int socketfd;
  int bind_status;
  int client_addr_len;

  struct sockaddr_in server_addr, client_addr;

  int socket_tab[15];
  for (int j = 0; j < 15; j++)
  {
    socket_tab[j] = 0;
  }
  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if ( socketfd < 0 ) {
    perror("Unable to open a socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  //détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Relier l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (bind_status < 0 ) {
    perror("bind");
    return(EXIT_FAILURE);
  }
 
  // Écouter les messages envoyés par le client
  int sock_err = listen(socketfd, 10);

  if(sock_err != SOCKET_ERROR){
    /* Création de l'ensemble de lecture */
    fd_set readfs;

    while(1)
    {
      /* On vide l'ensemble de lecture et on lui ajoute 
      la socket serveur */
      FD_ZERO(&readfs);
      FD_SET(socketfd, &readfs);
      int max_socket = socketfd;
      for (int j = 0; j < 15; j++)
      {
        if( socket_tab[j] > 0) {
          FD_SET(socket_tab[j], &readfs);
          if(socket_tab[j] > max_socket){
            max_socket = socket_tab[j];
          }
        }
      }

      /* Si une erreur est survenue au niveau du select */
      // 
      int select_socket = select(max_socket + 1, &readfs, NULL, NULL, NULL);
      if(select_socket < 0)
      {
        perror("select()");
        exit(errno);
      } else {
        int i = 0;
        while(select_socket > 0) {
          if(FD_ISSET(socketfd, &readfs)) {
            // nouvelle connection de client
            int client_socket_fd = accept(socketfd, (struct sockaddr *) &client_addr, &client_addr_len);
            if (client_socket_fd < 0 ) {
              perror("accept");
              return(EXIT_FAILURE);
            }
            for (int j = 0; j < 15; j++)
            {
              if( socket_tab[j] == 0 ) {
                socket_tab[j] = client_socket_fd;
                break;
              }
            }
            if(recois_envoie_message(client_socket_fd) == 2){
              for (int j = 0; j < 15; j++)
              {
                if( socket_tab[j] == client_socket_fd) {
                  socket_tab[j] = 0;
                }
              }
            }
            select_socket--;
          }
          if(FD_ISSET(socket_tab[i], &readfs)) {
            if(recois_envoie_message(socket_tab[i]) == 2){
              socket_tab[i] = 0;
            }
            select_socket--;
          }
          i++;
        }
      }
    }
  }
  
  return 0;
}
