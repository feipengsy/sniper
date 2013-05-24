#!/usr/bin/env python
# -*- coding:utf-8 -*-
# author: lintao

import libSniperPython

if __name__ == "__main__":

    import libSniperMgr
    op = libSniperPython.OptionParser
    op.OP("none.txt")

    # TODO:
    # We can use repr to convert python object to parser.

    op.addOption("Sniper", "LogLevel", "3")
    op.addOption("Sniper", "Cycler", "'NormCycler'")
    op.addOption("Sniper", "InputSvc", "'NONE'")

    import libSniperPython
    import libHelloWorldPy

    x = libHelloWorldPy.HelloAlg("x")
    x.x = 1
    x.MyString = 'GOD'
    x.MyVectorInt = range(4)
    x.MyStrInt = {"str1":1, "str2":2}
    print x.name()
    x.initialize()
    x.execute()
    x.finalize()
