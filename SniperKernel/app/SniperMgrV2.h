#ifndef SNIPER_MGR_V2_H
#define SNIPER_MGR_V2_H

#include <string>
#include <vector>

class SvcMgr;
class AlgMgr;
class ToolMgr;
class ICycler;

class SniperMgrV2
{
public :

    SniperMgrV2();
    virtual ~SniperMgrV2();

    bool configure();

    bool initialize();
    bool finalize();

    void run();

    const std::string& name() { return m_name; }


private :

    void   loadDll(const std::string& dll);

    ICycler*       m_cycler;
    SvcMgr*        m_svcs;
    AlgMgr*        m_algs;
    ToolMgr*       m_tools;

    long           m_nEvt;
    long           m_evtMax;
    std::string    m_name;

    std::string    isvc;
    std::string    cycler;
    std::vector<std::string> dlls;
};

#endif
