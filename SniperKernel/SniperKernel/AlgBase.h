#ifndef SNIPER_ALGBASE_H
#define SNIPER_ALGBASE_H

#include "SniperKernel/OptionParser.h"
#include "SniperKernel/SvcBase.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/BaseType.h"
#include <string>

class AlgBase
{
  public:

    AlgBase(const std::string& name, BaseType bt=Sniper_CPP) 
        : m_name(name), m_class_type(bt) {}
    virtual ~AlgBase(){}

    virtual bool initialize() = 0;
    virtual bool execute() = 0;
    virtual bool finalize() = 0;

    const std::string& name() { return m_name; }

    SvcBase* service(const std::string& name);

    template<typename Type>
    bool setOption(const std::string& option, Type& var);

    const BaseType get_class_type()  {
        return m_class_type;
    }

  protected :

    std::string m_name;

    BaseType m_class_type;

  private :
    //following interfaces are not supported
    AlgBase();
    AlgBase(const AlgBase&);
    AlgBase& operator=(const AlgBase&);
};

template<typename Type>
bool AlgBase::setOption(const std::string& option, Type& var)
{
    return OptionParser::setOption(m_name, option, var);
}

#endif //ALGBASE_H
