#ifndef LINE_H
#define LINE_H

#include <iostream>

#define CODE				0
#define COMMENT				1
#define CODE_AND_COMMENT	2
#define EMPTY				3

class Line
{
	public:
		Line();
		Line(std::string line);
		virtual ~Line();

		void setLanguage(std::string languageExtension);
		void analyseLine(Line *line = NULL);
		std::string removeString(std::string line);

		int getType() const;
		bool isInMultilineComment() const;

		char operator[](int i);

		friend std::ostream& operator<<(std::ostream& out, const Line& line)
		{
			return out << line.m_chars;
		}
	protected:
	private:
		std::string m_chars;
		std::string m_languageExtension;
		int m_type;
		bool m_isInMultilineComment;
		char m_inString;
};


#endif // LINE_H
