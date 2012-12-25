#include "SniperKernel/PhyEventBuf.h"

template<> DataBuffer<PhyEvent>::~DataBuffer()
{
    this->clear();
}

template<> void DataBuffer<PhyEvent>::clear()
{
    for(std::deque<PhyEvent*>::iterator it=m_dBuf.begin(); it!=m_dBuf.end(); ++it) {
	(*it)->ReleaseInstance();
    }
    m_dBuf.clear();
}
