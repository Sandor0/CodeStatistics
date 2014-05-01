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

void test();
void usage(std::string programName);
void exec(int argc, char *argv[]);


int main(int argc, char *argv[])
{
	if(argc > 1)
		exec(argc, argv);
	else
		test();
	return 0;
}

void exec(int argc, char *argv[])
{
	bool fullStats = false;
	if(argv[1] == "help" || argv[1] == "usage" || argc < 3)
	{
		usage(argv[0]);
		return;
	}
	Project project;
	Statistics stats;
    if(argv[1] == "d")
		fullStats = true;
	else if(argv[1] == "s")
		fullStats = false;
	for(int i = 2; i < argc; ++i)
		project.addFile(File(argv[i]));
	stats.addProject(project);
	stats.generateProjectStats();
	if(fullStats)
		stats.showProjectStats();
	else
		stats.showWholeProjectStats();
}

void usage(std::string programName)
{
	std::cout << "Usage : " << programName << " [ help | usage | f | s ] { files paths }" << '\n';
	std::cout << "\tf - full output, stats for each file" << '\n';
	std::cout << "\ts - simple output, global stats" << '\n';
}

void test()
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

	stats.showProjectStats();
}
