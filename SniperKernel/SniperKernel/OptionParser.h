#ifndef SNIPER_OPTION_PARSER_H
#define SNIPER_OPTION_PARSER_H

#include "SniperKernel/Parsers.h"

/**************************************************************************
 * Suppose in the options file, there exist:
 *    Object.Property = 9;
 * after calling:
 *     int  var;
 *     bool status = OptionParser::setOption("Object", "Property", var);
 * then the value "9" is assigned to "var" now.
 *************************************************************************/

namespace Gaudi { namespace Parsers { class Catalogue; } }

class OptionParser
{
    public :

	static OptionParser* instance(char* fname = 0);
	virtual ~OptionParser();

	template<class Type>
	static bool setOption(const std::string& client, const std::string& name, Type& var);

	static bool addOption(const std::string& client, const std::string& name, const std::string& value);      

	bool validate();


    private :

	OptionParser(char* fname);

	const std::string& name() { return m_name; }

	bool getValueStr(const std::string& client, const std::string& name, std::string& value);

	Gaudi::Parsers::Catalogue*  m_entries;
	std::string  m_name;

	static OptionParser* _instance;
};

template<class Type>
bool OptionParser::setOption(const std::string& client, const std::string& name, Type& var)
{
    std::string value;
    if ( _instance->getValueStr(client, name, value) ) {
	return Gaudi::Parsers::parse(var, value);
    }
    return true;
}

#endif
