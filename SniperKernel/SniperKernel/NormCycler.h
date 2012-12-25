#ifndef SNIPER_NORM_CYCLER_H
#define SNIPER_NORM_CYCLER_H

#include "SniperKernel/PhyEventBuf.h"
#include "SniperKernel/SvcBase.h"
#include "SniperKernel/ICycler.h"
#include "SniperKernel/EvtObject.h"

class UserBufMgr;

class NormCycler : public SvcBase,
                   public PhyEventBuf,
                   virtual public ICycler
{
    public :

	NormCycler(const std::string& name);
	virtual ~NormCycler();

	virtual bool initialize();
	virtual bool finalize();

	//move the cursor to the next nth event in buffer
	virtual EvtObject* next(int nth = 1);
	//append one event to the buffer that exceeds the time window
	virtual PhyEvent* expand();

	PhyEventBuf* dataBuffer();

    protected :

	virtual PhyEvent* theNext();

	virtual void pushBack(PhyEvent* evt);
	virtual void trimDated();
	virtual void fillFresh();

	ICycler*  m_is;
	PhyEvent* m_cur;
	PhyEvent* m_theBeyond;

	UserBufMgr* m_userBufMgr;

	std::vector<double> m_window;
};

#endif
