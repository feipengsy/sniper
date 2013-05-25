
#include "boost/noncopyable.hpp"
#include "boost/make_shared.hpp"
#include "boost/python.hpp"
using namespace boost::python;

#include "Hello.h"

BOOST_PYTHON_MODULE(libHelloWorldPy)
{
    class_< HelloAlg, boost::shared_ptr<HelloAlg>, bases<AlgBase>, boost::noncopyable> 
        ("HelloAlg", init<std::string>()) //[return_value_policy<reference_existing_object>()]
        ;
}
