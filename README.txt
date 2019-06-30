Dans ce dossier vous trouverez l’ensemble des fichiers correspondant au projet ISS du groupe composé de Elias Aoun Durand, Yvan Baki Bernard et Alexandre Chenu. 



À l’intérieur de ce dossier, vous trouverez :

- Plusieurs fichier .txt correspondant à des fichiers assembleurs : un exemple « ex_assembleur.txt » permettant de tester précisément certaines fonctionnalités de l’ISS ; un fichier « suite_syracuse.txt » permettant d’implémenter le comportement de la suite de Syracuse

- Une image .pdf correspondant au flowchart de l’implémentation de la suite de Syracuse en code assembleur.

- Un ficher main.c composé des fonctions et des structures nécessaires à l’initialisation des données, au traitement du fichier texte voulu et à l’affichage des résultats voulus (registres, adresse de mémoire…)

Les affichages sont situés à la fin du main.c et sont actuellement commentés. 
Vous êtes libre de les décommenter.

- Un fichier fonction_ISS.c et son fichier de headers contenant les fonctions nécessaire au traitement du fichier assembleur.

- Un fichier fonction_opération.c et son fichier de headers contenant les fonctions implémentant les opérations de notre ISA. 

- Un fichier Cache_memory.c et son fichier de headers contenant les fonctions et les structures nécessaires à la modélisation du fonctionnement de la mémoire Cache.




Le fonctionnement global de notre ISS est le suivant :

1. On ouvre le fichier assembleur et on effectue une première lecture afin d’identifier les labels (fonction detect_label). 
2. On procède à une lecture ligne par ligne du fichier texte afin d’effectuer les opérations souhaitée. 
Pour se faire, on effectue une analyse de l’opération lue et de ses arguments ( fonction analyse ). 
3. Les résultats de l’analyse sont alors renvoyés sous forme binaire : opération, numero de registre… (fonction identification). 
4. On affiche alors la trame binaire complète avec la fonction full_trame_bin.
5. On effectue les opérations souhaitée avec la fonction évaluation. 



Note : L’intégralité du code à été écrit en language C et peut être compilé sous GCC, language « légèrement » plus chronophage que Python!