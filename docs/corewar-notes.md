# CoreWar Notes

## 1. C'est quoi CoreWar ?

CoreWar est un jeu de programmation dans lequel plusieurs champions se battent dans une arène mémoire commune.

Chaque champion est un petit programme. La machine virtuelle les exécute cycle après cycle. Le but d'un champion est de survivre plus longtemps que les autres.

Le dernier champion encore considéré comme vivant remporte la partie.

## 2. C'est quoi un champion ?

Un champion est un programme écrit dans un langage assembleur spécifique à CoreWar.

Au départ, il est écrit dans un fichier `.s`, lisible par un humain. Ensuite, il est compilé par l'assembleur `asm` en fichier `.cor`, lisible par la machine virtuelle.

Pendant le combat, le champion est placé dans l'arène et exécuté par un ou plusieurs processus.

## 3. C'est quoi l'assembleur `asm` ?

L'assembleur `asm` est le programme qui transforme un champion écrit en assembleur CoreWar (`.s`) en champion binaire (`.cor`).

Il doit notamment :

- lire le fichier `.s` ;
- comprendre les directives comme `.name` et `.comment` ;
- parser les instructions ;
- résoudre les labels ;
- encoder les instructions en octets ;
- écrire le fichier final `.cor`.

## 4. C'est quoi la VM `corewar` ?

La VM, ou machine virtuelle, est le programme qui exécute les champions compilés.

Elle doit :

- charger les fichiers `.cor` ;
- placer les champions dans l'arène ;
- créer les processus de départ ;
- exécuter les instructions cycle par cycle ;
- gérer les règles de vie et de mort ;
- déterminer le gagnant à la fin du combat.

## 5. C'est quoi l'arène ?

L'arène est la mémoire commune dans laquelle les champions se battent.

Dans le CoreWar Epitech classique, elle contient généralement `4096` cases mémoire.

Chaque case représente un octet. Les champions sont chargés à différents endroits dans cette mémoire, puis leurs processus lisent et écrivent dans l'arène.

L'arène est circulaire : si une adresse dépasse la fin de la mémoire, elle revient au début.

Exemple :

```text
adresse 4096 => adresse 0
adresse 4097 => adresse 1
adresse -1   => adresse 4095
```

## 6. C'est quoi un process ?

Un process représente une exécution active d'un champion.

Un champion peut avoir un ou plusieurs process. Au début, chaque champion commence généralement avec un process. Certaines instructions comme `fork` peuvent créer de nouveaux process.

Un process contient notamment :

- un `pc`, qui indique sa position actuelle dans l'arène ;
- des registres ;
- un `carry` ;
- un état de vie ;
- des cycles d'attente avant d'exécuter une instruction.

## 7. C'est quoi le PC ?

Le PC signifie `program counter`.

C'est la position actuelle d'un process dans l'arène. La VM lit l'instruction à l'adresse indiquée par le PC, puis le PC avance ou saute ailleurs selon l'instruction exécutée.

Important : le PC appartient à un process, pas directement à un champion. Un même champion peut avoir plusieurs process, donc plusieurs PC.

## 8. Quelle est la différence entre `.s` et `.cor` ?

Le fichier `.s` est le fichier source du champion. Il est lisible par un humain.

Exemple :

```asm
.name "zork"
.comment "Just a basic living program"

start:
    live %1
    zjmp %:start
```

Le fichier `.cor` est le fichier compilé. Il contient du binaire lisible par la VM.

Le pipeline est donc :

```text
champion.s -> asm -> champion.cor -> corewar
```

## 9. Quelles sont les grandes étapes du projet ?

Les grandes étapes du projet sont :

1. Écrire la documentation et comprendre la spec.
2. Créer la structure du projet, le `Makefile` et les tests avec Criterion.
3. Implémenter l'arène mémoire circulaire.
4. Implémenter les structures de base : champion, process, instruction.
5. Créer l'assembleur `asm` pour compiler les champions `.s` en `.cor`.
6. Créer le loader pour lire les fichiers `.cor`.
7. Créer la VM `corewar` pour exécuter les champions.
8. Implémenter les instructions CoreWar une par une.
9. Ajouter les règles de vie, de mort et de victoire.
10. Nettoyer, tester, optimiser et documenter le projet.
11. Ajouter plus tard une visualisation graphique avec raylib.
