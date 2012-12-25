#ifndef PHYEVENT_H
#define PHYEVENT_H

#include "SniperKernel/EvtObject.h"

class PhyEvent : public EvtObject
{
    public :

	PhyEvent();

	virtual double timeDiff(PhyEvent* other);
	virtual bool   earlier(PhyEvent* other);

    private :

	virtual ~PhyEvent();

	PhyEvent(const PhyEvent&);  //Do not supported
	PhyEvent& operator=(const PhyEvent&);  //Do not supported
};

#endif
