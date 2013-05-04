
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
        : AlgBase(name) {
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
};

BOOST_PYTHON_MODULE(libSniperPython)
{
    class_<OptionParser, boost::noncopyable>("OptionParser", no_init)
        .def("OP", &OptionParser::instance, 
                return_value_policy<reference_existing_object>())
        .staticmethod("OP")
        .def("addOption", &OptionParser::addOption)
        .staticmethod("addOption")
        .def("setOption", &OptionParser::setOption<int>)
        .staticmethod("setOption")
    ;

    class_<AlgMgr, boost::noncopyable>("AlgMgr", no_init)
        .def("instance", &AlgMgr::instance,
                return_value_policy<reference_existing_object>())
        .staticmethod("instance")
        .def("execute", &AlgMgr::execute)

    ;

    class_<AlgBaseWrap, boost::noncopyable>("AlgBase", init<std::string>())
        .def("initialize", pure_virtual(&AlgBase::initialize))
        .def("execute", pure_virtual(&AlgBase::execute))
        .def("finalize", pure_virtual(&AlgBase::finalize))
        .def("name", &AlgBase::name, 
                return_value_policy<copy_const_reference>())
    ;
}
