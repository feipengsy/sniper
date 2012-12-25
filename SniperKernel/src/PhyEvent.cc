#include "SniperKernel/PhyEvent.h"

PhyEvent::PhyEvent()
{
}

PhyEvent::~PhyEvent()
{
}

double PhyEvent::timeDiff(PhyEvent* other)
{
    return 0.0;
}

bool PhyEvent::earlier(PhyEvent* other)
{
    return timeDiff(other)<0;
}
