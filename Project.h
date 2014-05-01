#ifndef PROJECT_H
#define PROJECT_H

#include <string>

#include "File.h"

class Project
{
	public:
		Project();
		Project(std::string projectName);
		virtual ~Project();

		std::string getProjectName() const;

		void addFile(std::string filename);
		void addFile(File file);

		File operator[](std::string filename);
		std::map<std::string, File> getMappedFiles() const;
	protected:
	private:
		std::map<std::string, File> m_files;
		std::string m_projectName;
};

#endif // PROJECT_H
