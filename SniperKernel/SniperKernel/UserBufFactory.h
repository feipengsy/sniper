#ifndef SNIPER_EVT_SEL_FACTORY_H
#define SNIPER_EVT_SEL_FACTORY_H

#include "SniperKernel/UserBuffer.h"
#include <string>

class UserBufFactory
{
    public :
	UserBufFactory(const std::string& name, UserBuffer* (*creator)(const std::string&));
};

#define DECLARE_BUFFER_WITH_SELECTOR(EvtSelClass) \
UserBuffer* _userBuf_with_##EvtSelClass##_creator_(const std::string& objName) {\
    return new UserBuffer(new EvtSelClass(objName)); } \
UserBufFactory  _reg_userBuf_with_##EvtSelClass##_creator(#EvtSelClass, &_userBuf_with_##EvtSelClass##_creator_)

#endif  //SNIPER_EVT_SEL_FACTORY_H
