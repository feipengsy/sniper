#ifndef SNIPER_MGR_H
#define SNIPER_MGR_H

#include <string>

class SvcMgr;
class AlgMgr;
class ToolMgr;
class OptionParser;
class ICycler;

class SniperMgr
{
    public :

	SniperMgr(std::string optionfile);
	virtual ~SniperMgr();

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
	OptionParser*  m_parser;

	long           m_nEvt;
	long           m_evtMax;
	std::string    m_name;
};

#endif
