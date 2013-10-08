#!/usr/bin/env python
# -*- coding:utf-8 -*-
# author: lintao

import libSniperMgr
import libSniperPython as sp

mgr = libSniperMgr.SniperMgr()
sp.setProperty("Sniper", "EvtMax", 5)
sp.setProperty("Sniper", "InputSvc", "NONE")
sp.setProperty("Sniper", "LogLevel", 2)
sp.setProperty("Sniper", "Dlls", ["DummyAlg", "RootWriter"])

sp.setProperty("AlgMgr", "Contents", ["DummyAlg"])
sp.setProperty("SvcMgr", "Contents", ["RootWriter"])

mgr.configure()

dalg = sp.AlgMgr.get("DummyAlg/dalg", True)
rw = sp.SvcMgr.get("RootWriter/rw", True)

# now to configure the algs and svcs.
d = {"FILE1": "output1.root", "FILE2": "output2.root"}
rw.setProp("Output", d)

# begin to run
mgr.initialize()
mgr.run()
mgr.finalize()
