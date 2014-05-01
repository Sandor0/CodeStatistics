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
	Project bigProject("CodeStatistics");
	Project crypto("Cryptographics");
	std::vector<File> files;
	files.push_back(File("File.h"));
	files.push_back(File("File.cpp"));
	files.push_back(File("Line.h"));
	files.push_back(File("Line.cpp"));
	files.push_back(File("Statistics.h"));
	files.push_back(File("Statistics.cpp"));
	files.push_back(File("Project.h"));
	files.push_back(File("Project.cpp"));
	files.push_back(File("main.cpp"));

	std::vector<File> cryptoFiles;
	cryptoFiles.push_back(File("../Cryptographie/Cryptography.cpp"));
	cryptoFiles.push_back(File("../Cryptographie/Cryptography.h"));
	cryptoFiles.push_back(File("../Cryptographie/Others.cpp"));
	cryptoFiles.push_back(File("../Cryptographie/Others.h"));
	cryptoFiles.push_back(File("../Cryptographie/StatsFile.cpp"));
	cryptoFiles.push_back(File("../Cryptographie/StatsFile.h"));
	cryptoFiles.push_back(File("../Cryptographie/Steganography.cpp"));
	cryptoFiles.push_back(File("../Cryptographie/Steganography.h"));
	cryptoFiles.push_back(File("../Cryptographie/main.cpp"));

	Statistics stats;

	for(int i = 0; i < files.size(); ++i)
		bigProject.addFile(files[i]);
	for(int i = 0; i < cryptoFiles.size(); ++i)
		crypto.addFile(cryptoFiles[i]);

	stats.addProject(bigProject);
	stats.addProject(crypto);

	stats.generateProjectStats();

	stats.showWholeProjectStats();


	/*std::cout << "\n\n\n\n";
	std::cout << "\n\n\n\n";
	File test3("main.cpp");
	std::cout << "\n\n\n\n";
	File test4("Line.cpp");*/
	return 0;
}
