#include "SniperKernel/SniperException.h"

SniperException::SniperException(const std::string& msg)
    : m_msg(msg)
{
}

SniperException::~SniperException() throw()
{
}

const char* SniperException::what() const throw()
{
    return m_msg.c_str();
}
