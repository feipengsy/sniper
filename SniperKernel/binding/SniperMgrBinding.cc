// Python Binding
#include "SniperMgrV2.h"
#include "boost/python.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(libSniperMgr)
{
   class_<SniperMgrV2>("SniperMgr")
       .def("initialize", &SniperMgrV2::initialize)
       .def("finalize", &SniperMgrV2::finalize)
       .def("run", &SniperMgrV2::run)
       //.def("name", &SniperMgr::name)
    ;
}

