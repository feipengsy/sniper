#ifndef SNIPER_EVT_SELECTOR_H
#define SNIPER_EVT_SELECTOR_H

#include "SniperKernel/OptionParser.h"
#include "SniperKernel/SniperLog.h"
#include <string>

class PhyEvent;

class EvtSelector
{
    public :

	EvtSelector(const std::string& name) : m_name(name) {}
	virtual ~EvtSelector() {}

	virtual bool select(PhyEvent* evt) = 0;

	const std::string& name() { return m_name; }

	template<typename Type>
	bool setOption(const std::string& option, Type& var);

    protected :

	std::string m_name;

    private :
	EvtSelector();  //not supported
	EvtSelector(const EvtSelector&);  //not supported
	EvtSelector& operator=(const EvtSelector&);  //not supported
};

template<typename Type>
bool EvtSelector::setOption(const std::string& option, Type& var)
{
    return OptionParser::setOption(m_name, option, var);
}

#endif
