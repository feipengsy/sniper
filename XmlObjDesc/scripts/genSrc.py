import sys,os


def genSrc( fullName ):
  fileName = fullName.split('/')[-1]
  srcFile = open( fullName + '.cc', 'w' )
  src = '#include "Event/%s"\n' % (fileName + '.h')
  src += 'ClassImp(JM::%s);' % fileName
  srcFile.write( src )
  srcFile.close()

def check( cwd ):
  srcSufList = [ 'cc', 'CC', 'cpp', 'CPP', 'cxx', 'CXX', 'c++', 'C++', 'c', 'C' ]
  genList = []
  for headerFile in sys.argv[1:]:
    fileName = headerFile[:-2]
    obj2doth = fileName + '.obj2doth'
    if os.path.exists( obj2doth ):
      fileList = fileName.split( '/' )
      genName = cwd + '/' + fileList[-1]
      genList.append( genName )
      for suf in srcSufList:
        if os.path.exists(  genName + '.' + suf ):
          genList.remove( genName )
  return genList  


if __name__ == '__main__' :
  genList = check( os.getcwd() )
  for fullName in genList:
    genSrc( fullName )
