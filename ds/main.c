
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-E = Appelle le préprocesseur. N'effectue pas la compilation. (Pré traitement) -> gcc -E test.c
-o = Fixe le nom du fichier objet généré lors de la compilation d'un fichier source et place la
sortie dans ce fichier. (pour faire un .exe) (édition de lien) -> gcc -o test.exe test.c
-c = Appelle le préprocesseur, effectue la compilation et l'assemblage, 
mais ne fait pas l'édition de lien. Seuls les fichiers objet (« .o ») sont générés. -> gcc -c test.c
-Wall affiche toutes les erreurs*/

/*int a = 10;
int * pa = &a; // pour définir un pointeur qui pointe l'adresse de a

// &a = son adresse
// *a = sa valeur

// %p pour afficher un pointeur
// *pa pour afficher la valeur que pointeur */

/*
Quel code est implémenté dans le fichier .h ? **Implémente les signatures de fonctions**

Quel code est implémenté dans le fichier .c ? **Implémente le code des signatures des fonctions qui sont dans .h**
*/

/*MAKEFILE
CC ?= gcc

CFLAGS=-Wall -Wextra -g

COBJS ?= client.o couleur.o
SOBJS ?= serveur.o 

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	$(CC) -o $(SERVER) $(SOBJS)

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS)

.c.o: 
	$(CC) -c $*.c
*/

/*int objectifCode(){
     Ce programme demandera à l'utilisateur de saisir deux nombres dans une ligne. Si l'utilisateur entre 'END', le programme se terminera, 
    sinon il affichera la valeur de l'opération bit à bit '&' sur les deux nombres. 
    char phrase[100];
    while(1) {
        printf("Entrez une phrase: ");
        fgets(phrase, 100, stdin) ;
        phrase[strnlen(phrase, 100)-1] = '\0' ;
        if (strncmp(phrase, "FIN", 100) == 0) {
            break ; 
        }
        int num[2];
        sscanf(phrase, "%d %d", &num[0], &num[1]);
        printf("%d\n", num[0] & num[1]); 
    }
    return(0);
}*/

float conversion (char * str){
	return atof(str); //atoi pour un int
}

