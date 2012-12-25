#include "SniperKernel/EvtObject.h"

EvtObject* EvtObject::GrabInstance()
{
    ++m_nHandler;
    return this;
}

void EvtObject::ReleaseInstance()
{
    if ( --m_nHandler <= 0 ) {
	delete this;
    }
}

EvtObject::EvtObject()
    : m_entry(-1),
      m_nHandler(0)
{
}

EvtObject::~EvtObject()
{
}
