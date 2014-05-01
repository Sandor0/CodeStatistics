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

/// =====================
/// Generate statistics
/// =====================

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
		generateFileStats(projectName, it->first);

	ProjectStats projectStats = m_projectsStats[projectName];
	projectStats.maxLinesLength = 0;
    projectStats.minLinesLength = m_projectsStats[projectName].fileStats.begin()->second.minLinesLength;
    projectStats.averageLinesLength = 0;

	projectStats.maxLinesCount = 0;
    projectStats.minLinesCount = files.begin()->second.numberOfLines();
    projectStats.averageLinesCount = 0;
	for(std::map<std::string, File>::iterator it = files.begin(); it != files.end(); ++it)
	{
		if(m_projectsStats[projectName].fileStats[it->first].maxLinesLength > projectStats.maxLinesLength)
			projectStats.maxLinesLength = m_projectsStats[projectName].fileStats[it->first].maxLinesLength;
		else if(m_projectsStats[projectName].fileStats[it->first].minLinesLength < projectStats.minLinesLength)
			projectStats.minLinesLength = m_projectsStats[projectName].fileStats[it->first].minLinesLength;
		projectStats.averageLinesLength+=m_projectsStats[projectName].fileStats[it->first].averageLinesLength;

		if(it->second.numberOfLines() > projectStats.maxLinesCount)
			projectStats.maxLinesCount = it->second.numberOfLines();
		else if(it->second.numberOfLines() < projectStats.minLinesCount)
			projectStats.minLinesCount = it->second.numberOfLines();
		projectStats.averageLinesCount+=it->second.numberOfLines();

		projectStats.linesType[CODE]+=m_projectsStats[projectName].fileStats[it->first].linesType[CODE];
		projectStats.linesType[CODE_AND_COMMENT]+=m_projectsStats[projectName].fileStats[it->first].linesType[CODE_AND_COMMENT];
		projectStats.linesType[COMMENT]+=m_projectsStats[projectName].fileStats[it->first].linesType[COMMENT];
		projectStats.linesType[EMPTY]+=m_projectsStats[projectName].fileStats[it->first].linesType[EMPTY];
	}
	projectStats.averageLinesCount/=files.size();
	projectStats.averageLinesLength/=files.size();

	m_projectsStats[projectName] = projectStats;
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


/// =====================
/// Display statistics
/// =====================

void Statistics::showProjectStats()
{
	for(std::map<std::string, Project>::iterator it = m_projects.begin(); it != m_projects.end(); ++it)
	{
        showProjectStats(it->first);
	}
}
void Statistics::showProjectStats(std::string projectName)
{
	ProjectStats projectStats = m_projectsStats[projectName];
	unsigned int total = projectStats.linesType[CODE] + projectStats.linesType[CODE_AND_COMMENT] + projectStats.linesType[COMMENT] + projectStats.linesType[EMPTY];
	std::cout << "Stats for project " << projectName << " (" << projectStats.fileStats.size() << " files) :" << '\n';
	std::cout << "\tLine of code : " << projectStats.linesType[CODE] << '\n';
	std::cout << "\tLine of code and comment : " << projectStats.linesType[CODE_AND_COMMENT] << '\n';
	std::cout << "\tLine of comment : " << projectStats.linesType[COMMENT] << '\n';
	std::cout << "\tEmpty line : " << projectStats.linesType[EMPTY] << '\n';
	std::cout << "\tTotal : " << total << '\n';
	std::cout << "\t----" << '\n';
	std::cout << "\tMax line count : " << projectStats.maxLinesCount << '\n';
	std::cout << "\tMin line count : " << projectStats.minLinesCount << '\n';
	std::cout << "\tAverage line count : " << projectStats.averageLinesCount << '\n';
	std::cout << "\t----" << '\n';
	std::cout << "\tMax line length : " << projectStats.maxLinesLength << '\n';
	std::cout << "\tMin line length : " << projectStats.minLinesLength << '\n';
	std::cout << "\tAverage line length : " << projectStats.averageLinesLength << '\n';
	std::cout << '\n';
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
	unsigned int total = fileStats.linesType[CODE] + fileStats.linesType[CODE_AND_COMMENT] + fileStats.linesType[COMMENT] + fileStats.linesType[EMPTY];
	std::cout << "\tStats for " << filename  << " : " << '\n';
	std::cout << "\t\tLine of code : " << fileStats.linesType[CODE] << '\n';
	std::cout << "\t\tLine of code and comment : " << fileStats.linesType[CODE_AND_COMMENT] << '\n';
	std::cout << "\t\tLine of comment : " << fileStats.linesType[COMMENT] << '\n';
	std::cout << "\t\tEmpty line : " << fileStats.linesType[EMPTY] << '\n';
	std::cout << "\t\tTotal : " << total << '\n';
	std::cout << "\t\t---" << '\n';
	std::cout << "\t\tMax lines length : " << fileStats.maxLinesLength << '\n';
	std::cout << "\t\tMin lines length : " << fileStats.minLinesLength << '\n';
	std::cout << "\t\tAverage lines length : " << fileStats.averageLinesLength << '\n';

	std::cout << '\n';
}