//4eme et 20eme bit à 1
int bits(int number){
    int result=number&524296;
    if(result==524296)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void my_strcpy(char *chaine_a_copier, char *chaine_de_destination) // ici on prend en paramètre les pointeurs qui pointe sur les chaines de caracteres
{
    int i = 0;
    while (chaine_a_copier[i] != '\0'){ // Parcourir la chaine jusqu'a \0
        chaine_de_destination[i] = chaine_a_copier[i]; // copier la chaine
        i++;
    } 

}
//strcopy avec pointeur
/*while(*chaineACopier!='\0')
    {
        chaineDest=chaineACopier;
        chaineDest++;
        chaineACopier++;
}*/

void my_strconcat(char *chaine_a_concatener, char *chaine) 
{
    int i, j;
    i = 0;
    j = 0;

    while (chaine_a_concatener[i] != '\0'){ // compte le nombre de carcatères
        i++;
    }

    while (chaine[j] != '\0'){
        chaine_a_concatener[i+j] = chaine[j]; // Permet j'ajouter à la fin de la chaine la chaine voulu
        j++;
    }
}


int my_strlen(char *chaine) 
{
    int i = 0;
    while (chaine[i] != '\0'){ // permet de compter les carcateres
        i++;
    }
    return i;
}
//Concat avec des pointeurs
/*void strConcat(char *chaine_a_concatener, char *chaine) 
{
    int i, j;
    i = 0;
    j = 0;

    while ( *(chaine_a_concatener + i) != '\0'){ // compte le nombre de carcatères
        i++;
    }

    while ( *(chaine + j) != '\0'){
        int test = 0 ;
        test = i+j;
        *(chaine_a_concatener +(i+j)) = *(chaine + j); // Permet j'ajouter à la fin de la chaine la chaine voulu
        j++;
    }
}
*/


int plusGrand(char ** tab, int taille){
    int plusGrand = atoi(tab[1]);
    
    for(int i = 1; i < taille; i++){ 
        if(plusGrand < atoi(tab[i])){
            plusGrand = atoi(tab[i]);
        }
    }

    return plusGrand;
    
}

int plusPetit(char ** tab, int taille){
    int plusPetit = atoi(tab[1]);
    for(int i = 1; i < taille; i++){
        if(plusPetit > atoi(tab[i])){
            plusPetit = atoi(tab[i]);
        }
    }
    return plusPetit;
}

float moyenne(char ** tab, int taille){
    float moyenne = 0;
    float somme = 0;
    for(int i = 1; i < taille; i++){
        somme += atoi(tab[i]);
    }
    moyenne = somme/(taille-1);
    return moyenne;
}


void puisance(int a, int b){
    int result = 1;
    for (int i = 0; i < b; i++){
        result = result * a;
    }

    printf("Le nombre %d à la puissance %d est : %d\n\n", a, b, result);
}

/* phrase a trouver fichier
void trouve_phrase(char *phrase_a_chercher, char *nom_fichier){
	// Variables compteur
    int nombreDeLigne = 0;

    // Variables fichier
    FILE* fichier = NULL;
    char chaine[1000];
    
    // Ouverture fichier
    fichier = fopen(nom_fichier, "r+");
    
    // Parcour pour trouver les correspondances
    while (fgets(chaine, 1000, fichier) != NULL){
    	nombreDeLigne++;
    	if(strstr(chaine, phrase_a_chercher) != NULL){
    		printf("Ligne : %d\n", nombreDeLigne);
    	}
    }

    // Fermeture fichier
    fclose(fichier);
}
*/


void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

int fibonacci(int n){
    if (n < 2)
    {
        return n;
    }
    else
    {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}


int fibonacciItt(int n) {
  int u = 0;
  int v = 1;
  int i, t;

  for(i = 2; i <= n; i++) {
    t = u + v;
    u = v;
    v = t;
  }
  return v;
}


int cal(char * source)
{
  int cpt=0;
  while (*source != '\0')
  {
    cpt++;
    source++;
  }
  return (cpt);
}

void echange(int * a, int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

typedef struct Batiment{
    char nom[255];
    char adresse[255];
}Batiment;

typedef struct Capteur{
    int identifiant;
    char temps[255];
    float luminosite;
    float pression;
    float temperature;
    Batiment batiment;
}Capteur;

typedef struct Couleur{
    short rouge;
    short vert;
    short bleu;
    short alpha;
    struct Couleur * suivant;
}Couleur;

typedef struct liste_couleurs{
    struct Couleur premier;
;
}liste_couleurs;

void parcours (struct liste_couleurs *listeCouleurs){

	// Affichage de la premiere couleur
	printf("{r = %hd, g = %hd, b= %hd, a = %hd}\n",listeCouleurs->premier.rouge, listeCouleurs->premier.vert, listeCouleurs->premier.bleu, listeCouleurs->premier.alpha);
	struct Couleur *couleur = listeCouleurs->premier.suivant;

	// Tant que c'est pas la derniere couleur, on affiche la couleur suivante.
	while(couleur != NULL) {
		printf("{r = %hd, g = %hd, b= %hd, a = %hd}\n", couleur->rouge, couleur->vert, couleur->bleu, couleur->alpha);
		couleur = couleur->suivant;  
	}
}

void insertion (struct Couleur *couleurAInserer, struct liste_couleurs *listeCouleurs){

	// On met la deuxieme couleur comme couleur suivante à la couleur à insérer
	couleurAInserer->suivant = listeCouleurs->premier.suivant;

	// On met la couleur à insérer à la deuxieme place de la liste.
	listeCouleurs->premier.suivant = couleurAInserer;

}

int main(int argc, char *argv[])
{   
    
    int nbr[argc-1];
    for (int i = 1; i < argc; i++)
    {
        nbr[i-1] = atoi(argv[i]);
    }

    for (int i = 0; i < sizeof(nbr) / sizeof(int); i++)
    {
        printf("%i\n", nbr[i]);
    }
    bubbleSort(nbr,argc-1);
    printf("=================================\n");
    for (int i = 0; i < sizeof(nbr) / sizeof(int); i++)
    {
        printf("%i\n", nbr[i]);
    }

    char command[50];
    sprintf(command, "head -n %s test.txt", argv[1]);
    system(command);

    /* 0 // car 2=0010 & 4=0100 => 0010=2 */
    printf("2 & 4 : %i \n", 2 & 4);
    /* 1 // aucune valeur non nulle */
    printf("2 && 4 : %i \n", 2 && 4);
    /* 6 // car 2=0010 & 4=0100 => 0010=2  */
    printf("2 | 4 : %i \n", 2 | 4);
    /* 1 */
    printf("2 || 4 : %i \n", 2 || 4);
    printf("%i\n",fibonacci(11));
    printf("%i\n",fibonacciItt(11));

    char tab[]="Bonjour, clement";
    int nbChar=cal(tab);
    printf("%s", tab);
    printf("comtient: %d caractere\n", nbChar);

    char message1[10] = "Bonjour" ;
    char *message2 = "Bonjour" ;    

    printf("%lu\n", sizeof (char));
    printf("%lu\n", sizeof (char *));
    printf("%lu\n", sizeof (char **));
    printf("%lu\n", sizeof (int **));
    printf("%lu\n", sizeof (message1));
    printf("%lu\n", strlen (message1));
    printf("%lu\n", sizeof (message2));
    printf("%lu\n", strlen (message2));
    
    #ifndef __OPERATEURS_H__
    #define __OPERATEURS_H__
    int num = 20;
    printf("%i\n",num);
    #define PI 3.141592653589
    #define multiplication(a,b) a * b
    #endif //__OPERATEURS_H__ 

    int a = 1;
    int b = 2;
    printf("A = %i\n", a);
    printf("B = %i\n", b);
    echange(&a,&b);
    printf("A = %i\n", a);
    printf("B = %i\n", b);
    Batiment b1 = {"nom","adresse"};
    Capteur capteur1 = {1,"20:23",23.2,56.2,89.5,b1};
    printf("%s\n",capteur1.batiment.nom);

    printf("10 modulo 3 = %i\n", 10 % 3);
    printf("10 & 3 = %i\n", 10 & 3);
    printf("10 | 3 = %i\n", 10 | 3);
    printf("10 && 3 = %i\n", 10 && 3);
    printf("10 || 3 = %i\n", 10 || 3);
    printf("10 << 3 = %i\n", 10 << 3);
    printf("10 / 3 = %i\n", 10 / 3);
    //printf("10 ** 3  = %i\n", 10 ** 3 ); marche pas
    
    puisance(2,3);
    
    //printf("%i", d(1048575));

    char chaine_de_destination[255];
    char chaine_a_copier[255] = "Chaine que l'on doit copier dans la destination";
    my_strcpy(chaine_a_copier, chaine_de_destination);
    printf("Chaine de destination : %s\n", chaine_de_destination);

    // Concaténer une chaine //
    char chaine_a_concatener[255] = "Chaine de base";
    char chaine[255] = " Chaine à ajouter";
    my_strconcat(chaine_a_concatener, chaine);
    printf("La chaine concatenée : %s\n", chaine_a_concatener);

    // Taille d'une chaine de caractère //
    char chaineLen[10] = "test";
    printf("Taille de la chaine : %d\n", my_strlen(chaineLen));

    printf("%i\n",plusPetit(argv,argc));
    printf("%i\n",plusGrand(argv,argc));
    printf("%f\n",moyenne(argv,argc));

    // Initialisation des couleurs chainées
	struct Couleur c10={0x00, 0xa5, 0x1d, 0x9a, NULL};
	struct Couleur c3={0x01, 0xcc, 0xff, 0xff, &c10};
	struct Couleur c2={0xe4, 0x95, 0x1c, 0x8a, &c3};
	struct Couleur c1={0x00, 0xa5, 0x1d, 0x9a, &c2};

	// Initialisation liste de couleurs chainées
	struct liste_couleurs liste={c1};

	// Affichage de la liste
	printf("Premier parcours : \n");
	parcours(&liste);

	// Insert de 10 nouvelles couleurs
	struct Couleur c1ajout={0x01, 0x01, 0x01, 0x01, NULL};
	struct Couleur c2ajout={0x20, 0x20, 0x20, 0x20, NULL};
	struct Couleur c3ajout={0x30, 0x30, 0x30, 0x30, NULL};
	struct Couleur c10ajout={0x10, 0x10, 0x10, 0x10, NULL};
	insertion(&c1ajout, &liste);
	insertion(&c2ajout, &liste);
	insertion(&c3ajout, &liste);
	insertion(&c10ajout, &liste);
	
	// Affichage de la liste après les ajouts des 10 couleurs
	printf("\nDeuxieme parcours : \n");
	parcours(&liste);

    return 0;
}

/* Trouver une phrase dans un tableau de caractere
int count(char *chaine_a_tester){
    int i = 0;
    while (chaine_a_tester[i] != '\0'){ // Parcourir la chaine jusqu'a \0
        i++;
    }
    return i;
}

int main(int argc, char ** argv) {

    // Variables
    int i = 0;
    int z, u, h, j, mauvais;  
    u = 0;
    h = 1;
    j = 0;
    mauvais = 0;
    char phrases[10][100] = {"une phrase", "rtg phrase", "trois phrase", "quatre phrase", "cinq phrase", "six phrase test", "sept phrase", "huit phrase", "neuf phrase", "dix phrase"};

    int nombre_de_mots = argc;
    int nombre_lettre_phrase_param = nombre_de_mots - 2; // par défaut je prend le nb de param et j'enlève 2, un pour le nom du fichier et le deuxième qui permet de compter les espaces dans une phrase

    // boucle pour parcourir la phrase en paramètre
    for(int k = 1; k < nombre_de_mots; k++){
        nombre_lettre_phrase_param += count(argv[k]);
    }
    char bonne[100];
    char *pBonne = bonne;

    while(j <= 10 || pBonne[u] != '\0'){
        if(count(phrases[j]) == nombre_lettre_phrase_param){
        
            pBonne = phrases[j];
            if(pBonne[u] == ' '){
                h++;
                i = 0;
                u++;
            }

            if(pBonne[u] == argv[h][i]){
                printf("%c, %c \n", pBonne[u], argv[h][i]);
                u++;
                i++;
                mauvais = 0;
            } else {
                j++;
            }
        } else {
            j++;
            mauvais++;
        }
    }

    if(mauvais != 0){
        printf("Phrase pas présente");
    } else {
        printf("Phrase présente");
    }
}*/