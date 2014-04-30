#include "Line.h"

std::string rtrim(std::string s, const std::string& delimiters = " \f\n\r\t\v" )
{
   s.erase( s.find_last_not_of( delimiters ) + 1 );
   return s;
}

std::string ltrim(std::string s,  const std::string& delimiters = " \f\n\r\t\v" )
{
   s.erase( 0, s.find_first_not_of( delimiters ) );
   return s;
}

std::string trim(std::string s, const std::string& delimiters = " \f\n\r\t\v" )
{
    s.erase( s.find_last_not_of( delimiters ) + 1 ).erase( 0, s.erase( s.find_last_not_of( delimiters ) + 1 ).find_first_not_of( delimiters ) );
    return s;
}

Line::Line()
{
	m_isInMultilineComment = false;
	m_inString = 0;
}
Line::Line(std::string line) : m_chars(line)
{
	m_isInMultilineComment = false;
	m_inString = 0;
}

Line::~Line()
{
	//dtor
}

void Line::setLanguage(std::string languageExtension)
{
	m_languageExtension = languageExtension;
}

std::string Line::removeString(std::string line)
{
	unsigned int quoteMarkCount = 0;
	unsigned int lastFoundPos = 0;
    while((lastFoundPos = line.find('"', lastFoundPos+1)) != line.npos) ++quoteMarkCount;
    if(m_inString == 0 && quoteMarkCount == 0) return line;
	bool inString = m_inString == 0 ? false : true;
	for(unsigned int i = 0; i < line.size(); ++i)
	{
		if(inString)
		{
			if(line[i] == m_inString)
			{
				m_inString = 0;
				inString = false;
			}
			line.erase(line.begin() + i--);
		}
		else
		{
			if(line[i] == '\'' || line[i] == '"')
			{
				m_inString = line[i];
				inString = true;
				line.erase(line.begin() + i--);
			}
		}
	}
	return line;
}
void Line::analyseLine(Line *previousLine)
{
	bool inMultilineComment = previousLine != NULL ? previousLine->isInMultilineComment() : false;

	std::string multilineTag = inMultilineComment ? "*/" : "/*";
	std::string trimedLine = trim(m_chars);

	if(trimedLine.empty())
	{
		m_type = EMPTY;
		m_isInMultilineComment = inMultilineComment;
		return;
	}

	trimedLine = removeString(trimedLine);

	int tagPosition = inMultilineComment ? trimedLine.size()-2 : 0;
	unsigned int simpleCommentPosition = trimedLine.find("//");
	unsigned int multilineCommentPosition = trimedLine.find(multilineTag);

	if(multilineCommentPosition != trimedLine.npos)
	{
		if(multilineCommentPosition == tagPosition)
			m_type = COMMENT;
		else
			m_type = CODE_AND_COMMENT;
		m_isInMultilineComment = !inMultilineComment;
		return;
	}
	else if(inMultilineComment)
		m_type = COMMENT;
	else if(simpleCommentPosition != trimedLine.npos)
	{
		if(simpleCommentPosition == 0)
			m_type = COMMENT;
		else
			m_type = CODE_AND_COMMENT;
		m_isInMultilineComment = inMultilineComment;
		return;
	}
	else
		m_type = CODE;
	m_isInMultilineComment = inMultilineComment;
}

int Line::getType() const
{
	return m_type;
}

char Line::operator[](int i)
{
	if(i >= 0 && i < m_chars.size())
		return m_chars[i];
}

bool Line::isInMultilineComment() const
{
	return m_isInMultilineComment;
}
