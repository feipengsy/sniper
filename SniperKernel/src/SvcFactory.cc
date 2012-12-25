#include "SniperKernel/SvcFactory.h"
#include "SniperKernel/SvcBase.h"
#include "SniperKernel/SvcMgr.h"
#include "SniperKernel/SniperException.h"

SvcFactory::SvcFactory(const std::string& name, SvcBase* (*creator)(const std::string&))
{
    typedef SvcBase* (*SvcCreator)(const std::string&);

    std::map<std::string, SvcCreator>::iterator it = SvcMgr::elementCreatorMap.find(name);
    if ( it != SvcMgr::elementCreatorMap.end() ) {
	std::string msg = std::string("Duplicated service definition: ") + name;
	throw SniperException(msg);
    }
    SvcMgr::elementCreatorMap.insert(std::make_pair<std::string, SvcCreator>(name, creator));
}
