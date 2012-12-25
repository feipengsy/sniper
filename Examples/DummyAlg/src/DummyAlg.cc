#include "DummyAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "RootWriter/RootWriter.h"
#include "TTree.h"

DECLARE_ALGORITHM(DummyAlg);

DummyAlg::DummyAlg(const std::string& name)
    : AlgBase(name)
{
    m_iEvt = 0;
}

DummyAlg::~DummyAlg()
{
}

bool DummyAlg::initialize()
{
    RootWriter* m_rw = dynamic_cast<RootWriter*>(service("RootWriter"));
    if ( m_rw == 0 ) {
	LogError << "Failed to get RootWriter instance!" << std::endl;
	return false;
    }

    m_tree1 = new TTree("tree1", "Dummy Test");
    m_tree1->Branch("iEvt",  &m_iEvt,  "iEvt/I");
    m_tree1->Branch("iLeaf", &m_iLeaf, "iLeaf/I");

    m_tree2 = new TTree("tree2", "Dummy Test");
    m_tree2->Branch("iEvt",  &m_iEvt,  "iEvt/I");
    m_tree2->Branch("fLeaf", &m_fLeaf, "fLeaf/F");

    m_tree3 = new TTree("tree3", "Dummy Test");
    m_tree3->Branch("iEvt",  &m_iEvt,  "iEvt/I");
    m_tree3->Branch("dLeaf", &m_dLeaf, "dLeaf/D");

    /* Make RootWriter be in charge of the Trees, so that we can set the
     * output file names in config_file as follows:
     *      RootWriter.Output = { "FILE1" : "output1.root",
     *                            "FILE2" : "output2.root" };
     *
     */
    m_rw->attach("FILE1", m_tree1);
    m_rw->attach("FILE1", m_tree3);

    m_rw->attach("FILE2", m_tree2);

    LogInfo << name() << " initialized successfully" << std::endl;

    return true;
}

bool DummyAlg::execute()
{
    ++m_iEvt;

    //Valid log level: LogDebug, LogInfo, LogWarn, LogError, LogFatal
    LogDebug << "Processing event " << m_iEvt << std::endl;

    //calculations
    m_iLeaf = m_iEvt % 100;
    m_fLeaf = (m_iEvt / 3.377) * 0.019;
    m_dLeaf = (m_iEvt / 3.377111) * 0.019222;

    //fill the trees
    m_tree1->Fill();
    m_tree2->Fill();
    m_tree3->Fill();

    return true;
}

bool DummyAlg::finalize()
{
    LogInfo << name() << " finalized successfully" << std::endl;

    return true;
}
