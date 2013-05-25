#include "SniperKernel/SvcMgr.h"
#include "SniperKernel/SniperLog.h"

SvcMgr* SvcMgr::_instance = 0;

SvcMgr* SvcMgr::instance()
{
    if ( _instance == 0 ) {
	_instance = new SvcMgr("SvcMgr");
    }
    return _instance;
}

SvcMgr::SvcMgr(const std::string& objname)
    : ElementMgr<SvcBase>(objname)
{
    for ( std::list< ElementMgr >::iterator it = m_elements.begin(); it != m_elements.end(); ++it ) {
	LogInfo << "Load service    : " << (*it)->name() << std::endl;
    }
}
