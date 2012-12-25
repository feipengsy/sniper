// $Id: Parser.cpp,v 1.11 2007/12/06 15:14:21 marcocle Exp $
// ============================================================================
// Include files
// ============================================================================
// STD & STL 
// ============================================================================
#include <iostream>
// ============================================================================
// Boost
// ============================================================================
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
// ============================================================================
// local 
// ============================================================================
#include "ParserUtils.h"
#include "ParserGrammar.h"
// ============================================================================
// local namespaces:
// ============================================================================
namespace ba = boost::algorithm;
// ============================================================================
namespace 
{
  const std::string GPP_COMMENT = "//GP:" ;
}
// ============================================================================
Gaudi::Parsers::Parser::Parser
( Catalogue&                catalogue , 
  std::vector<std::string>& included  , 
  std::ostream&             m         )
  : m_isPrint(false)
  , m_isPrintOptions(true)
  , m_catalogue(catalogue)
  , m_included(included)
  , m_stream ( m )
{
}
// ============================================================================
bool Gaudi::Parsers::Parser::parse ( const std::string& fileName )
{
  //m_stream << GPP_COMMENT + std::string(80,'=') << std::endl;
  bool sc = parseFile(fileName,Position());
  resolveReferences();
  if ( sc && m_isPrintOptions ){
      m_stream << m_catalogue;
      m_stream << "// " << std::string(82,'=') << std::endl;
  }
  return errorsCount()==0?true:false;
}
// ============================================================================
int Gaudi::Parsers::Parser::errorsCount()
{
	int result=0;
	for ( MessagesStoreT::const_iterator cur=m_messages.begin();
        cur!=m_messages.end() ; ++cur)
  { if ( cur->severity() == Message::E_ERROR){ ++result; } }
	return result;
}
// ============================================================================
void Gaudi::Parsers::Parser::matchInclude
(const std::string& fileName,const Position& pos)
{ parseFile(fileName,pos); }
// ============================================================================
void Gaudi::Parsers::Parser::matchAssign
( const std::string& objName  ,
  const std::string& propName , 
  const Sign& oper,
  const std::vector<std::string>& vectorValue,
  const Position& pos,bool isVector)
{
  // --------------------------------------------------------------------------
  if( m_isPrint )
  {
    m_stream 
      << boost::format("%2% %3% %4%;%|72t|%5% %1%") 
      % posString(pos.line(),pos.column()) 
      % (objName+"."+propName) 
      % sign(oper) 
      % valueToString(vectorValue , isVector) 
      % GPP_COMMENT 
      << std::endl ;
  }
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  if (oper == S_ASSIGN)
  {
    // ------------------------------------------------------------------------
    PropertyEntry* assignProp;
    if(isVector){
      assignProp = new PropertyEntry(propName,vectorValue,pos);
    }else{
      assignProp = new PropertyEntry(propName,vectorValue[0],pos);
    }
    m_catalogue.addProperty(objName,*assignProp);
    delete assignProp;
    // ------------------------------------------------------------------------
  }
  else
  {
    // += or -=
    // ------------------------------------------------------------------------
    PropertyEntry foundProp;
    bool ok;
    ok = m_catalogue.findProperty(objName,propName,foundProp);
    if (!ok)
    {
      foundProp = PropertyEntry(propName,std::vector<std::string>());
    }
    if(oper == S_PLUSASSIGN)
    {
      ok = foundProp.addValues(vectorValue);
      if(!ok){
        addMessage
          ( Message::E_ERROR, 
            Message::C_CANNOTADDTONOTVECTOR,
            boost::str
            ( boost::format
              ("Cannot add values to not vector property \"%1%.%2%\"")
              %  objName % propName),pos);
        return;
      }
      m_catalogue.addProperty(objName,foundProp);
    }
    // ------------------------------------------------------------------------
    if(oper == S_MINUSASSIGN)
    {
      int count=0;
      ok = foundProp.removeValues(vectorValue,count);
      if(!ok){
        addMessage
          ( Message::E_ERROR, 
            Message::C_CANNOTREMOVEFROMNOTVECTOR,
            boost::str
            ( boost::format
              ( "Cannot remove values from not vector property \"%1%.%2%\"" ) 
              %  objName % propName),pos);
        return;
      }
      // ----------------------------------------------------------------------
      if (count == 0)
      {
        addMessage
          ( Message::E_WARNING, 
            Message::C_ZEROREMOVED,
            boost::str
            ( boost::format
              ( "Nothing removed from property \"%1%.%2%\"" ) 
              %  objName % propName),pos);   
      }
      else
      {
        m_catalogue.addProperty(objName,foundProp);
      }
      
    } 
    // ------------------------------------------------------------------------
  }
}
// ============================================================================
void Gaudi::Parsers::Parser::setIsPrint
( bool on , const Gaudi::Parsers::Position& pos)
{
  // ignore the printout if the full print is activated  
  if ( on && m_isPrintOptions ) { return ; }
  m_isPrint = on;
  //m_stream 
  //  << boost::format("%3% printing is %2% %|78t|%1%") 
  //  % posString(pos.line(),pos.column()) 
  //  % (on?"ON":"OFF") 
  //  % GPP_COMMENT 
  //  << std::endl ;
}
// ============================================================================
void Gaudi::Parsers::Parser::setIsPrintOptions
( bool on , const Position& pos)
{
  m_isPrintOptions = on;
  //m_stream 
  //  << boost::format ("%3% printing options is %2% %|78t|%1%") 
  //  % posString(pos.line(),pos.column()) 
  //  % (on?"ON":"OFF") 
  //  % GPP_COMMENT 
  //  << std::endl ;
  // deactivate the printout if the print of all options is activated 
  if ( m_isPrintOptions && m_isPrint ) { setIsPrint ( false , pos ) ; }
}
// ============================================================================
bool Gaudi::Parsers::Parser::parseFile
( const std::string& fileName ,
  const Position& pos)
{
  std::string fileToParse;
  bool ok = Gaudi::Parsers::Utils::searchFile(fileName,fileToParse);
  if(!ok){
    addMessage( Message::E_ERROR, Message::C_FILENOTFOUND,
               boost::str(boost::format("Couldn't find file \"%1%\"") % fileName),pos);
    return false;
  }
  
  ok = isIncluded(fileToParse);
  if(ok)
  {
    const std::string _msg = 
      ( boost::format("Skip already included file  \"%1%\"") % fileToParse ).str() ;
    addMessage ( Message::E_WARNING , Message::C_OK , _msg , pos ) ;
    if ( m_isPrint ) 
    { 
      m_stream 
        << boost::format("%3% skip already included file  \"%2%\" %|78t|%1%") 
        % posString(pos.line(), pos.column()) 
        % fileToParse 
        % GPP_COMMENT
        << std::endl ; 
    }
    return true;
  }
  std::string input;
  ok = Gaudi::Parsers::Utils::readFile(fileToParse,input);
  if(!ok)
  {
    addMessage
      ( Message::E_ERROR, Message::C_FILENOTOPENED,
       boost::str
       (boost::format("Couldn't open file \"%1%\"") % fileToParse),pos);
    return false;
  }  
  m_included.push_back(fileToParse);
  
  
  IteratorT beginpos(input.begin(), input.end(), fileToParse);
  IteratorT endpos;
  
  boost::spirit::parse_info<IteratorT> info; 
  SkipperGrammar grSkipper;      
  
  //m_stream 
  //    << boost::format("%3% include \"%2%\" %|78t|%1%") 
  //    % posString(pos.line(), pos.column()) 
  //    % fileToParse 
  //    % GPP_COMMENT 
  //    << std::endl ;
  ParserGrammar grParser(this);
  info = boost::spirit::parse(beginpos, endpos, grParser >> end_p,grSkipper);

  boost::spirit::file_position stoppos = info.stop.get_position();
  if (!info.full) {
    addMessage(Message::E_ERROR, Message::C_SYNTAXERROR,
               "Syntax error",Position(stoppos.file,stoppos.line,stoppos.column));
    return false;      
  }
  {
    std::string _msg =
      ( boost::format("Parsed file \"%2%\" %|78t|%1%")  
        % posString(stoppos.line, stoppos.column) 
        % fileToParse ) .str() ;
    addMessage ( Message::E_VERBOSE , 
                 Message::C_OK , 
                 _msg ,
                 Position(stoppos.file,stoppos.line,stoppos.column) ) ;
    if ( m_isPrint )
    { 
      m_stream 
        << boost::format("%3% end  \"%2%\" %|78t|%1%")
        % posString(stoppos.line, stoppos.column) 
        % fileToParse 
        % GPP_COMMENT 
        << std::endl ; 
    }
  }
  return true;  
}
// ============================================================================
std::string Gaudi::Parsers::Parser::severityName
(Message::Severity severity){
  switch(severity)
  {
  case Message::E_ERROR   :
    return "ERROR"     ;
  case Message::E_WARNING :
    return "WARNING"   ;
  case Message::E_NOTICE  :
    return "NOTICE"    ;
  case Message::E_VERBOSE :
    return "VERBOSE"   ;
  default:
    return "UNDEFINED" ; 
  }
}
// ============================================================================
void Gaudi::Parsers::Parser::addMessage
( const Message::Severity& severity ,
  const Message::Code&     code     , 
  const std::string&       message  , 
  const Position&          pos      )
{
  Message result
    ( severity , code,
      boost::str(boost::format("%1%(%2%,%3%) : %4% #%5% : %6%") % pos.fileName()
                 % pos.line() % pos.column() % severityName(severity) % code 
                 % message));
  m_messages.push_back(result);
}
// ============================================================================
// Purpose: Implementation of Parser::isIncluded()
// Comment: Test if file already included
// Parameters:
//  - fileName File name
// Return: true if file already included
// ============================================================================
bool Gaudi::Parsers::Parser::isIncluded(const std::string& fileName)
{
  for(std::vector<std::string>::const_iterator cur=m_included.begin();
      cur!=m_included.end();cur++)
  { if(fileName==*cur){ return true; } }
  return false;
}
// ============================================================================
// Purpose: Implementation of Parser::resolveReferences()
// Comment: Resolve references
// TODO: Refactor?
// ============================================================================
void Gaudi::Parsers::Parser::resolveReferences()
{
  Catalogue::CatalogueT cat = m_catalogue.catalogue();
  // ----------------------------------------------------------------------------
  for( Catalogue::CatalogueT::const_iterator curObj = cat.begin();  
       curObj!=cat.end();curObj++)
  {
    std::string objName = curObj->first;
    // ------------------------------------------------------------------------
    for( std::vector<PropertyEntry>::const_iterator curProp = 
           curObj->second.begin();curProp != curObj->second.end(); curProp++)
    {
      std::string value = curProp->value();
      if ( (value.length()>0) && (value[0]=='@'))
      {
        // --------------------------------------------------------------------
        std::vector<std::string> objAndProp;
        std::string refprop(value.begin()+1,value.end());
        ba::split(objAndProp,
                  refprop,
                  ba::is_any_of("."));            
        PropertyEntry foundProperty;
        bool ok;
        ok = m_catalogue.findProperty(objAndProp[0],objAndProp[1],
                                      foundProperty);
        if(!ok)
        {
          addMessage
            ( Message::E_ERROR,
              Message::C_PROPERTYNOTFOUND,
              boost::str(boost::format("Cannot find property \"%1%.%2%\"")
                         % objAndProp[0] % objAndProp[1]),curProp->position());
        }
        else
        {
          // -------------------------------------------------------------------
          if((ba::to_lower_copy(objAndProp[0]) == objName)
             && 
             (ba::to_lower_copy(objAndProp[1]) 
              == curProp->name()))
          {
            // ----------------------------------------------------------------
            addMessage
              ( Message::E_ERROR,
                Message::C_BADREFERENCE,
                boost::str(boost::format("Reference to self \"%1%.%2%\"")
                           % objAndProp[0] % objAndProp[1]),curProp->position());
            // ----------------------------------------------------------------
          }
          else
          {
            PropertyEntry property = foundProperty;
            property.setName(curProp->name());
            m_catalogue.addProperty(objName,property);
          }
          // ------------------------------------------------------------------
        }
        // --------------------------------------------------------------------
      }
    }
    // ------------------------------------------------------------------------
  }
}
// ============================================================================
// String representation of sign
// ============================================================================
std::string Gaudi::Parsers::Parser::sign(Sign aSign)
{
  switch(aSign)
  {
  case S_ASSIGN:
    return "=";
  case S_PLUSASSIGN:
    return "+=";
  case S_MINUSASSIGN:
    return "-=";
  default:
    return "unknown_operation";
  }
}
// ============================================================================
// String representation of value vector
// ============================================================================
std::string Gaudi::Parsers::Parser::valueToString
( std::vector<std::string> value, bool isVector )
{
  if ( !isVector){ return value[0]; }
  //
  std::string result;
  std::string delim;
  result+=" [ ";
  for ( std::vector<std::string>::const_iterator cur = value.begin();
        cur != value.end(); cur++ )
  {
    result += delim + *cur;
    delim = " , ";
  }
  return result + " ] ";
}
// ============================================================================
/*  Implementation of Gaudi::Parsers::Utils::posString()
 *  Comment: Convert position to string
 *  Parameters:
 *    - line Line
 *    - column Column
 */
// ============================================================================
std::string Gaudi::Parsers::Parser::posString(int line, int column)
{ return boost::str(boost::format("(%1%,%2%)") % line % column); }
// ============================================================================

// ============================================================================
// The END 
// ============================================================================
