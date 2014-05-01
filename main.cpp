#include <iostream>
#include <vector>

#include "File.h"
#include "Statistics.h"

/**
 * 1. Nombre de lignes 	| de code 				  |	d'un | projet  |
 *						| de commentaires		  |		 | fichier |
 *						| de code et commentaires |
 *						| vide					  |
 *
 * Taille | maximale | des | fichiers  | d'un projet
 * 		  | minimale |     | lignes    |
 *		  | moyenne  |     | fonctions |
 *		  | etc...   |
 *
 * Statistiques sur les différents languages utilisés
 *
 * Représentation graphiques des données
 *
 *
**/

using namespace std;

int main(int argc, char *argv[])
{
	File file("File.h");
	Statistics stats(file);
	stats.showFileStats();
	std::cout << "\n\n\n\n";
	File test2("File.cpp");
	std::cout << "\n\n\n\n";
	File test3("main.cpp");
	std::cout << "\n\n\n\n";
	File test4("Line.cpp");
	return 0;
}
