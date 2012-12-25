// $Id: PropertyEntry.cpp,v 1.4 2007/05/24 14:41:21 hmd Exp $
// ============================================================================
// CVS tag $Name: GAUDI_v20r4-pre $, version $Revision: 1.4 $ 
// ============================================================================
// Include files
// ============================================================================
// STD & STL 
// ============================================================================
#include <algorithm>
// ============================================================================
// local 
// ============================================================================
#include "Catalogue.h"
#include "ParserUtils.h"
// ============================================================================

// ============================================================================
// Purpose:    Implementation of PropertyEntry::PropertyEntry()
// Comment:    Constructor
// Parameters:
// - name Name of property
// - value String value of property
// Return: 
// ============================================================================
Gaudi::Parsers::PropertyEntry::PropertyEntry
(  const std::string& name, 
   const std::string& value )
  : m_name(name),
    m_isVector(false)
{
   m_value.push_back(value);
}
// ============================================================================
// Purpose:    Implementation of PropertyEntry::PropertyEntry()
// Comment:    Constructor
// Parameters:
// - name Name of property
// - value Vector value of property
// Return: 
// ============================================================================
Gaudi::Parsers::PropertyEntry::PropertyEntry
( const std::string& name, 
  const std::vector<std::string>& value )
  : m_name(name),
    m_value(value),
    m_isVector(true)
{
   if ( 1 == m_value.size() && "" == m_value[0] ) { clear(); }
}
// ============================================================================
// Purpose:    Implementation of PropertyEntry::PropertyEntry()
// Comment:    Constructor
// Parameters:
// - name Name of property
// - value String value of property
// - position Property position in file
// Return: 
// ============================================================================
Gaudi::Parsers::PropertyEntry::PropertyEntry
(  const std::string& name, 
   const std::string& value,
   const Position& pos )
  : m_name(name),
    m_position(pos),
    m_isVector(false)
{
   m_value.push_back(value);
}

// ============================================================================
// Purpose:    Implementation of PropertyEntry::PropertyEntry()
// Comment:    Constructor
// Parameters:
// - name Name of property
// - value Vector value of property
// - position Property position in file
// Return: 
// ============================================================================
Gaudi::Parsers::PropertyEntry::PropertyEntry
( const std::string& name, 
  const std::vector<std::string>& value,
  const Position& pos )
  : m_name(name),
    m_value(value),
    m_position(pos),
    m_isVector(true)
{
   if ( 1 == m_value.size() && "" == m_value[0] ) { clear(); }
}

// ============================================================================
// Purpose:    Implementation of PropertyEntry::value()
// Comment:    Value of property
// Return: Value of property
// ============================================================================
std::string Gaudi::Parsers::PropertyEntry::value(void) const
{
   std::string result="";
   if(m_isVector){
      result = "[";
      std::string delim="";
      for(std::vector<std::string>::const_iterator cur=m_value.begin();
         cur!=m_value.end();cur++){
            result+=delim+*cur;
            delim=",";
      }
      result+="]";
   }else{
      if(m_value.size()>0){
         result = m_value[0];
        }
   }
   return result;
}

// ============================================================================
// Purpose:    Implementation of PropertyEntry::addValues()
// Comment:    Add values to vector value
// Parameters:
// - values Values to add
// Return: true if property value is vector 
//  (and we can add values)
// ============================================================================
bool Gaudi::Parsers::PropertyEntry::addValues
( const std::vector<std::string>& values )
{
   if(!m_isVector) return false;
   for(std::vector<std::string>::const_iterator cur = values.begin();
    cur!=values.end();cur++){
      m_value.push_back(*cur);
    }
   return true;   
}

// ============================================================================
// Purpose:    Implementation of PropertyEntry::removeValues()
// Comment:    Remove values from property value
// Parameters:
// - values 
// - count Count of removed items
// Return: true if property value is vector 
//  (and we can remove values)
// ============================================================================
bool Gaudi::Parsers::PropertyEntry::removeValues
( const std::vector<std::string>& values, 
  int& count )
{
   if(!m_isVector) return false;
   for(std::vector<std::string>::const_iterator
      cur = values.begin();cur!=values.end();cur++){
      std::vector<std::string>::iterator item = std::find(m_value.begin(),
        m_value.end(),*cur);
      if(item!=m_value.end()){
         m_value.erase(item);
         count++;
      }
    }
    return true;
}

// ============================================================================
// Purpose:    Implementation of PropertyEntry::clear()
// Comment:    Clear property vector value
// Return: true if property value is vector 
// (and we can clear values)
// ============================================================================
bool Gaudi::Parsers::PropertyEntry::clear(void)
{
   if(!m_isVector) return false;
   m_value.clear();
   return true;
}
// ============================================================================
/// remove environment variables 
// ============================================================================
bool Gaudi::Parsers::PropertyEntry::removeEnv() 
{
  for ( std::vector<std::string>::iterator item = 
          m_value.begin() ; m_value.end() != item ; ++item ) 
  { *item = Gaudi::Parsers::Utils::removeEnvironment ( *item ) ; }
  return true ;
}
// ============================================================================

// ============================================================================
// The END 
// ============================================================================
