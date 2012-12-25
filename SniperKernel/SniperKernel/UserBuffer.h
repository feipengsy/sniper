#ifndef SNIPER_USER_BUFFER_H
#define SNIPER_USER_BUFFER_H

#include "SniperKernel/PhyEventBuf.h"
#include "SniperKernel/EvtSelector.h"

class UserBuffer : public PhyEventBuf
{
    public :

	UserBuffer(EvtSelector* selector);
	virtual ~UserBuffer();

	const std::string& name() { return m_selector->name(); }

	bool tryPushBack(PhyEvent* evt);
	void synchronize(PhyEventBuf* buf);

    private :

	EvtSelector*  m_selector;
};

#endif
