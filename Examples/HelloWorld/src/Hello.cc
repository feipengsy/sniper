#include "Hello.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/OptionParser.h"

DECLARE_ALGORITHM(HelloAlg);

HelloAlg::HelloAlg(const std::string& name)
    : AlgBase(name)
{
    m_count = 0;

    setOption("MyString", m_string);
                            
}

HelloAlg::~HelloAlg()
{

}

bool
HelloAlg::initialize()
{
    LogInfo << name() 
            << " initialized successfully"
            << std::endl;
    LogInfo << name()
            << " MyString: "
            << m_string
            << std::endl;
    return true;
}

bool
HelloAlg::execute()
{
    ++m_count;
    return true;
}

bool
HelloAlg::finalize()
{
    LogInfo << name() 
            << " finalized successfully"
            << std::endl;
    LogInfo << name()
            << " count: "
            << m_count
            << std::endl;

    return true;
}
