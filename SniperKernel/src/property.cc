#include <iostream>
#include <string>
#include <boost/noncopyable.hpp>
#include "SniperKernel/property.hh"

void
MyProperty::show() {
    bp::object s = m_value.attr("__str__")();
    std::string str = bp::extract<std::string>(s);
    std::cout << str << std::endl;
}

MyProperty*
getProperty(std::string objname,
            std::string key) {
    MyProperty* pb = PropertyManager::instance().get(objname, key);
    return pb;
}

bool
setProperty(std::string objname,
            std::string key,
            bp::object& value) {

    MyProperty* pb = PropertyManager::instance().get(objname, key);

    if (pb == NULL) {
        // can't find the property
        return false;
    }

    pb->modify(value);

}

