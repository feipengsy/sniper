import xparser,os

class genLinkDef:
  
  def __init__( self, godRoot ):    
    self.godRoot = godRoot

  def getExternClasses( self, godClass ):
    classList = []
    for att in godClass['attribute']:
      if att['attrs'].has_key( 'extern' ):
        if att['attrs']['extern'] == 'TRUE':
          classList.append( att['attrs']['type'] )
    return classList

  def parseXld( self ):
    x = xparser.xparser()
    xld = x.parseSource( self.godRoot + 'xml_files/xld.xml' )
    return xld['attr']

  def findClass( self, classtype, xldList ):
    i = 1
    for attrDict in xldList:
      ct = ''
      if attrDict['attrs'].has_key( 'namespace' ):
        ct = attrDict['attrs']['namespace'] + '::' + attrDict['attrs']['type']
      else:
        ct = attrDict['attrs']['type']
      if ct == classtype:
        return { 'OK' : True, 'Value' : attrDict }
      if attrDict.has_key('attr'):
        return { 'OK' : False, 'Value' : attrDict['attr'] + xldList[i:] }
      i = i + 1
    return { 'OK' : False, 'Value' : '' }    

  def getClassTree( self, xld, classList ):
    classTree = {}
    for classtype in classList:
      result = { 'OK' : False, 'Value' : xld }
      while True:
        result = self.findClass( classtype, result['Value'] )
        if not result['Value']:
          print 'Cannot find extern class %s, please report to us' % classtype #FIXME think what should we do here
          classTree[classtype] = ''
          break
        if result['OK']:
          classTree[classtype] = result['Value']
          break
    return classTree

  def getLinkDefClasses( self, classTree ):
    finalList = []
    for k,v in classTree.items():
      if v:
        finalList.append( k )
        if v.has_key( 'attr' ):
          vList = v['attr']
          while True:
            ct = ''
            if vList[0]['attrs'].has_key( 'namespace' ):
              ct = vList[0]['attrs']['namespace'] + '::' + vList[0]['attrs']['type']
            else:
              ct = vList[0]['attrs']['type']
            finalList.append( ct )
            if vList[0].has_key( 'attr' ):
              vList = vList[0]['attr'] + vList[1:]
            else:
              vList = vList[1:]
              if not vList:
                break
    finalList = finalList[::-1]
    return finalList
        
  def doit( self, package, godClasses, ns, outputDir ):
    for godClass in godClasses:
      s = ''
      s = s + '#ifdef __CINT__\n\n\n'
      classList = self.getExternClasses( godClass )
      if classList:
        xldList = self.parseXld()
        classTree = self.getClassTree( xldList, classList )
        finalList = self.getLinkDefClasses( classTree )
        for ct in finalList:
          s = s + '#pragma link off all_function ' + ct + ';\n'
        for ct in finalList:
          s = s + '#pragma link C++ class ' + ct + ';\n'
      s = s + '#pragma link C++ class %s::%s;\n' % ( ns, godClass['attrs']['name'] )
      s = s + '\n\n#endif'
      fileName = '%sLinkDef.h' % godClass['attrs']['name']
      ldFile = open( outputDir+os.sep+fileName,'w' )
      ldFile.write( s )
      ldFile.close()
