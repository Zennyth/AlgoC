#### Objectifs :
> Notre objectif final pour ce projet est de créer une plate-forme multi-client. Jusqu'à maintenant, vous avez toujours un client et un serveur à la fois. Mais maintenant, nous voulons que plusieurs clients puissent communiquer avec votre serveur à la fois. Modifier votre code serveur, afin qu'il puisse accepter plusieurs requêtes client à la fois.
> De plus, nous devions écrire des tests unitaires
> La communication se fait encore avec des **_string_**, le JSON nous sert juste à intéragir.

#### Fichiers :
> Nous avons donc un dossier **src** dans lequel se trouve toutes les sources de la Tâche 3.
> Nous avons un autre dossier **images** dans lequel se trouve les _images_ pour la fonction _couleur_.
> Nous avons un autre fichier **json** dans lequel se trouve le code de la librairie Json.
> Pour savoir comment exécuter ce code, regardé le **_INSTALL_**.
> Nous avons un autre fichier **unitTesting** dans lequel se trouve l'intégralité de nos tests unitaire.

#### Dossier :
> Nous avons un dossier files qui stocke tous les fichiers textes (couleurs et balises).

#### Bibliothèques :
> Nous avons installé deux bibiliothèques : math.h pour le calcul de l'écart-type (racine carrée), pthread.h afin de tester si le multiclient est disponible sur le serveur et nous avons également gardé tous les imports qui était déjà présent dans la code (string.h, unistd.h, stdio.h, stdlib.h).

#### Références :
> Nous avons cherché sur internet lorsque nous avions des erreurs de syntax ou que nous comprenions pas une erreur (majoritairement Stack Overflow). 

#### Difficultés :
> Cette tâche était extremement compliqué puisque c'est la seule que nous avons pas réussi à terminer dans son entièreté à temps. Nous avons finis les tests fonctionnels sur la mutiplicité des clients mais nous ne sommes pas convaincu de notre solution. 

#### Commentaires :
> Anthony Chomienne nous a aidé à fixer les bugs sur le multi-client.
> Les tests unitaires se lancent en exécutant le ./unitTesting, généré automatiquement par le Makefile.
> Les tests unitaires sont regroupés dans le fichier UnitTesting qui teste la librairie Json en simmulant le côté client et le côté serveur.
> Les types de tests unitaires :
> * Librairie Json accepte tous les types d'opération
> * Librairie Json accepte et analyse les messages
> * Librairie Json valide les messages et respect le protocole de communication
> Les types de tests fonctionnels :
> * Multi-connexion des clients sur le serveur grâce à la mise en place du multi-thread.
> La fonction Log installée sur le serveur permet de stocker tous les messages valides envoyés par les clients.