#ifndef SNIPER_TOOL_BASE_H
#define SNIPER_TOOL_BASE_H

#include "SniperKernel/OptionParser.h"
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
	bool setOption(const std::string& option, Type& var);

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
bool ToolBase::setOption(const std::string& option, Type& var)
{
    return OptionParser::setOption(m_name, option, var);
}

#endif
