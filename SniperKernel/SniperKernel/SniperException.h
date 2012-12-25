#ifndef SNIPER_EXCEPTION_H
#define SNIPER_EXCEPTION_H

#include <exception>
#include <string>

class SniperException : public std::exception
{
    public :

	SniperException(const std::string& msg);
	virtual ~SniperException() throw();

	const char* what() const throw();

    private :

	std::string m_msg;
};

#endif
