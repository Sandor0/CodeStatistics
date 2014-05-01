#include "Statistics.h"

Statistics::Statistics()
{
	//ctor
}

Statistics::Statistics(File &file)
{
    m_file = file;
    this->generateStats();
}

Statistics::~Statistics()
{
	//dtor
}

void Statistics::generateStats()
{
    std::vector<Line> lines = m_file.getLines();
    m_filestats.maxLinesLength = 0;
    m_filestats.minLinesLength = lines[0].size();
    m_filestats.averageLinesLength = 0;
    for(unsigned int i = 0; i < lines.size(); ++i)
	{
		if(lines[i].getType() != EMPTY)
		{
			if(lines[i].size() > m_filestats.maxLinesLength)
				m_filestats.maxLinesLength = lines[i].size();
			else if(lines[i].size() < m_filestats.minLinesLength)
				m_filestats.minLinesLength = lines[i].size();
			m_filestats.averageLinesLength+=lines[i].size();
		}
		++m_filestats.lineType[lines[i].getType()];
	}
	m_filestats.averageLinesLength/=lines.size();
}

void Statistics::showFileStats()
{
    std::cout << "Stats for " << m_file.getFilename() << '\n';
	std::cout << "Max lines length : " << m_filestats.maxLinesLength << '\n';
	std::cout << "Min lines length : " << m_filestats.minLinesLength << '\n';
	std::cout << "Average lines length : " << m_filestats.averageLinesLength << '\n';
	std::cout << "Line of code : " << m_filestats.lineType[CODE] << '\n';
	std::cout << "Line of code and comment : " << m_filestats.lineType[CODE_AND_COMMENT] << '\n';
	std::cout << "Line of comment : " << m_filestats.lineType[COMMENT] << '\n';
	std::cout << "Empty line : " << m_filestats.lineType[EMPTY] << '\n';
}
