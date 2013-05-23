#!/usr/bin/env python
# -*- coding:utf-8 -*-
# author: lintao

import libSniperPython

if __name__ == "__main__":

    import libSniperMgr
    op = libSniperPython.OptionParser
    op.OP("none.txt")

    op.addOption("Sniper", "LogLevel", "3")
    op.addOption("Sniper", "Cycler", "'NormCycler'")
    op.addOption("Sniper", "InputSvc", "'NONE'")

    op.addOption("Sniper", "Dlls", '{"HelloWorld"}') 

    op.addOption("AlgMgr", "Contents", 
                    '{"HelloAlg/Hello1"}')

    op.addOption("Sniper", "EvtMax", "10")

    op.addOption("Hello1", "MyString", "'GOD'")
    op.addOption("Hello1", "MyVectorInt", "[1,2,3]")
    op.addOption("Hello1", "MyStrInt", '{"str":1, "str2":2}')

    sm = libSniperMgr.SniperMgr("")

    sm.initialize()
    print "RUN BEGIN"
    sm.run()
    print "RUN END"
    sm.finalize()

