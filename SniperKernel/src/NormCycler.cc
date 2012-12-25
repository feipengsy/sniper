#include "SniperKernel/NormCycler.h"
#include "SniperKernel/UserBufMgr.h"
#include "SniperKernel/SvcMgr.h"

NormCycler::NormCycler(const std::string& name)
    : SvcBase(name),
      m_cur(0),
      m_theBeyond(0),
      m_userBufMgr(0)
{
    if ( m_name == "Cycler" ) {
	m_userBufMgr = UserBufMgr::instance();
    }

    m_name = "NormCycler";  //to avoid naming confusion
}

NormCycler::~NormCycler()
{
    UserBufMgr::release();
}

bool NormCycler::initialize()
{
    setOption("TimeWindow", m_window);
    if ( m_window.size() != 2 ) {
	m_window.clear();
	m_window.push_back(-0.001);
	m_window.push_back(0.001);
    }
    LogDebug << "Window (" << m_window[0] << ", " << m_window[1] << ")" << std::endl;

    m_is = SvcMgr::get<ICycler>("InputSvc");
    if ( m_is == 0 ) {  // some tricks to make it work with [InputSvc = "NONE"]
	m_iCur = 0;
	m_window[0] = 0.0;
	m_window[1] = 0.0;
    }

    return true;
}

bool NormCycler::finalize()
{
    if ( m_theBeyond != 0 ) {
	m_theBeyond->ReleaseInstance();
	m_theBeyond = 0;
    }
    LogDebug << " @ finalize" << std::endl;
    return true;
}

EvtObject* NormCycler::next(int nth)
{
    if ( m_is != 0 ) m_iCur += nth;
    while ( m_dBuf.size() <= m_iCur ) {
	pushBack( theNext() );
	if ( m_theBeyond == 0 ) break;
    }

    if ( m_iCur < m_dBuf.size() ) {
	m_cur = m_dBuf[m_iCur];
	trimDated();
	fillFresh();
    }
    else {
	m_cur = 0;
    }

    if ( m_userBufMgr != 0 && m_cur != 0 ) {
	m_userBufMgr->synchronize(this);
    }

    return m_cur;
}

PhyEvent* NormCycler::expand()
{
    PhyEvent* _last = m_theBeyond;
    pushBack( theNext() );
    return _last;
}

PhyEventBuf* NormCycler::dataBuffer()
{
    return dynamic_cast<PhyEventBuf*>(this);
}

PhyEvent* NormCycler::theNext()
{
    if ( m_is != 0 ) {
	return (PhyEvent*)(m_is->next());
    }
    static PhyEvent* pevt = new PhyEvent;
    return pevt;
}

void NormCycler::pushBack(PhyEvent* evt)
{
    if ( m_theBeyond != 0 ) {
	m_dBuf.push_back(m_theBeyond);
	if ( m_userBufMgr != 0 ) {
	    m_userBufMgr->tryPushBack(m_theBeyond);
	}
    }

    m_theBeyond = (evt!=0) ? dynamic_cast<PhyEvent*>(evt->GrabInstance()) : 0;
}

void NormCycler::trimDated()
{
    //remove events that out-of-date
    PhyEvent* firstEvt = m_dBuf[0];
    while ( firstEvt != m_cur ) {
	if ( firstEvt->timeDiff(m_cur) > m_window[0] ) {
	    break;
	}
	m_dBuf[0] = 0;
	m_dBuf.pop_front();
	firstEvt->ReleaseInstance();  //delete firstEvt;
	firstEvt = m_dBuf[0];
	--m_iCur;
    }
}

void NormCycler::fillFresh()
{
    //fill fresh events to the buffer;
    while ( m_theBeyond != 0 && m_theBeyond->timeDiff(m_cur) < m_window[1] ) {
	pushBack( theNext() );
    }
}
