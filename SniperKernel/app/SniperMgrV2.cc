#include "SniperMgrV2.h"
#include "SniperKernel/SvcMgr.h"
#include "SniperKernel/AlgMgr.h"
#include "SniperKernel/ToolMgr.h"
#include "SniperKernel/property.hh"
#include "SniperKernel/GlobalVar.h"
#include "SniperKernel/ICycler.h"
#include <dlfcn.h>

#include "boost/python.hpp"

namespace bp = boost::python;

SniperMgrV2::SniperMgrV2()
    : m_nEvt(0),
      m_evtMax(-1),
      m_name("Sniper")
{
    std::cout << "***********************    _            _       _    _       _   _\n"
              << "** Welcome to SNiPER ** :  Software for Non-collider Physics ExpeRiments\n"
              << "***********************"
              << std::endl;

    // Declare Property
    declareProperty("GlobalVar", "NumADs",   GlobalVar::NumADs);
    declareProperty(name(),      "LogLevel", SniperLog::LogLevel);
    declareProperty(name(),      "EvtMax",   m_evtMax);

    // Input Svc
    /// dynamically load the input service
    declareProperty(name(),      "InputSvc", isvc);

    // main Cycler
    /// dynamically set the main Cycler
    declareProperty(name(),      "Cycler",   cycler);

    ///// always load the TOutputSvc services automatically
    //OptionParser::addOption("SvcMgr",  "Contents",  "{\"TOutputSvc\"}");

    /// loading dynamic libraries
    declareProperty(name(),      "Dlls",     dlls);

    /// instance of services and algorithms
    m_svcs   = SvcMgr::instance();
    m_algs   = AlgMgr::instance();
    m_tools  = ToolMgr::instance();
}

SniperMgrV2::~SniperMgrV2()
{
    delete m_tools;
    delete m_algs;
    delete m_svcs;
    LogInfo << "Terminated" << std::endl;
}

bool SniperMgrV2::configure()
{
    // Input Svc
    if ( isvc.empty() ) {
        throw SniperException(name()+".InputSvc is not set properly!");
    }
    // TODO
    // using boost python list
    // ["isvc/InputSvc"]
    if ( isvc != "NONE" ) {
        loadDll(isvc);
        bp::list ct(std::string(isvc+"/InputSvc"));
        setProperty("SvcMgr", "Contents", ct);
    }
    LogInfo << "Select InputSvc : " << isvc << std::endl;

    // Cycler
    if ( cycler.empty() ) cycler = "NormCycler";
    if ( cycler != "NormCycler" ) {
        //FIXME: always load the NormCycler or not ?
        loadDll(cycler);
    }
    bp::list ct = (bp::list)getProperty("SvcMgr", "Contents")->value();
    ct.append(cycler+"/Cycler");
    setProperty("SvcMgr", "Contents", ct);
    LogInfo << "Select Cycler   : " << cycler << std::endl;

    // Loading Libraries
    for(std::vector<std::string>::iterator it=dlls.begin(); it!=dlls.end(); ++it) {
        loadDll(*it);
    }

    return true;
}

bool SniperMgrV2::initialize()
{
    m_cycler = SvcMgr::get<ICycler>("Cycler");

    LogDebug << "initializing ..." << std::endl;
    // TODO
    // validate the property
    if ( m_svcs->initialize() && m_algs->initialize() /*&& m_parser->validate()*/ ) {
        LogInfo << "Successfully initialized" << std::endl;
        return true;
    }
    return false;
}

bool SniperMgrV2::finalize()
{
    LogDebug << "finalizing ..." << std::endl;
    if ( m_algs->finalize() && m_svcs->finalize() ) {
        LogInfo << "Successfully finalized" << std::endl;
    }
    return false;
}

void SniperMgrV2::run()
{

    while ( m_evtMax < 0 || m_nEvt < m_evtMax ) {
        if ( m_cycler->next() ) {
            if ( m_algs->execute() ) {
                ++m_nEvt;
                continue;
            }
        }
        break;
    }

    LogInfo << "Total processed events " << m_nEvt << std::endl;
}

void SniperMgrV2::loadDll(const std::string& dll)
{
    std::string dllname = std::string("lib") + dll + ".so";
    void *dl_handler = dlopen(dllname.c_str(), RTLD_LAZY|RTLD_GLOBAL);
    if ( !dl_handler ) {
        LogFatal << dlerror() << std::endl;
        std::string msg = std::string("Can't load DLL ") + dllname;
        throw SniperException(msg);
    }
}

