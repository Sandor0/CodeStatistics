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
	Project project("projet_test");
	Project project2("projet_test2");
	File file("File.h");
	File file2("File.cpp");
	File file3("Statistics.cpp");
	File file4("Statistics.h");
	Statistics stats;

	project.addFile(file);
	project.addFile(file2);
	project2.addFile(file3);
	project2.addFile(file4);

	stats.addProject(project);
	stats.addProject(project2);

	stats.generateProjectStats();

	stats.showWholeProjectStats();


	/*std::cout << "\n\n\n\n";
	std::cout << "\n\n\n\n";
	File test3("main.cpp");
	std::cout << "\n\n\n\n";
	File test4("Line.cpp");*/
	return 0;
}
