# Projet d'un week-end de course de Formule 1 en C :
Le but du projet est de gérer un week-end complet d’un grand prix de Formule 1, depuis les séances d’essais du vendredi jusqu’à la course du dimanche, en passant par les essais du samedi et la séance de qualifications. 
Il y a 22 voitures engagées dans un grand prix. 
Leurs numéros sont : 44, 6, 5, 7, 3, 33, 19, 77, 11, 27, 26, 55, 14, 22, 9, 12, 20, 30, 8, 21, 31, 94. 
Un circuit de F1 est divisé en 3 secteurs (S1, S2, S3). 
Le calendrier d’un week-end de F1 est établi comme suit : 
* Vendredi après-midi, une séance d’essais libres d’1h30 (P2) 
* Samedi matin, une séance d’essais libres d’1h (P3) 
* Samedi après-midi, la séance de qualifications, divisée en 3 parties : 
o Q1, durée 18 minutes, qui élimine les 6 dernières voitures (qui occuperont les places 17 à 22 sur la grille de départ de la course) 
o Q2, durée 15 minutes, qui élimine les 6 voitures suivantes (qui occuperont les places 11 à 16 sur la grille de départ de la course) 
o Q3, durée 12 minutes, qui permet de classer les 10 voitures restantes pour établir les 10 premières places sur la grille de départ de la course 
* Dimanche après-midi, la course en elle-même. 

##Première partie : gestion des séances d’essai, des qualifications et de la course 
###Lors des séances d’essais (P1, P2, P3) : 
* Relever les temps dans les 3 secteurs à chaque passage pour chaque voiture 
* Toujours savoir qui a le meilleur temps dans chacun des secteurs 
* Classer les voitures en fonction de leur tour complet le plus rapide 
* Savoir si une voiture est aux stands (P) 
* Savoir si une voiture est out (abandon de la séance) 
* Dans ces 2 derniers cas, on conserve toujours le meilleur temps de la voiture et celle-ci reste dans le classement 
* Conserver le classement final à la fin de la séance 
Lors des qualifications (Q1, Q2, Q3) : 
* Relever les temps dans les 3 secteurs à chaque passage pour chaque voiture 
* Toujours savoir qui a le meilleur temps dans chacun des secteurs 
* Classer les voitures en fonction de leur tour complet le plus rapide 
* Savoir si une voiture est aux stands (P) 
* Savoir si une voitures est out (abandon de la séance) 
* Dans ces 2 derniers cas, on conserve toujours le meilleur temps de la voiture et celle-ci reste dans le classement 
* A la fin de Q1, il reste 16 voitures qualifiées pour Q2 et les 6 dernières sont placées à la fin de la grille de départ (places 17 à 22) 
* A la fin de Q2, il reste 10 voitures qualifiées pour Q3 et les 6 dernières sont placées dans les places 11 à 16 de la grille de départ 
* Le classement de Q3 attribue les places 1 à 10 de la grille de départ 
* Conserver le classement final à la fin des 3 séances (ce sera l’ordre de départ pour la course) 
Lors de la course : 
* Le premier classement est l’ordre sur la grille de départ 
* Le classement doit toujours être maintenu tout au long de la course (gérer les dépassements) 
* Relever les temps dans les 3 secteurs à chaque passage pour chaque voiture 
* Toujours savoir qui a le meilleur temps dans chacun des secteurs 
* Toujours savoir qui a le tour le plus rapide 
* Savoir si la voiture est out (abandon) ; dans ce cas, elle sera classée en fin de classement 
* Savoir si la voiture est aux stands (PIT), gérer le temps aux stands et faire ressortir la voiture à sa place dans la course (généralement 2 ou 3 PIT par voitures) 
* Conserver le classement final et le tour le plus rapide 
Remarque : les stands se trouvent toujours dans le secteur 3. 
 
  
##Seconde partie : gestion des drapeaux de course et de la voiture de sécurité 
###Durant la course, différents drapeaux peuvent être présentés aux pilotes : 
* Drapeau bleu : destiné aux pilotes doublés. Un pilote qui a un tour de retard est obligé de laisser passer un pilote qui va plus vite que lui (qui le double). 
 
* Drapeau jaune : concerne un secteur. Lorsqu’il est levé, interdiction pour tout le monde de dépasser dans ce secteur. 
 
 
* Drapeau rouge : arrêt de la course et re-départ depuis la voie des stands, dans l’ordre du classement actuel. 
 
* Voiture de sécurité : tout le monde suit. Attention : le nombre de tours à faire lors de la course continue à diminuer ! 
 
Lorsque la voiture de sécurité va rentrer, tous les pilotes « dépassés » doivent reprendre leur place dans l’ordre du classement actuel. Ils ont 2 tours pour se remettre à leur place en dépassant. 
Lorsque cela est fait, la voiture de sécurité rentre et la course reprend. 

@gregory
