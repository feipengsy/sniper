#ifndef SNIPER_EVT_SELECTOR_H
#define SNIPER_EVT_SELECTOR_H

#include "SniperKernel/SniperLog.h"
#include "SniperKernel/property.hh"
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
        bool declProp(const std::string& option, Type& var);

    protected :

	std::string m_name;

    private :
	EvtSelector();  //not supported
	EvtSelector(const EvtSelector&);  //not supported
	EvtSelector& operator=(const EvtSelector&);  //not supported
};

template<typename Type>
bool EvtSelector::declProp(const std::string& option, Type& var)
{
    MyProperty* mp = declareProperty(m_name, option, var);
    if (mp) {
        return true;
    } else {
        return false;
    }
}

#endif
