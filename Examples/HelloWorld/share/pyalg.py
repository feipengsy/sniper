#!/usr/bin/env python
# -*- coding:utf-8 -*-
# author: lintao

import libSniperPython

class Derived(libSniperPython.AlgBase):

    def __init__(self, name, count=0):
        super(Derived, self).__init__(name)
        self.count = count

    def initialize(self):
        return True
    def execute(self):
        self.count += 1
        print "Hello", self.name()
        return True
    def finalize(self):
        print self.name(), self.count
        return True

if __name__ == "__main__":

    import libSniperMgr
    op = libSniperPython.OptionParser
    op.OP("test.txt")
    op.addOption("Hello1", "MyString", "GOD")
    op.addOption("Hello1", "MyVectorInt", "[1,2,3]")
    op.addOption("Hello2", "MyVectorInt", "[2,3]")
    op.addOption("Hello1", "MyStrInt", '{"str":1, "str2":2}')
    #op.addOption("Hello2", "MyStrInt", '{\'str\':2, "str3":3}')
    op.addOption("Hello2", "MyStrInt", '{2, 3}')
    
    d1 = Derived("d1")
    d2 = Derived("d2")
    d3 = Derived("d3")
    libSniperPython.AlgMgr.AddAlg(d1)
    libSniperPython.AlgMgr.AddAlg(d2)
    libSniperPython.AlgMgr.AddAlg(d3)

    sm = libSniperMgr.SniperMgr("")
    sm.initialize()
    sm.run()
    sm.finalize()

