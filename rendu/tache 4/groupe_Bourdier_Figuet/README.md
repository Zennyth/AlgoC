    
#### Objectifs :
> Notre objectif est d'implémenter les fonctionnalités suivantes sur le serveur : moyenne, le minimum, maximum, écart-type
> La communication se fait encore avec des **_string_**, le JSON nous sert juste à intéragir.

#### Fichiers :
> Nous avons donc un dossier **src** dans lequel se trouve toutes les sources de la Tâche 3.
> Nous avons un autre dossier **images** dans lequel se trouve les _images_ pour la fonction _couleur_.
> Nous avons un autre fichier **json** dans lequel se trouve le code de la librairie Json.
> Pour savoir comment exécuter ce code, regardé le **_INSTALL_**.

#### Dossier :
> Nous avons un dossier files qui stocke tous les fichiers textes (couleurs et balises).

#### Bibliothèques :
> Nous avons installé une bibiliothèques : math.h pour le calcul de l'écart-type (racine carrée) et nous avons également gardé tous les imports qui était déjà présent dans la code (string.h, unistd.h, stdio.h, stdlib.h).

#### Références :
> Nous avons cherché sur internet lorsque nous avions des erreurs de syntax ou que nous comprenions pas une erreur (majoritairement Stack Overflow).

#### Difficultés :
> Cette tâche n'était pas si dure que ça c'est pour cela que Monsieur John Samuel nous a donné un défi supplémentaire pour augmenter la difficulté de cette tâche.

#### Commentaires :
> Le défi de Monsieur John Samuel était de modifier la focntion minimum et maximum en utilisant la fonction _qsort_.
> En effet, nous avons donc fait une seule fonction pour le **minimum** et le **maximum** qui tri dans l'ordre croissant tous les nombres saisis par l'utilisateur. De plus, nous avons également rajouté une fonctionnalité : l'utilisateut saisi le nombre de chiffre qu'il veut que la fonction renvoie.
Exemple, l'utilisateur saisi cette commande : "minimum",**3**,23,56,89,78,54,451  --> le premier mot saisie dit si c'es le _minimum_ ou le _maximum_, ensuite le nombre en **gras** signifie que le tableau retournera **3** valeurs et enfin ce sont les valeurs à trier. Cette commaande retournerait donc **23,54,56**.
> L'utilisateur peut saisir au maximum 28 chiffres à trier.
> Ensuite, pour la moyenne et l'écart-type, l'utilsateur ne saisit pas le nombre de chiffre qu'il veut que la fonction renvoie puisque ces fonctions renvoient automatiquement un seul nombre. 
> Enfin, l'utilisateur peut saisir au maximum 29 chiffres pour ces deux fonctionnalités.
