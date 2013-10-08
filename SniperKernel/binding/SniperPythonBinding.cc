#include <iostream>
#include <string>
#include "boost/noncopyable.hpp"
#include "boost/make_shared.hpp"
#include "boost/python.hpp"
namespace bp = boost::python;
using namespace boost::python;

#include "SniperKernel/AlgMgr.h"
#include "SniperKernel/AlgBase.h"

// Alg Base Wrapper
struct AlgBaseWrap : AlgBase, wrapper<AlgBase>
{
    AlgBaseWrap(const std::string& name)
        : AlgBase(name, Sniper_PYTHON) {
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

    static void SetAttr(object obj, const std::string& name, object o) {
        // If the type of obj is defined in python
        // we just keep the origin method.
        // else, add these key-value to catalogue.
        BaseType bt = extract<BaseType>(obj.attr("get_class_type")());
        if (bt == Sniper_PYTHON) {
            obj.attr("__dict__")[name] = o;
            return;
        } 
        std::string objname = extract<std::string>(obj.attr("name")());
        std::string value = extract<std::string>(o.attr("__repr__")());
        //OptionParser::addOption( objname, // object name
        //                         name, // option key
        //                         value // option value
        //                        );
    }
};

// Wrapper for PYTHON
#include "SniperKernel/property.hh"

struct BasePropertyBase: public MyProperty, bp::wrapper<MyProperty>
{
    BasePropertyBase(std::string key, bp::object value)
        : MyProperty(key, value)
    {}

    void modify(bp::object& new_value) {
        this->get_override("modify")(new_value);
    }
};

// Wrapper for Svc
#include "SniperKernel/SvcMgr.h"
#include "SniperKernel/SvcBase.h"
struct SvcBaseWrap : SvcBase, wrapper<SvcBase>
{
    SvcBaseWrap(const std::string& name)
        : SvcBase(name, Sniper_PYTHON) {
    }
    bool initialize() {
        return this->get_override("initialize")();
    }
    bool finalize() {
        return this->get_override("finalize")();
    }
};

BOOST_PYTHON_MODULE(libSniperPython)
{

    enum_<BaseType>("BaseType")
        .value("Sniper_CPP", Sniper_CPP)
        .value("Sniper_PYTHON", Sniper_PYTHON)
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
        .def("AddAlg", &AlgMgr::AddAlg)
        .staticmethod("AddAlg")

    ;

    class_<AlgBaseWrap, boost::shared_ptr<AlgBaseWrap>, boost::noncopyable>("AlgBase", init<std::string>())
        .def("initialize", pure_virtual(&AlgBase::initialize))
        .def("execute", pure_virtual(&AlgBase::execute))
        .def("finalize", pure_virtual(&AlgBase::finalize))
        .def("name", &AlgBase::name, 
                return_value_policy<copy_const_reference>())
        .def("__setattr__", &AlgBaseWrap::SetAttr)
        .def("get_class_type", &AlgBase::get_class_type)
        .def("setProp", &AlgBase::setProp)
    ;

    class_<SvcMgr, boost::noncopyable>("SvcMgr", no_init)
        .def("instance", &SvcMgr::instance,
                return_value_policy<reference_existing_object>())
        .staticmethod("instance")
        .def("get",
                &SvcMgr::get<SvcBase>,
                return_value_policy<reference_existing_object>())
        .staticmethod("get")
    ;

    class_<SvcBaseWrap, boost::shared_ptr<SvcBaseWrap>, boost::noncopyable>("SvcBase", init<std::string>())
        .def("initialize", pure_virtual(&SvcBase::initialize))
        .def("finalize", pure_virtual(&SvcBase::finalize))
        .def("name", &SvcBase::name, 
                return_value_policy<copy_const_reference>())
        .def("setProp", &SvcBase::setProp)
    ;

    bp::class_<BasePropertyBase, boost::noncopyable>("MyProperty",
            bp::init<std::string, bp::object>())
        .def("modify", bp::pure_virtual(&MyProperty::modify))
        .def("show", &MyProperty::show)
        .def("key", &MyProperty::key,
            bp::return_value_policy<bp::copy_const_reference>())
        .def("value", &MyProperty::value,
            bp::return_value_policy<bp::copy_non_const_reference>())
    ;
    bp::def("getProperty", &getProperty,
            bp::return_value_policy<bp::reference_existing_object>());
    bp::def("setProperty", &setProperty);
}
