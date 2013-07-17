#!/usr/bin/env python
# -*- coding:utf-8 -*-
# author: lintao

# using the new Mgr.

import libSniperPython

if __name__ == "__main__":

    import libSniperMgr
    mgr = libSniperMgr.SniperMgr()
    libSniperPython.setProperty("Sniper", "EvtMax", 5)
    libSniperPython.setProperty("Sniper", "InputSvc", "NONE")

    mgr.configure()
    # TODO
    # How To add the Alg into the MGR?
    #op.addOption("Sniper")

    import libSniperPython
    import libHelloWorldPy

    x = libHelloWorldPy.HelloAlg("x")
    #x.MyString = 'GOD'
    libSniperPython.setProperty("x", "MyString", "GOD")
    libSniperPython.setProperty("x", "MyVectorInt", range(4))
    libSniperPython.setProperty("x", "MyStrInt", {"str1":1, "str2":2})
    #x.MyVectorInt = range(4)
    #x.MyStrInt = {"str1":1, "str2":2}
    print x.name()
    #x.initialize()
    #x.execute()
    #x.finalize()

    libSniperPython.AlgMgr.AddAlg(x)

    mgr.initialize()
    mgr.run()
    mgr.finalize()
