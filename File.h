#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "Line.h"

std::string readFile(std::string filename);

class File
{
	public:
		File();
		File(std::string filename);
		void getLines();
		void analyseFile();
		virtual ~File();
	protected:
	private:
		std::string m_filename;
		std::vector<Line> m_lines;
		std::string m_extension;
};

#endif // FILE_H
