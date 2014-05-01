#include "Statistics.h"

Statistics::Statistics()
{
	//ctor
}

Statistics::~Statistics()
{
	//dtor
}

void Statistics::addProject(Project project)
{
	m_projects[project.getProjectName()] = project;
}

void Statistics::generateProjectStats()
{
	for(std::map<std::string, Project>::iterator it = m_projects.begin(); it != m_projects.end(); ++it)
	{
		generateProjectStats(it->first);
	}
}
void Statistics::generateProjectStats(std::string projectName)
{
	std::map<std::string, File> files = m_projects[projectName].getMappedFiles();
	for(std::map<std::string, File>::iterator it = files.begin(); it != files.end(); ++it)
	{
		generateFileStats(projectName, it->first);
	}
	/// TODO: generate project stats, not only file stats
}
void Statistics::generateFileStats(std::string projectName, std::string filename)
{
    std::vector<Line> lines = m_projects[projectName][filename].getLines();
    FileStats filestats;
    filestats.maxLinesLength = 0;
    filestats.minLinesLength = lines[0].size();
    filestats.averageLinesLength = 0;
    for(unsigned int i = 0; i < lines.size(); ++i)
	{
		if(lines[i].getType() != EMPTY)
		{
			if(lines[i].size() > filestats.maxLinesLength)
				filestats.maxLinesLength = lines[i].size();
			else if(lines[i].size() < filestats.minLinesLength)
				filestats.minLinesLength = lines[i].size();
			filestats.averageLinesLength+=lines[i].size();
		}
		++filestats.linesType[lines[i].getType()];
	}
	filestats.averageLinesLength/=lines.size();

	m_projectsStats[projectName].fileStats[filename] = filestats;
}


void Statistics::showProjectStats()
{
	for(std::map<std::string, Project>::iterator it = m_projects.begin(); it != m_projects.end(); ++it)
	{
        showProjectStats(it->first);
	}
}
void Statistics::showProjectStats(std::string projectName)
{
	std::cout << "Stats for project " << projectName << " :" << '\n';
	std::cout << "No project stats yet." << '\n';
}
void Statistics::showWholeProjectStats()
{
	for(std::map<std::string, Project>::iterator it = m_projects.begin(); it != m_projects.end(); ++it)
	{
        showWholeProjectStats(it->first);
	}
}
void Statistics::showWholeProjectStats(std::string projectName)
{
	showProjectStats(projectName);
	std::map<std::string, File> files = m_projects[projectName].getMappedFiles();
	for(std::map<std::string, File>::iterator it = files.begin(); it != files.end(); ++it)
	{
        showFileStats(projectName, it->first);
	}
}

void Statistics::showFileStats(std::string projectName, std::string filename)
{
	FileStats fileStats = m_projectsStats[projectName].fileStats[filename];
	std::cout << "Stats for " << filename  << " : " << '\n';
	std::cout << "\tLine of code : " << fileStats.linesType[CODE] << '\n';
	std::cout << "\tLine of code and comment : " << fileStats.linesType[CODE_AND_COMMENT] << '\n';
	std::cout << "\tLine of comment : " << fileStats.linesType[COMMENT] << '\n';
	std::cout << "\tEmpty line : " << fileStats.linesType[EMPTY] << '\n';
	std::cout << "\t---" << '\n';
	std::cout << "\tMax lines length : " << fileStats.maxLinesLength << '\n';
	std::cout << "\tMin lines length : " << fileStats.minLinesLength << '\n';
	std::cout << "\tAverage lines length : " << fileStats.averageLinesLength << '\n';

	std::cout << '\n';
}
