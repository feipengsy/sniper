#ifndef SNIPER_SVC_BASE_H
#define SNIPER_SVC_BASE_H

#include "SniperKernel/OptionParser.h"
#include "SniperKernel/property.hh"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/BaseType.h"
#include <string>

class SvcBase
{
    public :

	SvcBase(const std::string& name, BaseType bt=Sniper_CPP) 
            : m_name(name), m_class_type(bt) {}
	virtual ~SvcBase() {}

	const std::string& name() { return m_name; }

	virtual bool initialize() = 0;
	virtual bool finalize() = 0;

	template<typename Type>
	bool setOption(const std::string& option, Type& var);

	template<typename Type>
	bool declProp(const std::string& option, Type& var);
    const BaseType get_class_type() {
        return m_class_type;
    }

    protected :

	std::string m_name;
    BaseType m_class_type;

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

template<typename Type>
bool SvcBase::declProp(const std::string& option, Type& var)
{
    MyProperty* mp = declareProperty(m_name, option, var);
    if (mp) {
        return true;
    } else {
        return false;
    }
}

#endif
