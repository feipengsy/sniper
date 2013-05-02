// Python Binding
#include "SniperMgr.h"
#include "boost/python.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(libSniperMgr)
{
   class_<SniperMgr>("SniperMgr", init<std::string>())
       .def("initialize", &SniperMgr::initialize)
       .def("finalize", &SniperMgr::finalize)
       .def("run", &SniperMgr::run)
       //.def("name", &SniperMgr::name)
    ;
}

