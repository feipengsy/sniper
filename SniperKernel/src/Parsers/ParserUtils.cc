// $Id: ParserUtils.cpp,v 1.7 2007/05/24 14:41:22 hmd Exp $
// ============================================================================
// CVS tag $Name: GAUDI_v20r4-pre $, version $Revision: 1.7 $ 
// ============================================================================
// Include files
// ============================================================================
// STD & STL
// ============================================================================
#include <iostream>
#include <fstream>
// ============================================================================
// Boost
// ============================================================================
#include <boost/filesystem/operations.hpp>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
// ============================================================================
// local
// ============================================================================
#include "ParserUtils.h"
#include "ParserGrammar.h"
// ============================================================================
namespace fs = boost::filesystem;
using namespace std;

// ============================================================================
/** @file
 *  implementation file for helper functions from 
 *  namespace Gaudi::Parsers and namespace Gaudi::Parsers:Utils 
 *  @see Gaudi::Parsers 
 *  @see Gaudi::Parsers::Utils 
 *
 *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
 *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
 *  @date   2006-05-13
 */
// ============================================================================
bool Gaudi::Parsers::Utils::getEnv
( const std::string& envName , std::string& envValue )
{
  char* envch = getenv(envName.c_str());
	if(envch==NULL) { return false; }
	envValue = envch;
  return true;
}
// ============================================================================
std::string 
Gaudi::Parsers::Utils::removeEnvironment(const std::string& input){
  std::string result=input;// result
  
  const char* re = "\\$(([A-Za-z0-9_]+)|\\(([A-Za-z0-9_]+)\\))";
  std::string::const_iterator start, end;
  boost::regex expression(re);
  start = input.begin();
  end = input.end();   
  boost::match_results<std::string::const_iterator> what;
  boost::match_flag_type flags = boost::match_default;
  while ( boost::regex_search(start, end, what, expression, flags ) )   
  {
    std::string var,env;
    std::string matched(what[0].first,what[0].second);
    std::string v1(what[2].first,what[2].second);
    std::string v2(what[3].first,what[3].second);      
    
    if ( v1.length()>0){ var = v1; }
    else { var = v2; }
    
    bool ok = getEnv(var, env);
    if(ok)
    { boost::algorithm::replace_first(result,matched, env); }
    start = what[0].second;
    // update flags:
    flags |= boost::match_prev_avail;
    flags |= boost::match_not_bob;
  }
  return result;
}
// ============================================================================
bool Gaudi::Parsers::Utils::searchFile
( const std::string&              fileInput  , 
  std::string&                    fileOutput )
{
    fs::path givenPath(removeEnvironment(fileInput),fs::native);
    if(fs::exists(fileOutput = givenPath.string())) {
	return true;
    }
    return false;
}
// ============================================================================
bool Gaudi::Parsers::Utils::readFile
(const std::string& name ,  std::string& result)
{
  std::ifstream in(name.c_str());
  if (!in.is_open()) { return false; }
  char c;
  while (!in.get(c).eof()) { result += c; }
  return true;  
}
// ============================================================================
bool Gaudi::Parsers::Utils::parseValue
( const string&             input        , 
  std::string&              stringResult ,
  std::vector<std::string>& vectorResult )
{
  
  typedef 
    boost::spirit::position_iterator<std::string::const_iterator> IteratorT;
  
  Gaudi::Parsers::ValueGrammar   grValue;
  Gaudi::Parsers::SkipperGrammar grSkipper;
  IteratorT beginpos(input.begin(), input.end(), "");
  IteratorT endpos;
  boost::tuple<std::string, std::vector<std::string> > result;
  boost::spirit::parse_info<IteratorT> info = 
    boost::spirit::parse
    (beginpos, endpos, grValue[var(result)=arg1] ,grSkipper);
  if (!info.full){ return false; }
  stringResult = result.get<0>();
  vectorResult = result.get<1>();
  return true;
}
// ============================================================================

// ============================================================================
// The END 
// ============================================================================

