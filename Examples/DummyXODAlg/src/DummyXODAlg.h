#ifndef DUMMY_XOD_ALG_H
#define DUMMY_XOD_ALG_H

#include "SniperKernel/AlgBase.h"
#include "Event/RawEvent.h"
#include "TRandom.h"

class TTree;

class DummyXODAlg : public AlgBase
{
    public :

        DummyXODAlg(const std::string& name);
        virtual ~DummyXODAlg();

        virtual bool initialize();
        virtual bool execute();
        virtual bool finalize();

    private :

        int     m_iEvt;
        TTree*  m_tree1;
        JM::RawEvent* revent;
        TRandom* ran;
};

#endif
