#include "File.h"

File::File()
{
	//ctor
}
File::File(std::string filename) : m_filename(filename)
{
	m_extension = m_filename.substr(m_filename.rfind('.')+1);
	this->analyseFile();
}

File::~File()
{
	//dtor
}


void File::analyseFile()
{
	std::map<int, int> stats;
	this->getLines();
	bool inMultilineComment = false;
	for(unsigned int i = 0; i < m_lines.size(); ++i)	/// TODO: Add an if statement for multi-language file (html, php) with detection of the language of the current line
	{
		m_lines[i].setLanguage(m_extension);
		inMultilineComment = m_lines[i].analyseLine(inMultilineComment);
		std::cout << i << '\t';
		++stats[m_lines[i].getType()];
		switch(m_lines[i].getType())
		{
			case CODE:
				std::cout << "CODE";
				break;
			case COMMENT:
				std::cout << "COMMENT";
				break;
			case CODE_AND_COMMENT:
				std::cout << "C&C";
				break;
			case EMPTY:
				std::cout << "EMPTY";
				break;
			default:
				std::cout << "unknow";
				break;
		}
		std::cout << '\t' << m_lines[i] << '\n';
	}
	std::cout << '\n';
	std::cout << "CODE : " << stats[CODE] << '\n';
	std::cout << "COMMENT : " << stats[COMMENT] << '\n';
	std::cout << "CODE AND COMMENT : " << stats[CODE_AND_COMMENT] << '\n';
	std::cout << "EMPTY : " << stats[EMPTY] << '\n';
}

void File::getLines()
{
	std::string rawFile = readFile(m_filename);
	std::vector<std::string> lines;
	std::string line;
	for(unsigned int i = 0; i < rawFile.size(); ++i)
	{
		if(rawFile[i] == '\n')
		{
			m_lines.push_back(Line(line));
			line.clear();
		}
		else
			line+=rawFile[i];
	}
	/*for(int i = 0; i < m_lines.size(); ++i)
		std::cout << i+1 << '\t' << m_lines[i] << '\n';*/
}

std::string readFile(std::string filename)
{
	std::ifstream file(filename.c_str());
	std::string ret;
	while(file.good())
		ret+=file.get();
	file.close();
	return ret;
}
