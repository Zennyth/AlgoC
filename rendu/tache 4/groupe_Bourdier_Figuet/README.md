#### Objectifs :
> Notre objectif est d'utiliser le format d'image bmp et de communiquer entre le serveur et le client à l'aide du format de message JSON.
> La communication se fait encore avec des **_string_**, le JSON nous sert juste à intéragir.

#### Fichiers :
> Nous avons donc un dossier **src** dans lequel se trouve toutes les sources de la Tâche 3.
> Nous avons un autre dossier **images** dans lequel se trouve les _images_ pour la fonction _couleur_.
> Nous avons un autre fichier **json** dans lequel se trouve le code de la librairie Json.
> Pour savoir comment exécuter ce code, regardé le **_INSTALL_**.

#### Dossier :
> Nous avons un dossier files qui stocke tous les fichiers textes (couleurs et balises).

#### Bibliothèques :
> Nous n'avons pas touché aux bibliothèques, nous avons gardé tous les imports qui était déjà présent dans la code (string.h, unistd.h, stdio.h, stdlib.h).

#### Références :
> Nous avons cherché sur internet lorsque nous avions des erreurs de syntax ou que nous comprenions pas une erreur (majoritairement Stack Overflow).
> Nous avons également demandé de l'aide à un groupe (BOYER Charles et LAZARETH Baptiste) en cas de dernier recours.

#### Difficultés :
> Cette râche était définitivement plus dur que les précedentes puisque nous avons suivis une architecture de code précise.
> Ce n'était pas irréalisable mais la difficulté à augmenté.

#### Commentaires :
> Voici la description du fonctionnemnt de notre librairie Json qui pour l'instant est bien maigre comparé à l'originale.
> String -> Vérificator -> Parsor -> Json Object
> Concernant le parsing nous avons opté avec un découpage en index pour ainsi éviter au maximum les erreurs de saisie.
> Nous avons décidé de gérer les erreurs avec d'autres objets json qui ont comme code: "error", ils ont aussi une description de l'erreur en question dans la propriété valeurs, ils sont sont ensuite affichés si jamais il y a eu une erreur de parsing.
> Nous avons décidé de lever une exception si jamais l'utilisateur ne respectait pas le format suivant :
> Propriété : "code", "valeurs" -> Exception levé : "Vous n'avez pas défini la propiété code" ou "Vous n'avez pas défini la propiété valeurs"
> les valeurs des propriétés si dessus doivent respecté le format suivant :
> "" pour les string et pas de guillemet pour les nombres