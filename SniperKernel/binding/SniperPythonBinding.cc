
#include "boost/noncopyable.hpp"
#include "boost/python.hpp"
using namespace boost::python;

#include "SniperKernel/OptionParser.h"

#include "SniperKernel/AlgMgr.h"
#include "SniperKernel/AlgBase.h"

// Alg Base Wrapper
struct AlgBaseWrap : AlgBase, wrapper<AlgBase>
{
    AlgBaseWrap(const std::string& name)
        : AlgBase(name, Sniper_PYTHON) {
        AlgMgr::AddAlg(this);
    }
    bool initialize() {
        return this->get_override("initialize")();
    }
    bool execute() {
        return this->get_override("execute")();
    }
    bool finalize() {
        return this->get_override("finalize")();
    }

    void setattr(const std::string& name, object o) {
        
    }
};

BOOST_PYTHON_MODULE(libSniperPython)
{

    enum_<BaseType>("BaseType")
        .value("Sniper_CPP", Sniper_CPP)
        .value("Sniper_PYTHON", Sniper_PYTHON)
    ;
    class_<OptionParser, boost::noncopyable>("OptionParser", no_init)
        .def("OP", &OptionParser::instance, 
                return_value_policy<reference_existing_object>())
        .staticmethod("OP")
        .def("addOption", &OptionParser::addOption)
        .staticmethod("addOption")
    ;

    class_<AlgMgr, boost::noncopyable>("AlgMgr", no_init)
        .def("instance", &AlgMgr::instance,
                return_value_policy<reference_existing_object>())
        .staticmethod("instance")
        .def("initialize", &AlgMgr::initialize)
        .def("execute", &AlgMgr::execute)
        .def("finalize", &AlgMgr::finalize)
        .def("get", 
                /*(AlgBase* (AlgMgr::*)(const std::string&, bool))*/&AlgMgr::get<AlgBase>,
                return_value_policy<reference_existing_object>())
        .staticmethod("get")

    ;

    class_<AlgBaseWrap, boost::noncopyable>("AlgBase", init<std::string>())
        .def("initialize", pure_virtual(&AlgBase::initialize))
        .def("execute", pure_virtual(&AlgBase::execute))
        .def("finalize", pure_virtual(&AlgBase::finalize))
        .def("name", &AlgBase::name, 
                return_value_policy<copy_const_reference>())
        .def("__setattr__", &AlgBaseWrap::setattr)
        .def("get_class_type", &AlgBase::get_class_type)
    ;
}
