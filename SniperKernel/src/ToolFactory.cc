#include "SniperKernel/ToolFactory.h"
#include "SniperKernel/ToolBase.h"
#include "SniperKernel/ToolMgr.h"
#include "SniperKernel/SniperException.h"

ToolFactory::ToolFactory(const std::string& name, ToolBase* (*creator)(const std::string&))
{
    typedef ToolBase* (*ToolCreator)(const std::string&);

    std::map<std::string, ToolCreator>::iterator it = ToolMgr::elementCreatorMap.find(name);
    if ( it != ToolMgr::elementCreatorMap.end() ) {
	std::string msg = std::string("Duplicated tool definition: ") + name;
	throw SniperException(msg);
    }
    ToolMgr::elementCreatorMap.insert(std::make_pair<std::string, ToolCreator>(name, creator));
}
