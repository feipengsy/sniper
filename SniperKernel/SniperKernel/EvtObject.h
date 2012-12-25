#ifndef SNIPER_EVT_OBJECT_H
#define SNIPER_EVT_OBJECT_H

class EvtObject
{
    public :

	EvtObject* GrabInstance();
	void       ReleaseInstance();

	EvtObject();
	virtual ~EvtObject();

	int entry() { return m_entry; }

    private :

	int m_entry;

	// for automatic memory management
	int     m_nHandler;
};

#endif
