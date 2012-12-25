#ifndef SNIPER_SVC_BASE_H
#define SNIPER_SVC_BASE_H

#include "SniperKernel/OptionParser.h"
#include "SniperKernel/SniperLog.h"
#include <string>

class SvcBase
{
    public :

	SvcBase(const std::string& name) : m_name(name) {}
	virtual ~SvcBase() {}

	const std::string& name() { return m_name; }

	virtual bool initialize() = 0;
	virtual bool finalize() = 0;

	template<typename Type>
	bool setOption(const std::string& option, Type& var);

    protected :

	std::string m_name;

    private :
	SvcBase();  //not supported
	SvcBase(const SvcBase&);  //not supported
	SvcBase& operator=(const SvcBase&);  //not supported
};

template<typename Type>
bool SvcBase::setOption(const std::string& option, Type& var)
{
    return OptionParser::setOption(m_name, option, var);
}

#endif
