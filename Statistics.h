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

#include "File.h"

typedef std::map<int, int> LineType;

struct FileStats
{
	unsigned int maxLinesLength;
	unsigned int minLinesLength;
	unsigned int averageLinesLength;

	LineType lineType;
};

class Statistics
{
	public:
		Statistics();
		Statistics(File &file);
		virtual ~Statistics();

		void generateStats();

		void showFileStats();
		void showLineStats(int line);

	protected:
	private:
		File m_file;
		FileStats m_filestats;
};

#endif // STATISTICS_H
