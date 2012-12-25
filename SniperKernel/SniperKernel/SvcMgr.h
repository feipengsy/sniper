#ifndef SNIPER_SVC_MGR_H
#define SNIPER_SVC_MGR_H

#include "SniperKernel/ElementMgr.h"
#include "SniperKernel/SvcBase.h"

class SvcMgr : public ElementMgr<SvcBase>
{
    public :

	static SvcMgr* instance();


    private :

	SvcMgr(const std::string& name);

	friend class SvcFactory;
	static SvcMgr* _instance;
};

#endif
