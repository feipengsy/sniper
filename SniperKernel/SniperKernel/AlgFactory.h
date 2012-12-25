#ifndef SNIPER_ALG_FACTORY_H
#define SNIPER_ALG_FACTORY_H

#include <string>

class AlgBase;

class AlgFactory
{
    public :
	AlgFactory(const std::string& name, AlgBase* (*creator)(const std::string&));
};

#define DECLARE_ALGORITHM(AlgClass) \
AlgBase* _alg_##AlgClass##_creator_(const std::string& objName) { return new AlgClass(objName); } \
AlgFactory  _reg_alg_##AlgClass##_creator(#AlgClass, &_alg_##AlgClass##_creator_)

#endif //ALG_FACTORY_H
