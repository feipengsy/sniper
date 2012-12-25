#ifndef SNIPER_PHY_EVENT_BUF_H
#define SNIPER_PHY_EVENT_BUF_H

#include "SniperKernel/DataBuffer.h"
#include "SniperKernel/PhyEvent.h"

typedef DataBuffer<PhyEvent> PhyEventBuf;

template<> DataBuffer<PhyEvent>::~DataBuffer();
template<> void DataBuffer<PhyEvent>::clear();

#endif
