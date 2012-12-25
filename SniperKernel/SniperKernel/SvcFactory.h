#ifndef SNIPER_SVC_FACTORY_H
#define SNIPER_SVC_FACTORY_H

#include <string>

class SvcBase;

class SvcFactory
{
    public :
	SvcFactory(const std::string& name, SvcBase* (*creator)(const std::string&));
};

#define DECLARE_SERVICE(SvcClass) \
SvcBase* _svc_##SvcClass##_creator_(const std::string& objName) { return new SvcClass(objName); } \
SvcFactory  _reg_svc_##SvcClass##_creator(#SvcClass, &_svc_##SvcClass##_creator_)

#endif
