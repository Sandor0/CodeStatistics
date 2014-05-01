#include "Project.h"

Project::Project()
{
	m_projectName = "Untitled";
}

Project::Project(std::string projectName) : m_projectName(projectName)
{

}

Project::~Project()
{
	//dtor
}

std::string Project::getProjectName() const
{
	return m_projectName;
}

void Project::addFile(std::string filename)
{
	m_files[filename] = File(filename);
}
void Project::addFile(File file)
{
	m_files[file.getFilename()] = file;
}

File Project::operator[](std::string filename)
{
	return m_files[filename];
}
std::map<std::string, File> Project::getMappedFiles() const
{
	return m_files;
}


