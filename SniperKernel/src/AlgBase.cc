#include "SniperKernel/AlgBase.h"
#include "SniperKernel/SvcMgr.h"

SvcBase* AlgBase::service(const std::string& name)
{
    return SvcMgr::get(name);
}

const enum BaseType AlgBase::_class_type = Sniper_CPP;
