#include "DummyXODAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "RootWriter/RootWriter.h"
#include "TTree.h"

DECLARE_ALGORITHM(DummyXODAlg);

DummyXODAlg::DummyXODAlg(const std::string& name)
    : AlgBase(name)
{
    m_iEvt = 0;
    revent = new JM::RawEvent;
    ran = new TRandom;
}

DummyXODAlg::~DummyXODAlg()
{
}

bool DummyXODAlg::initialize()
{
    RootWriter* m_rw = dynamic_cast<RootWriter*>(service("RootWriter"));
    if ( m_rw == 0 ) {
        LogError << "Failed to get RootWriter instance!" << std::endl;
        return false;
    }
  
    m_tree1 = new TTree("tree1", "Dummy XOD Test");
    m_tree1->Branch("event_branch", "JM::RawEvent", &revent);
    m_rw->attach("FILE1", m_tree1);
    
    LogInfo << name() << " initialized successfully" << std::endl;

    return true;

}
bool DummyXODAlg::execute()
{
  ++m_iEvt;
 
  revent->setTotalMom(6.0); 
  m_tree1->Fill();
  LogDebug << "Processing event " << m_iEvt <<std::endl;

  return true;
}

bool DummyXODAlg::finalize()
{
    LogInfo << name() << " finalized successfully" << std::endl;

    return true;
}
