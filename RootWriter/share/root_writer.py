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
    libSniperPython.setProperty("Sniper", "InputSvc", "NONE")
    libSniperPython.setProperty("Sniper", "Dlls", ["RootWriter"])
    mgr.configure()

    rw = libSniperPython.SvcMgr.get("RootWriter/rw", True)
    rw.setProp("Out", {"FILE1":"hello.root"})
    print rw
