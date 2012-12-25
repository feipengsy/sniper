// $Id: Catalogue.cpp,v 1.8 2007/05/24 14:41:22 hmd Exp $
// ============================================================================
// CVS tag $Name: GAUDI_v20r4-pre $, version $Revision: 1.8 $ 
// ============================================================================
// Include files
// ============================================================================
// Boost.string_algo
// ============================================================================
#include "boost/algorithm/string.hpp" // For case conversations
#include "boost/format.hpp" 
// ============================================================================
// local
// ============================================================================
#include "Catalogue.h"
#include "ParserUtils.h"
// ============================================================================
namespace ba = boost::algorithm;

// ============================================================================
// Purpose:    Implementation of Catalogue::findProperties()
// Comment:    Find properties of object by object name
// Parameters:
// - objName Object name
// - list Result list
// Return: true if catalogue contains object properties
// ============================================================================
bool Gaudi::Parsers::Catalogue::findProperties
( const std::string& objName, 
  std::vector<PropertyEntry>& lst, bool rm )
{
  ObjectsStoreT::iterator obj = 
    m_properties.find(objName);
  if ( obj == m_properties.end()){ return false; }
  PropertiesStoreT::const_iterator cur = obj->second.begin();
  PropertiesStoreT::const_iterator end = obj->second.end();
  for(;cur!=end;cur++){ lst.push_back(cur->second); }
  if ( rm ) m_properties.erase( obj );
  return true;
}

// ============================================================================
// Purpose:    Implementation of Catalogue::findProperty()
// Comment:    Find property in catalogue
// Parameters:
// - objName Object name
// - propName Property name
// - property
// Return: true -  if catalogue contains property
// ============================================================================
bool Gaudi::Parsers::Catalogue::findProperty
(  const std::string& objName, 
   const std::string& propName, 
   PropertyEntry& property, bool rm )
{
  ObjectsStoreT::iterator obj = m_properties.find(objName);
  if ( obj == m_properties.end()){ return false; }
  PropertiesStoreT::iterator prop = obj->second.find(propName);
  if ( prop==obj->second.end()){ return false; }
  property = prop->second;
  if ( rm ) {
      obj->second.erase( prop );
      if ( obj->second.empty() ) m_properties.erase( obj );
  }
  return true;
}

// ============================================================================
// Purpose:    Implementation of Catalogue::catalogue()
// Comment:    Return all objects names and their properties info
// Return:  objects names and their properties info
// ============================================================================
Gaudi::Parsers::Catalogue::CatalogueT 
  Gaudi::Parsers::Catalogue::catalogue() const
{
  CatalogueT result;
  for(ObjectsStoreT::const_iterator curObj=m_properties.begin();
    curObj!=m_properties.end();curObj++){
    std::vector<PropertyEntry> properties;
      for(PropertiesStoreT::const_iterator curProp=curObj->second.begin();
        curProp!=curObj->second.end();curProp++){
          properties.push_back(curProp->second);
       }      
     result[curObj->first] = properties;
   }
   return result;
}

// ============================================================================
// Purpose:    Implementation of Catalogue::addProperty()
// Comment:    Add property to catalogue
// Parameters:
// - objName Name of object
// - property PropertyEntry
// Return: 
// ============================================================================
void Gaudi::Parsers::Catalogue::addProperty
(  const std::string& objName, 
   const PropertyEntry& property )
{
  PropertyEntry prop = property;
  prop.removeEnv();
  m_properties[objName][ property.name()] = prop;
}

// ============================================================================
// Purpose:    Implementation of Catalogue::addProperty()
// Comment:    Add property to catalogue
// Parameters:  
//  - objName Name of object
//  - propName Property name
//  - value Value as string
// ============================================================================
bool Gaudi::Parsers::Catalogue::addProperty
( const std::string& objName, 
  const std::string& propName,
  const std::string& value )
{
  bool ok;
  std::string stringResult;
  std::vector<std::string> vectorResult;
  ok = Gaudi::Parsers::Utils::parseValue(value,stringResult,vectorResult);
  if(!ok){
    return false;
  }
  bool isVector = (vectorResult.size()>0) || (stringResult=="{}");
  if(isVector){
    addProperty(objName,PropertyEntry(propName,vectorResult));
  }else{
     addProperty(objName,PropertyEntry(propName,stringResult));        
  }
  return true;
}
// ============================================================================
///  case-insensitive comparison criteria for strings 
// ============================================================================
bool Gaudi::Parsers::_NoCaseCmp_::operator() 
  ( const std::string& s1 , 
    const std::string& s2 ) const 
{ return boost::to_lower_copy( s1 ) < boost::to_lower_copy( s2 ) ; }
// ============================================================================
// print the content of the catalogue to std::ostream
// ============================================================================
std::ostream& Gaudi::Parsers::Catalogue::fillStream ( std::ostream& o ) const 
{
  o << "// " << std::string(82,'=') << std::endl 
    << "//       Parser catalogue " << std::endl 
    << "// " << std::string(82,'=') << std::endl ;
  return print(o);
}
  
std::ostream& Gaudi::Parsers::Catalogue::print( std::ostream& o ) const
{
  //size_t nComponents = 0 ;
  //size_t nProperties = 0 ;
  
  CatalogueT cat = catalogue();
  for( Catalogue::CatalogueT::const_iterator obj = cat.begin();
       cat.end() != obj ; ++obj )
  {
      /*
    o << boost::format("// Properties of '%1%' %|40t|#=%2%" ) 
      % obj->first % obj->second.size() << std::endl ;
    ++nComponents ;
    nProperties += obj->second.size() ;
    */
    for( std::vector<PropertyEntry>::const_iterator prop = obj->second.begin(); 
         obj->second.end() != prop ; ++prop )
    {
      o << boost::format("%1%.%2%  %|32t| = %3% ; ") 
        % obj->first
        % prop->name()
        % prop->value() << std::endl ;
    }
  }
  /*
  o << "// " << std::string(82,'=') << std::endl
    << boost::format("// End parser catalogue #Components=%1% #Properties=%2%")
    % nComponents % nProperties     << std::endl 
    << "// " << std::string(82,'=') << std::endl ;
    */
  
  return o ; 
}
// ============================================================================       
// printout operator 
// ============================================================================
std::ostream& operator<<( std::ostream& o , const Gaudi::Parsers::Catalogue& c ) 
{ return c.fillStream ( o ) ; }
// ============================================================================

// ============================================================================
// The END 
// ============================================================================
