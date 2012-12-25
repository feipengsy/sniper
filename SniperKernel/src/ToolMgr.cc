#include "SniperKernel/ToolMgr.h"
#include "SniperKernel/SniperLog.h"

ToolMgr* ToolMgr::_instance = 0;

template<> bool ElementMgr<ToolBase>::initialize()
{
    return true;
}

template<> bool ElementMgr<ToolBase>::finalize()
{
    return true;
}

ToolMgr* ToolMgr::instance()
{
    if ( _instance == 0 ) {
	_instance = new ToolMgr("ToolMgr");
    }
    return _instance;
}

ToolMgr::ToolMgr(const std::string& objname)
    : ElementMgr<ToolBase>(objname)
{
    //for ( std::list<ToolBase*>::iterator it = m_elements.begin(); it != m_elements.end(); ++it ) {
    //    LogInfo << "Load tools : " << (*it)->name() << std::endl;
    //}
}
