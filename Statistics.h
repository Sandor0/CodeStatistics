#ifndef STATISTICS_H
#define STATISTICS_H

/**
 *
 * 	Project Stats
 *		Max lines in file
 *		Min lines in file
 *		Average lines in file
 *		Max lines length in project
 *		Min lines length in project
 *		Average lines length in project
 *		Number of | code only | lines
 *				  | comment	  |
 *				  | code&comm |
 *				  | empty     |
 *		---- Advanced
 *		Number of functions in all file
 *		Max functions in file
 *		Min functions in file
 *		Average functions in file
 *
 *	File Stats
 *		Max lines length
 *		Min lines length
 *		Average lines length
 *		Number of | code only | lines
 *				  | comment	  |
 *				  | code&comm |
 *				  | empty     |
 *	Line Stats
 *		Length of line
 *
 *
*/

#include <iostream>
#include <map>

#include "Project.h"
#include "File.h"

typedef std::map<int, int> LinesType;

struct FileStats
{
	unsigned int maxLinesLength;
	unsigned int minLinesLength;
	unsigned int averageLinesLength;

	LinesType linesType;
};

struct ProjectStats
{
	unsigned int maxLinesCount;
	unsigned int minLinesCount;
	unsigned int averageLinesCount;

	unsigned int maxLinesLength;
	unsigned int minLinesLength;
	unsigned int averageLinesLength;

	LinesType linesType;

	std::map<std::string, FileStats> fileStats;
};

class Statistics
{
	public:
		Statistics();
		virtual ~Statistics();

		void addProject(Project project);

		void generateProjectStats();
		void generateProjectStats(std::string projectName);
		void generateFileStats(std::string projectName, std::string filename);

		void showProjectStats();
		void showWholeProjectStats();
		void showProjectStats(std::string projectName);
		void showWholeProjectStats(std::string projectName);
		void showFileStats(std::string projectName, std::string filename);

	protected:
	private:
		std::map<std::string, Project> m_projects;
		std::map<std::string, ProjectStats> m_projectsStats;
};

#endif // STATISTICS_H
