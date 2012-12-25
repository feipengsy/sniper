#include "SniperKernel/UserBuffer.h"

UserBuffer::UserBuffer(EvtSelector* selector)
    : m_selector(selector)
{
}

UserBuffer::~UserBuffer()
{
    delete m_selector;
}

bool UserBuffer::tryPushBack(PhyEvent* evt)
{
    if ( m_selector->select(evt) ) {
	m_dBuf.push_back(dynamic_cast<PhyEvent*>(evt->GrabInstance()));
	return true;
    }
    return false;
}

void UserBuffer::synchronize(PhyEventBuf* buf)
{
    PhyEventBuf::Iterator it = buf->begin();
    while ( !m_dBuf.empty() && m_dBuf[0]->earlier(*it) ) {
	m_dBuf[0]->ReleaseInstance();
	m_dBuf[0] = 0;
	m_dBuf.pop_front();
    }
    unsigned int size = m_dBuf.size();
    m_iCur = size;
    if ( size > 0 ) {
	int curEntry = buf->curEvt()->entry();
	while ( --m_iCur != 0 && m_dBuf[m_iCur]->entry() != curEntry ) {
	    if ( m_dBuf[m_iCur]->earlier(buf->curEvt()) ) break;
	}
	if ( m_dBuf[m_iCur]->entry() != curEntry ) {
	    m_iCur = size;
	}
    }
}
