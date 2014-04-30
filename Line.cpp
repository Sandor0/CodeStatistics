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
	//ctor
}
Line::Line(std::string line) : m_chars(line)
{
	//ctor
}

Line::~Line()
{
	//dtor
}

void Line::setLanguage(std::string languageExtension)
{
	m_languageExtension = languageExtension;
}
bool Line::analyseLine(bool inMultilineComment)	/// return true if in multiline comment
{
	std::string multilineTag = inMultilineComment ? "*/" : "/*";
	std::string trimedLine = trim(m_chars);
	int tagPosition = inMultilineComment ? trimedLine.size()-2 : 0;
	unsigned int comment = trimedLine.find("//");
	unsigned int multilineComment = trimedLine.find(multilineTag);
	if(trimedLine.empty())
	{
		m_type = EMPTY;
		return inMultilineComment;
	}
	else if(multilineComment != trimedLine.npos)
	{
		if(multilineComment == tagPosition)
			m_type = COMMENT;
		else
			m_type = CODE_AND_COMMENT;
		return !inMultilineComment;
	}
	else if(inMultilineComment)
		m_type = COMMENT;
	else if(comment != trimedLine.npos)
	{
		if(comment == 0)
			m_type = COMMENT;
		else
			m_type = CODE_AND_COMMENT;
		return inMultilineComment;
	}
	else
		m_type = CODE;
	return inMultilineComment;
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
