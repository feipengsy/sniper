import xparser,os

class genLinkDef:
  
  def __init__( self, godRoot ):    
    self.godRoot = godRoot

  def getExternClasses( self, godClass ):
    classList = []
    for att in godClass['attribute']:
      if att['attrs']['extern'] == 'TRUE':
        classList.append( att['attrs']['type'] )
    return classList

  def genExternTemplates( self, godClass ):
    templateList = []
    templateDict = {}
    for att in godClass['template']:
      if att['attrs']['extern'] == 'TRUE':
        templateList.append( att['attrs']['type'] )
      attTypeList = att['typename']
      while True:
        if attTypeList[0].has_key( 'typename' ):
          if attTypeList[0]['attrs']['extern'] == 'TRUE':
            templateType = attTypeList[0]['attrs']['type']
            templateList.append( templateType )
            if not templateDict.has_key( templateType ):
              templateDict[templateType] = self.findTempParameter( attTypeList[0]['typename'] )
          attTypeList = attTypeList[0]['typename'] + attTypeList[1:]
        else:
          if attTypeList[0]['attrs']['extern'] == 'TRUE':
            templateType = attTypeList[0]['attrs']['type']
            templateList.append( templateType )
            templateDict[templateType] = ''
          attTypeList = attTypeList[1:]
        if not attTypeList:               
          break
    return ( templateList, templateDict )

  def findTempParameter( self, attTypeList ):
    tempParameter = '<'
    depth = 0
    depthLength = { 0 : len( attTypeList ) }
    while True:
      if attTypeList[0].has_key( 'typename' ):
        tempParameter = tempParameter + attTypeList[0]['attrs']['type'] + '<'
        depthLength[depth] = depthLength[depth] - 1
        depth = depth + 1
        depthLength[depth] = len( attTypeList[0]['typename'] )
        attTypeList = attTypeList[0]['typename'] + attTypeList[1:]
      else:
        tempParameter = tempParameter + attTypeList[0]['attrs']['type'] + ','
        depthLength[depth] = depthLength[depth] - 1
        attTypeList = attTypeList[1:]
      if depthLength[depth] == 0:
        if tempParameter.endswith( ',' ):
          tempParameter = tempParameter[:-1]
        tempParameter = tempParameter + '>,'
        depth = depth - 1
      if not attTypeList:
        if tempParameter.endswith( ',' ):
          tempParameter = tempParameter[:-1]
        while depth >= 0:
          tempParameter = tempParameter + '>'
          depth = depth - 1                
        break
    return tempParameter

  def parseXld( self ):
    x = xparser.xparser()
    xld = x.parseSource( self.godRoot + 'xml_files/xld.xml' )
    return xld['attr']

  def findClass( self, classname, xldList ):
    i = 1
    for attrDict in xldList:
      ct = ''
      if attrDict['attrs'].has_key( 'ns' ):
        ct = attrDict['attrs']['ns'] + '::' + attrDict['attrs']['name']
      else:
        ct = attrDict['attrs']['name']
      if ct == classname:
        return { 'OK' : True, 'Value' : attrDict }
      if attrDict.has_key('attr'):
        return { 'OK' : False, 'Value' : attrDict['attr'] + xldList[i:] }
      i = i + 1
    return { 'OK' : False, 'Value' : '' }

  def getClassTree( self, xld, classList ):
    classTree = {}
    for classname in classList:
      result = { 'OK' : False, 'Value' : xld }
      while True:
        result = self.findClass( classname, result['Value'] )
        if not result['Value']:
          print 'Cannot find extern class %s, please report to us' % classname #FIXME think what should we do here
          classTree[classname] = ''
          break
        if result['OK']:
          classTree[classname] = result['Value']
          break
    return classTree

  def getLinkDefClasses( self, classTree ):
    finalList = []
    for k,v in classTree.items():
      if v:
        finalList.append( k + '#class' )
        if v.has_key( 'attr' ):
          vList = v['attr']
          while True:
            ct = ''
            if vList[0]['attrs'].has_key( 'ns' ):
              ct = vList[0]['attrs']['ns'] + '::' + vList[0]['attrs']['name'] + '#' + vList[0]['attrs']['type']
            else:
              ct = vList[0]['attrs']['name'] + '#' + vList[0]['attrs']['type']
            finalList.append( ct )
            if vList[0].has_key( 'attr' ):
              vList = vList[0]['attr'] + vList[1:]
            else:
              vList = vList[1:]
              if not vList:
                break
    finalList = finalList[::-1]
    finalList1 = []
    for ele in finalList:
      if ele not in finalList1:
        finalList1.append( ele )
    return finalList1
        
  def doit( self, package, godClasses, ns, outputDir ):
    for godClass in godClasses:
      s = ''
      s = s + '#ifdef __CINT__\n\n\n'
      classList = self.getExternClasses( godClass )
      if godClass.has_key( 'template' ):
        tempTuple = self.genExternTemplates( godClass )
        allList = tempTuple[0] + classList
      else:
        tempTuple = ([],[])
        allList = classList
      if allList:
        xldList = self.parseXld()
        classTree = self.getClassTree( xldList, allList )
        finalList = self.getLinkDefClasses( classTree )       
        for ct in finalList:
          if ct.endswith( '#class' ):
            if ct[:-6] in tempTuple[0]:
              s = s + '#pragma link off all_function ' + ct[:-6] + tempTuple[1][ct[:-6]] + ';\n'
            else:
              s = s + '#pragma link off all_function ' + ct[:-6] + ';\n'
        for ct in finalList:
          ctList = ct.split('#')
          if ctList[1] == 'class':
            if ctList[0] in tempTuple[0]:
              s = s + '#pragma link C++ class %s%s+;\n' %  ( ctList[0], tempTuple[1][ctList[0]] )
            else:
              s = s + '#pragma link C++ class %s+;\n' %  ctList[0]
          else:
            s = s + '#pragma link C++ %s %s;\n' %  ( ctList[1], ctList[0] )
      s = s + '#pragma link C++ class %s::%s+;\n' % ( ns, godClass['attrs']['name'] )
      s = s + '\n\n#endif'
      fileName = '%sLinkDef.h' % godClass['attrs']['name']
      ldFile = open( outputDir+os.sep+fileName,'w' )
      ldFile.write( s )
      ldFile.close()

