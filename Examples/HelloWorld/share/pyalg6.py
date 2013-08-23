#!/usr/bin/env python
# -*- coding:utf-8 -*-
# author: lintao

# using the new Mgr.

import sys

# From PyCintex in ROOT
dlflags = sys.getdlopenflags()
sys.setdlopenflags( 0x100 | 0x2 )    # RTLD_GLOBAL | RTLD_NOW

import libSniperMgr
import libSniperPython


if __name__ == "__main__":

    mgr = libSniperMgr.SniperMgr()
    libSniperPython.setProperty("Sniper", "EvtMax", 5)
    libSniperPython.setProperty("Sniper", "InputSvc", "NONE")
    libSniperPython.setProperty("Sniper", "LogLevel", 2)
    libSniperPython.setProperty("Sniper", "Dlls", ["HelloWorld"])


    libSniperPython.setProperty("AlgMgr", "Contents", ["HelloAlg/x"])

    mgr.configure()
    # TODO

    libSniperPython.setProperty("x", "MyString", "GOD")
    libSniperPython.setProperty("x", "MyVectorInt", range(4))
    libSniperPython.setProperty("x", "MyStrInt", {"str1":1, "str2":2})

    libSniperPython.getProperty("x", "MyString").value()

    mgr.initialize()
    mgr.run()
    mgr.finalize()
