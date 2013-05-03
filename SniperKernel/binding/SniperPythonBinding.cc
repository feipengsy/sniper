
#include "boost/noncopyable.hpp"
#include "boost/python.hpp"
using namespace boost::python;

#include "SniperKernel/OptionParser.h"

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
}
