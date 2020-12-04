## Description de la compilation et l'execution de votre application
## Installation de l'application
> Pour effectuer la compilation, il suffit de se diriger dans le dossier **_src_** avec la commande **_cd /src_** puis de faire la commande **_make all_** avant d'exécuter les scripts **_serveur_** et **_client_**.

## Execution de l'application
#### Message
> type de message : message
message : hello world !
#### Nom
> type de message : nom
message : exemple
#### Calcul
> type de message : calcul
 - _minimum_ ou _maximum_
 > Pour le _minimum_ et le _maximum_ il vous suffit de saisir par exemple : "minimum",3,25,65,96,98,33
 Le premier nombre saisie signifie le nombre de valeur retournée. Ici _3_ est saisie cela signifie que l'on va retourner au client les _3_ plus petit nombre sur la suite saisie par le client. Ici on va donc retourner au client 25,33,65.
Pour le maximum, c'est exactement pareil que le minimum
 - _+_ , _-_ , _*_ 
> Pour ces fonctionnalités,  il vous suffit de saisir : "+",10,23. La saisie est limité à 2 nombres
- _moyenne_, _ecarttype_
> Pour ces 2 dernières fonctionnalités, vous pouvez saisir plus de nombre par exemple : "moyenne",10,25,25,65,98,78,45,25
Cela va nous retourner la moyenne de tous ces nombres saisis
#### Couleurs
> type de message : couleurs
message : 3,"#123456","#321654","#987654"
#### Balises
> type de message : balises
message : 3,"#123456","#321654","#987654"
#### Plot
>Pour cette fonctionnalité, il faut ajouter en argument le path de l'image
type de message : plot
nombre de couleurs : 1~30