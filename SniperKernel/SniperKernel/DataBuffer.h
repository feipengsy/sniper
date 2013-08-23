#ifndef SNIPER_DATA_BUFFER_H
#define SNIPER_DATA_BUFFER_H

#include <deque>
#include <algorithm>

#include "SniperKernel/BaseType.h"

template<typename Data>
class DataBuffer
{
    public :

	typedef typename std::deque<Data*>::iterator Iterator;

	DataBuffer(BaseType bt=Sniper_CPP);
	virtual ~DataBuffer();

	inline Iterator begin();
	inline Iterator current();
	inline Iterator end();

	//Return the Iterator that corresponding to the data pointer
	inline Iterator find(const Data* data);
	//current()+pos, the pos can be positive or negtive
	inline Iterator seek(int pos);

	inline Data*    curEvt();
	inline Data*    seekEvt(int pos);

	inline int      totalSize();
	inline int      forwardSize();
	inline int      backwardSize();

	void            clear();
    BaseType get_class_type() {
        return m_class_type;
    }

    protected :

	unsigned int       m_iCur;
	std::deque<Data*>  m_dBuf;
    const BaseType m_class_type;


    private :
	// following interfaces are not supported
	DataBuffer(const DataBuffer&);
	DataBuffer& operator=(const DataBuffer&);
};

template<typename Data>
DataBuffer<Data>::DataBuffer(BaseType bt)
    : m_iCur(0xFFFFFFFF), m_class_type(bt)
{
}

template<typename Data>
DataBuffer<Data>::~DataBuffer()
{
    clear();
}

template<typename Data>
typename DataBuffer<Data>::Iterator DataBuffer<Data>::begin()
{
    return m_dBuf.begin();
}

template<typename Data>
typename DataBuffer<Data>::Iterator DataBuffer<Data>::current()
{
    return (m_dBuf.begin()+m_iCur);
}

template<typename Data>
typename DataBuffer<Data>::Iterator DataBuffer<Data>::end()
{
    return m_dBuf.end();
}

template<typename Data>
typename DataBuffer<Data>::Iterator DataBuffer<Data>::find(const Data* data)
{
    return std::find(m_dBuf.begin(), m_dBuf.end(), data);
}

template<typename Data>
typename DataBuffer<Data>::Iterator DataBuffer<Data>::seek(int pos)
{
    return (m_dBuf.begin()+(int(m_iCur)+pos));
}

template<typename Data>
Data* DataBuffer<Data>::curEvt()
{
    if ( !m_dBuf.empty() ) {
	return m_dBuf[m_iCur];
    }
    return (Data*)0;
}

template<typename Data>
Data* DataBuffer<Data>::seekEvt(int pos)
{
    return m_dBuf.at(m_iCur+pos);
}

template<typename Data>
int DataBuffer<Data>::totalSize()
{
    return m_dBuf.size();
}

template<typename Data>
int DataBuffer<Data>::forwardSize()
{
    return (m_dBuf.size()-m_iCur-1);
}

template<typename Data>
int DataBuffer<Data>::backwardSize()
{
    return m_iCur;
}

template<typename Data>
void DataBuffer<Data>::clear()
{
    for(typename std::deque<Data*>::iterator it=m_dBuf.begin(); it!=m_dBuf.end(); ++it) {
	delete (*it);
    }
    m_dBuf.clear();
}

#endif
