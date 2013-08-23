#ifndef SNIPER_TOOL_BASE_H
#define SNIPER_TOOL_BASE_H

#include "SniperKernel/property.hh"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/BaseType.h"
#include <string>

class ToolBase
{
    public :

	ToolBase(const std::string& name, BaseType bt=Sniper_CPP) 
            : m_name(name), m_class_type(bt) {}
	virtual ~ToolBase() {}

	const std::string& name() { return m_name; }

    template<typename Type>
    bool declProp(const std::string& option, Type& var);

    MyProperty* getProp(const std::string& option) {
        return getProperty(m_name, option);
    }

    const BaseType get_class_type()  {
        return m_class_type;
    }

    protected :

	std::string m_name;
    enum BaseType m_class_type;

    private :
	ToolBase();  //not supported
	ToolBase(const ToolBase&);  //not supported
	ToolBase& operator=(const ToolBase&);  //not supported
};

template<typename Type>
bool ToolBase::declProp(const std::string& option, Type& var)
{
    MyProperty* mp = declareProperty(m_name, option, var);
    if (mp) {
        return true;
    } else {
        return false;
    }
}

#endif
