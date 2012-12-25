#include "SniperKernel/UserBufMgr.h"
#include "SniperKernel/SniperLog.h"

UserBufMgr* UserBufMgr::_instance = 0;

template<> ElementMgr<UserBuffer>::ElementMgr(const std::string& name)
    : m_name(name)
{
    std::vector<std::string> vNames;
    OptionParser::setOption(name, "Selectors", vNames);

    for(std::vector<std::string>::iterator i=vNames.begin(); i!=vNames.end(); ++i) {
	std::string typName = *i;
	std::string objName = typName;
	std::string::size_type pseg = typName.find('/', 0);
	if ( pseg != std::string::npos ) {
	    typName = typName.substr(0, pseg);
	    objName = objName.substr(pseg+1, std::string::npos);
	}

	Type2CreatorMap::iterator j = elementCreatorMap.find(typName);
	if ( j == elementCreatorMap.end() ) {
	    std::string msg = name + ": unknown selector " + typName;
	    throw SniperException(msg);
	}
	UserBuffer* obj = (j->second)(objName);
	m_elements.push_back(obj);
	name2obj[objName] = obj;
    }
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
    for ( std::list<UserBuffer*>::iterator it = m_elements.begin();
	    it != m_elements.end(); ++it ) {
	(*it)->tryPushBack(evt);
    }
}

void UserBufMgr::synchronize(PhyEventBuf* buf)
{
    for ( std::list<UserBuffer*>::iterator it = m_elements.begin();
	    it != m_elements.end(); ++it ) {
	(*it)->synchronize(buf);
    }
}

UserBufMgr::UserBufMgr(const std::string& objname)
    : ElementMgr<UserBuffer>(objname)
{
}
