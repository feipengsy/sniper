#ifndef Hello_h
#define Hello_h

#include <string>

#include "SniperKernel/AlgBase.h"

class HelloAlg: public AlgBase
{
    public:
        HelloAlg(const std::string& name);

        ~HelloAlg();

        bool initialize();
        bool execute();
        bool finalize();

    private:
        int m_count;

        std::string m_string;
};

#endif
