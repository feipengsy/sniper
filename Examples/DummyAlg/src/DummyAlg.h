#ifndef DUMMY_ALG_H
#define DUMMY_ALG_H

#include "SniperKernel/AlgBase.h"

class TTree;

class DummyAlg : public AlgBase
{
    public :

	DummyAlg(const std::string& name);
	virtual ~DummyAlg();

	virtual bool initialize();
	virtual bool execute();
	virtual bool finalize();

    private :

	int     m_iEvt;
	int     m_iLeaf;
	float   m_fLeaf;
	double  m_dLeaf;

	TTree*       m_tree1;
	TTree*       m_tree2;
	TTree*       m_tree3;
};

#endif
