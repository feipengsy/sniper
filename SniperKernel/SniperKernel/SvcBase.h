#ifndef SNIPER_SVC_BASE_H
#define SNIPER_SVC_BASE_H

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
	bool declProp(const std::string& option, Type& var);

    MyProperty* getProp(const std::string& option) {
        return getProperty(m_name, option);
    }

    bool setProp(const std::string& option, bp::object& obj) {
        return setProperty(m_name, option, obj);
    }

    BaseType get_class_type() {
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
