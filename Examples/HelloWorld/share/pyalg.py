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
    sm = libSniperMgr.SniperMgr("test.txt")
    #op = libSniperPython.OptionParser.OP("test.txt")
    mgr = libSniperPython.AlgMgr.instance()

    d1 = Derived("d1")
    d2 = Derived("d2")
    d3 = Derived("d3")

    sm.initialize()
    sm.run()
    sm.finalize()

