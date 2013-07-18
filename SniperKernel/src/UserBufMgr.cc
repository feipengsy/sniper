#include "SniperKernel/UserBufMgr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/property.hh"

UserBufMgr* UserBufMgr::_instance = 0;

template<> ElementMgr<UserBuffer>::ElementMgr(const std::string& name)
    : m_name(name)
{
    declareProperty(name, "Selectors", vNames);

}

template<> bool ElementMgr<UserBuffer>::initialize()
{
    return true;
}

template<> bool ElementMgr<UserBuffer>::finalize()
{
    return true;
}

UserBufMgr* UserBufMgr::instance()
{
    if ( _instance == 0 ) {
	_instance = new UserBufMgr("UserBufMgr");
    }
    return _instance;
}

void UserBufMgr::release()
{
    if ( _instance != 0 ) {
	delete _instance;
	_instance = 0;
    }
}

PhyEventBuf* UserBufMgr::bufWithSelector(const std::string& selector)
{
    return get(selector, false);
}

void UserBufMgr::tryPushBack(PhyEvent* evt)
{
    for ( std::list< ElementPtr >::iterator it = m_elements.begin();
	    it != m_elements.end(); ++it ) {
	(*it)->tryPushBack(evt);
    }
}

void UserBufMgr::synchronize(PhyEventBuf* buf)
{
    for ( std::list< ElementPtr >::iterator it = m_elements.begin();
	    it != m_elements.end(); ++it ) {
	(*it)->synchronize(buf);
    }
}

UserBufMgr::UserBufMgr(const std::string& objname)
    : ElementMgr<UserBuffer>(objname)
{
}
