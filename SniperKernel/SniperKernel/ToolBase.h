#ifndef SNIPER_TOOL_BASE_H
#define SNIPER_TOOL_BASE_H

#include "SniperKernel/OptionParser.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/BaseType.h"
#include <string>

class ToolBase
{
    public :

	ToolBase(const std::string& name) : m_name(name) {}
	virtual ~ToolBase() {}

	const std::string& name() { return m_name; }

	template<typename Type>
	bool setOption(const std::string& option, Type& var);
    virtual const enum BaseType get_class_type() const {
        return _class_type;
    }


    protected :

	std::string m_name;
    static const enum BaseType _class_type;

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
