#include "SniperMgr.h"
#include "SniperKernel/SvcMgr.h"
#include "SniperKernel/AlgMgr.h"
#include "SniperKernel/ToolMgr.h"
#include "SniperKernel/OptionParser.h"
#include "SniperKernel/GlobalVar.h"
#include "SniperKernel/ICycler.h"
#include <dlfcn.h>

SniperMgr::SniperMgr(std::string optionfile)
    : m_nEvt(0),
      m_evtMax(-1),
      m_name("Sniper")
{
    std::cout << "***********************    _            _       _    _       _   _\n"
	      << "** Welcome to SNiPER ** :  Software for Non-collider Physics ExpeRiments\n"
	      << "***********************"
	      << std::endl;
    LogInfo << optionfile << std::endl;
    m_parser = OptionParser::instance(const_cast<char*>(optionfile.c_str()));

    /// general variables
    OptionParser::setOption("GlobalVar", "NumADs",   GlobalVar::NumADs);
    OptionParser::setOption(name(),      "LogLevel", SniperLog::LogLevel);
    OptionParser::setOption(name(),      "EvtMax",   m_evtMax);

    /// dynamically load the input service
    std::string isvc;
    OptionParser::setOption(name(),      "InputSvc", isvc);
    if ( isvc.empty() ) {
	throw SniperException(name()+".InputSvc is not set properly!");
    }
    if ( isvc != "NONE" ) {
	loadDll(isvc);
	OptionParser::addOption("SvcMgr", "Contents", std::string("{\"")+isvc+"/InputSvc\"}");
    }
    LogInfo << "Select InputSvc : " << isvc << std::endl;

    /// dynamically set the main Cycler
    std::string cycler;
    OptionParser::setOption(name(),      "Cycler",   cycler);
    if ( cycler.empty() ) cycler = "NormCycler";
    if ( cycler != "NormCycler" ) {
	//FIXME: always load the NormCycler or not ?
	//OptionParser::addOption("SvcMgr",  "Contents",  "{\"NormCycler\"}");
	loadDll(cycler);
    }
    OptionParser::addOption("SvcMgr", "Contents", std::string("{\"")+cycler+"/Cycler\"}");
    LogInfo << "Select Cycler   : " << cycler << std::endl;

    ///// always load the TOutputSvc services automatically
    //OptionParser::addOption("SvcMgr",  "Contents",  "{\"TOutputSvc\"}");

    /// loading dynamic libraries
    std::vector<std::string> dlls;
    OptionParser::setOption(name(),      "Dlls",     dlls);
    for(std::vector<std::string>::iterator it=dlls.begin(); it!=dlls.end(); ++it) {
	loadDll(*it);
    }

    /// instance of services and algorithms
    m_svcs   = SvcMgr::instance();
    m_algs   = AlgMgr::instance();
    m_tools  = ToolMgr::instance();
}

SniperMgr::~SniperMgr()
{
    delete m_parser;
    delete m_tools;
    delete m_algs;
    delete m_svcs;
    LogInfo << "Terminated" << std::endl;
}

bool SniperMgr::initialize()
{
    m_cycler = SvcMgr::get<ICycler>("Cycler");

    LogDebug << "initializing ..." << std::endl;
    if ( m_svcs->initialize() && m_algs->initialize() && m_parser->validate() ) {
	LogInfo << "Successfully initialized" << std::endl;
	return true;
    }
    return false;
}

bool SniperMgr::finalize()
{
    LogDebug << "finalizing ..." << std::endl;
    if ( m_algs->finalize() && m_svcs->finalize() ) {
	LogInfo << "Successfully finalized" << std::endl;
    }
    return false;
}

void SniperMgr::run()
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

void SniperMgr::loadDll(const std::string& dll)
{
    std::string dllname = std::string("lib") + dll + ".so";
    void *dl_handler = dlopen(dllname.c_str(), RTLD_LAZY|RTLD_GLOBAL);
    if ( !dl_handler ) {
	LogFatal << dlerror() << std::endl;
	std::string msg = std::string("Can't load DLL ") + dllname;
	throw SniperException(msg);
    }
}

