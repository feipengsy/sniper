#include "Hello.h"
#include "SniperKernel/AlgFactory.h"

DECLARE_ALGORITHM(HelloAlg);

HelloAlg::HelloAlg(const std::string& name)
    : AlgBase(name)
{
    m_count = 0;
    // Using declare property
    declProp("MyString", m_string);
    declProp("MyVectorInt", m_vector_int);
    declProp("MyStrInt", m_str_int);

}

HelloAlg::~HelloAlg()
{

}

bool
HelloAlg::initialize()
{
    //OptionParser::instance()->addOption(name, "MyString", "LINTAO");
    //setOption("MyString", m_string);
                            
    LogInfo << name() 
            << " initialized successfully"
            << std::endl;
    LogInfo << name()
            << " MyString: "
            << m_string
            << std::endl;
    LogInfo << name()
            << " MyVectorInt("<< m_vector_int.size() << "): " << std::endl; 
    for (std::vector<int>::iterator i=m_vector_int.begin();
            i!=m_vector_int.end(); ++i) {
        LogInfo << (*i) << std::endl;
    }
    LogInfo << std::endl;
    LogInfo << name()
            << " MyStrInt("<< m_str_int.size() << "): " << std::endl; 
    for (std::map<std::string, int>::iterator i=m_str_int.begin();
            i!=m_str_int.end(); ++i) {
        LogInfo << i->first << ":"
                << i->second
                << std::endl;
    }
    return true;
}

bool
HelloAlg::execute()
{
    ++m_count;
    LogInfo << name() 
            << " count: "
            << m_count
            << std::endl;
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
