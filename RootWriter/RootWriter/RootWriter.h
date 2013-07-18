#ifndef SNIPER_ROOT_WRITER_SVC_H
#define SNIPER_ROOT_WRITER_SVC_H

#include "SniperKernel/SvcBase.h"
#include <map>

/**************************************************************************
 * Examples
 * It's similar to TTree and TNtuple :
 *     RootWriter* svc = SvcMgr::get<RootWriter>("RootWriter");
 *     TTree* tree = svc->bookTree("Fkey/dir/tree", "title");
 *
 * or to Histograms:
 *     RootWriter* svc = SvcMgr::get<RootWriter>("RootWriter");
 *     TH1D* hist = new TH1D(...)
 *     svc->attach("Fkey/dir", hist);
 *
 * the dir(TDirectory in TFile) is optional (0 - several levels)
 *************************************************************************/

class TFile;
class TTree;
class TNtuple;
class TDirectory;

class RootWriter : public SvcBase
{
    public :

	RootWriter(const std::string& name);
	virtual ~RootWriter();

	bool initialize();
	bool finalize();

	TTree* bookTree(const std::string& fullPath, const std::string& title);
	TNtuple* bookNtuple(const std::string& fullPath, const std::string& title, const std::string& leafs);

	template<class Type>
	bool attach(const std::string& fullDirs, Type* obj);  //fullDirs: fKey/Dirs

    private :

	//fKey: the tag of a file
	bool addFile(const std::string& fKey, const std::string& fname);

	//get the TDirectory that associated to fullDirs
	TDirectory* getDir(const std::string& fullDirs);

	//fKey -> TFile
	std::map<std::string, TFile*> m_key2file;
        std::map<std::string, std::string> fmap;
};

template<class Type>
bool RootWriter::attach(const std::string& fullDirs, Type* obj)
{
    TDirectory* pDir = getDir(fullDirs);
    obj->SetDirectory(pDir);

    return (pDir!=0);
}

#endif
