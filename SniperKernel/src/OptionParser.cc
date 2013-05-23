#include "SniperKernel/OptionParser.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/SniperLog.h"
#include "Parsers/ParserUtils.h"
#include "Parsers/Catalogue.h"

OptionParser* OptionParser::_instance = 0;

OptionParser* OptionParser::instance(char* fname)
{
    if ( _instance == 0 ) {
	_instance = new OptionParser(fname);
    }
    return _instance;
}

bool OptionParser::addOption(const std::string& client, const std::string& name, const std::string& value)
{
    std::string stringResult;
    std::vector<std::string> vectorResult;
    bool ok = Gaudi::Parsers::Utils::parseValue(value, stringResult, vectorResult);
    std::cout << "ADD OPTION: " << ok << std::endl;
    if ( ok ) {
	bool isVector = (vectorResult.size()>0) || (stringResult=="{}");
	if ( isVector ) {
	    Gaudi::Parsers::PropertyEntry property(name, vectorResult);
	    if ( _instance->m_entries->findProperty(client, name, property, false) ) {
		int count = 0;
		property.removeValues(vectorResult, count);
		property.addValues(vectorResult);
	    }
	    _instance->m_entries->addProperty(client, property);
	}
	return true;
    } else {
        Gaudi::Parsers::PropertyEntry property(name, value);
        _instance->m_entries->addProperty(client, property);
    }
    return false;
}

OptionParser::OptionParser(char* fname)
    : m_name("OptionParser")
{
    m_entries = new Gaudi::Parsers::Catalogue();
    std::vector<std::string> m_included;
    Gaudi::Parsers::Parser parser(*m_entries, m_included);

    bool sc = parser.parse( fname );
    if ( !sc ) {
	using Gaudi::Parsers::Message;
	const std::vector<Message>& messages = parser.messages();
	for (std::vector<Message>::const_iterator it = messages.begin(); it != messages.end(); ++it ) {
	    if ( it->severity() == Gaudi::Parsers::Message::E_ERROR ) {
		LogError << it->message() << std::endl;
	    }
	}
	delete m_entries;
	throw SniperException("OptionParser: error while parsing option file");
    }
}

OptionParser::~OptionParser()
{
    delete m_entries;
}

bool OptionParser::validate()
{
    Gaudi::Parsers::Catalogue::CatalogueT left = m_entries->catalogue();
    if ( ! left.empty() ) {
	LogError << "INVALID OPTIONS FOUND." << std::endl;
	std::cout << "Attention: following line(s) in your configuration file is(are) not recognized:" << std::endl;
	m_entries->print(std::cout);
	std::cout << "Please ensure your spell is right, otherwise remove the useless settings!" << std::endl;
	return false;
    }
    return true;
}

bool OptionParser::getValueStr(const std::string& client, const std::string& name, std::string& value)
{
    Gaudi::Parsers::PropertyEntry property;
    if ( m_entries->findProperty(client, name, property, true) ) {
	value = property.value();
	return true;
    }
    return false;
}
