#ifndef SNIPER_ALG_MGR_H
#define SNIPER_ALG_MGR_H

#include "SniperKernel/ElementMgr.h"
#include "SniperKernel/AlgBase.h"

class AlgMgr : public ElementMgr<AlgBase>
{
    public :

	static AlgMgr* instance();

	bool execute();

        static bool AddAlg(ElementPtr);

    private :

	AlgMgr(const std::string& name);

	friend class AlgFactory;
	static AlgMgr* _instance;
};

#endif
