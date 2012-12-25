// $Id: Parsers.h,v 1.5 2008/01/14 19:42:56 marcocle Exp $
// ============================================================================
#ifndef GAUDIPROPERTYPARSERS_PARSERS_H
#define GAUDIPROPERTYPARSERS_PARSERS_H 1
// ============================================================================
// Include files
// ============================================================================
// STD & STL 
// ============================================================================
#include <string>
#include <vector>
#include <map>
// ============================================================================
/** @file
 *  The declaration of major parsing functions used e.g 
 *  for (re)implementation of new extended properties see class Property
 *  These function also could be used in a different, much wider contex.
 *  all of them have the semantic:
 *  <c>bool parse ( TYPE& result , const std::string& input )</c>
 *  where <c>input</c> is the input string to be parsed, 
 *  and <c>result</c> is the the result of parsing
 *
 *  @code 
 *  
 *  const std::string        input = ... ;
 *  std::vector<std::string> result ;
 * 
 *  // parse the input 
 *  bool sc = parse ( result , input ) ;
 *  if ( sc.isFailure() ) 
 *  {
 *    // error here ...
 *  }
 *  std::cout << "vector size " << result.size() << std::endl ;
 *
 *  @endcode 
 *
 *  @see Gaudi::Parsers::parse 
 *  @see Property 
 *
 *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
 *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
 *  @date 2006-05-12 
 */
// ============================================================================
namespace Gaudi
{
  // ==========================================================================
  namespace Parsers
  { 
    // ========================================================================
    /** parse the <c>bool</c> value
     *  @see Gaudi::Parsers::BoolGrammar 
     *  @param result (output) boolean result
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-12 
     */
    bool parse 
    ( bool& result , const std::string& input ) ;
    // ========================================================================
    /** parse the <c>char</c> value
     *
     *  @see Gaudi::Parsers::CharGrammar 
     *  @param result (output) boolean result
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-12 
     */
    bool parse
    ( char&              result , 
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser(char&,std::string&)
    bool parse
    ( unsigned char&     result , 
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser(char&,std::string&)
    bool parse
    ( signed char&       result ,
      const std::string& input  ) ;
    // ========================================================================
    /** parse the <c>int</c> value
     *
     *  @see Gaudi::Parsers::IntGrammar 
     *  @param result (output) integer result
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */
    bool parse 
    ( int&               result ,
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( int&, const std::string& )
    bool parse
    ( short&             result , 
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( int&, const std::string& )
    bool parse
    ( unsigned short&    result ,
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( int&, const std::string& )
    bool parse
    ( unsigned int&      result , 
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( int&, const std::string& )
    bool parse
    ( long&              result , 
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( int&, const std::string& )
    bool parse
    ( unsigned long&     result ,
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( int&, const std::string& )
    bool parse
    ( long long&         result ,
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( int&, const std::string& )
    bool parse
    ( unsigned long long& result,
      const std::string& input  ) ;
    // ========================================================================
    /** parse the <c>double</c> value
     *
     *  @see Gaudi::Parsers::RealGrammar 
     *  @param result (output) double result
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */
    bool parse
    ( double&            result ,
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( double&, const std::string& )
    bool parse
    ( float&             result ,
      const std::string& input  ) ;
    /// @see Gaudi::Parsers::parser( double&, const std::string& )
    bool parse
    ( long double&       result , 
      const std::string& input  ) ;
    // ========================================================================
    /** parse the <c>std::string</c> value
     *
     *  @see Gaudi::Parsers::StringGrammar 
     *  @param result (output) string result
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */
    bool parse 
    ( std::string&       result , 
      const std::string& input  ) ;
    // ========================================================================
    /** parse the <c>std::vector\<bool\></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::BoolGrammar 
     *  @param result (output) vector with boolean elements
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */
    bool parse
    ( std::vector<bool>& result , 
      const std::string& input  ) ;
    // ========================================================================
    /** parse the <c>std::vector\<char\></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::CharGrammar 
     *  @param result (output) vector with char elements
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */
    bool parse
    ( std::vector<char>&          result , 
      const std::string&          input  ) ;
    /// @see parse( std::vector<char>& ,const std::string& );
    bool parse
    ( std::vector<unsigned char>& result ,
      const std::string&          input  ) ;
    /// @see parse( std::vector<char>& ,const std::string& );
    bool parse
    ( std::vector<signed char>&   result ,
      const std::string&          input  ) ;
    // ========================================================================
    /** parse the <c>std::vector\<int\></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::IntGrammar 
     *  @param result (output) vector with integer elements
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */
    bool parse
    ( std::vector<int>&            result , 
      const std::string&           input  ) ;
    /// @see parse( std::vector<int>& ,const std::string& );
    bool parse
    ( std::vector<short>&          result , 
      const std::string&           input  ) ;
    /// @see parse( std::vector<int>& ,const std::string& );
    bool parse
    ( std::vector<unsigned short>& result ,
      const std::string&           input  ) ;
    /// @see parse( std::vector<int>& ,const std::string& );
    bool parse
    ( std::vector<unsigned int>&   result ,
      const std::string&           input  ) ;
    /// @see parse( std::vector<int>& ,const std::string& );
    bool parse
    ( std::vector<long>&           result , 
      const std::string&           input  ) ;
    /// @see parse( std::vector<int>& ,const std::string& );
    bool parse
    ( std::vector<unsigned long>&  result ,
      const std::string&           input  ) ;
    /// @see parse( std::vector<int>& ,const std::string& );
    bool parse
    ( std::vector<long long>&      result , 
      const std::string&           input  ) ;
    /// @see parse( std::vector<int>& ,const std::string& );
    bool parse
    ( std::vector<unsigned long long>& result,
      const std::string&           input  ) ;
    // ========================================================================
    /** parse the <c>std::vector\<double\></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::RealGrammar 
     *  @param result (output) vector with double elements
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */
    bool parse
    ( std::vector<double>&      result ,
      const std::string&        input  ) ;
    /// @see parse( std::vector<double>& ,const std::string& );
    bool parse
    ( std::vector<float>&       result ,
      const std::string&        input  ) ;
    /// @see parse( std::vector<double>& ,const std::string& );
    bool parse
    ( std::vector<long double>& result , 
      const std::string&        input  ) ;
    // ========================================================================
    /** parse the <c>std::vector\<std::string\></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::StringGrammar 
     *  @param result (output) vector with string elements
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::vector<std::string>& result , 
      const std::string&        input  ) ;
    // ========================================================================
    // Advanced parses
    // ========================================================================
    /** parse the <c>std::pair\<double,double\></c> value
     *
     *  @see Gaudi::Parsers::PairGrammar 
     *  @see Gaudi::Parsers::RealGrammar 
     *  @param result (output) pair of doubles
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse 
    ( std::pair<double,double>& result , 
      const std::string&        input  ) ;
    // ========================================================================
    /** parse the <c>std::pair\<int,int\></c> value
     *
     *  @see Gaudi::Parsers::PairGrammar 
     *  @see Gaudi::Parsers::IntGrammar 
     *  @param result (output) pair of integers
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::pair<int,int>& result , 
      const std::string&  input  ) ;
    // ========================================================================
    /** parse the <c>std::vector\<std::pair\<double,double\> \></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::PairGrammar 
     *  @see Gaudi::Parsers::RealGrammar 
     *  @param result (output) vector with pairs of doubles
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::vector< std::pair<double,double> >& result ,
      const std::string&                       input  ) ;
    // ========================================================================
    /** parse the <c>std::vector\<std::pair\<int,int\> \></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::PairGrammar 
     *  @see Gaudi::Parsers::IntGrammar 
     *  @param result (output) vector with pairs of int
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::vector< std::pair<int,int> >& result , 
      const std::string&                 input  ) ;
    // ========================================================================
    // vector< vector< TYPE > >
    // ========================================================================
    /** parse the <c>std::vector\<std::vector\<std::string\> \></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::StringGrammar 
     *  @param result (output) vector with vectors of strings
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::vector< std::vector<std::string> >& result ,
      const std::string&                       input  ) ;
    // ========================================================================    
    /** parse the <c>std::vector\<std::vector\<double\> \></c> value
     *
     *  @see Gaudi::Parsers::VectorGrammar 
     *  @see Gaudi::Parsers::RealGrammar 
     *  @param result (output) vector with vectors of doubles
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::vector< std::vector<double> >& result ,
      const std::string&                  input  ) ;    
    // ========================================================================
    // map< TYPE, TYPE >
    // ========================================================================    
    /** parse the <c>std::map\<int , int\></c> value
     *
     *  @see Gaudi::Parsers::MapGrammar 
     *  @see Gaudi::Parsers::IntGrammar 
     *  @param result (output) map with integer key and double value
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::map< int , int >& result , 
      const std::string&     input  ) ;
    // ========================================================================
    /** parse the <c>std::map\<int , double\></c> value
     *
     *  @see Gaudi::Parsers::MapGrammar 
     *  @see Gaudi::Parsers::IntGrammar 
     *  @see Gaudi::Parsers::RealGrammar 
     *  @param result (output) map with integer key and double value
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::map< int , double >& result , 
      const std::string&        input  ) ;
    // ========================================================================    
    /** parse the <c>std::map\<std::string , std::string\></c> value
     *
     *  @see Gaudi::Parsers::MapGrammar 
     *  @see Gaudi::Parsers::StringGrammar 
     *  @param result (output) map with string key and value
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::map< std::string , std::string >& result , 
      const std::string&                     input  ) ;
    // ========================================================================    
    /** parse the <c>std::map\<std::string , int\></c> value
     *
     *  @see Gaudi::Parsers::MapGrammar 
     *  @see Gaudi::Parsers::StringGrammar
     *  @see Gaudi::Parsers::IntGrammar
     *  @param result (output) map with string key and integer value
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::map< std::string , int >& result , 
      const std::string&             input  ) ;
    // ========================================================================    
    /** parse the <c>std::map\<std::string , double\></c> value
     *
     *  @see Gaudi::Parsers::MapGrammar 
     *  @see Gaudi::Parsers::StringGrammar
     *  @see Gaudi::Parsers::RealGrammar
     *  @param result (output) map with string key and integer value
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::map< std::string , double >& result , 
      const std::string&                input  ) ;
    // ========================================================================    
    /** parse the <c>std::map\<std::string , std::vector\<std::string\> \></c> 
     *  value
     *
     *  @see Gaudi::Parsers::MapGrammar 
     *  @see Gaudi::Parsers::StringGrammar
     *  @see Gaudi::Parsers::VectorGrammar
     *  @param result (output) map with string value and 
     *                 vector of strings as value
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::map< std::string , std::vector< std::string> >& result ,
      const std::string&                                   input  ) ;
    // ========================================================================    
    /** parse the <c>std::map\<std::string , std::vector\<int\> \></c> value
     *
     *  @see Gaudi::Parsers::MapGrammar 
     *  @see Gaudi::Parsers::StringGrammar
     *  @see Gaudi::Parsers::VectorGrammar
     *  @see Gaudi::Parsers::IntGrammar
     *  @param result (output) map with string value and 
     *                 vector of integers as value
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::map< std::string , std::vector< int > >& result , 
      const std::string&                            input  ) ;
    // ========================================================================    
    /** parse the <c>std::map\<std::string , std::vector\<double\> \></c> value
     *
     *  @see Gaudi::Parsers::MapGrammar 
     *  @see Gaudi::Parsers::StringGrammar
     *  @see Gaudi::Parsers::VectorGrammar
     *  @see Gaudi::Parsers::RealGrammar
     *  @param result (output) map with string value and 
     *                 vector of doubles as value
     *  @param input  (input) the string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-14 
     */    
    bool parse
    ( std::map< std::string , std::vector< double > >& result ,
      const std::string&                               input  ) ;    
    // ======================================================================== 
    /** parse the <c>std::map\<int,std::string\> \></c> objects 
     *
     *  @see Gaudi::Parsers::MapGrammar
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @date 2007-12-06
     */
    bool parse 
    ( std::map<int, std::string>& result , 
      const std::string&          input  ) ;
    // ======================================================================== 
    /** parse the <c>std::map\<unsigned int,std::string\> \></c> objects 
     *
     *  @see Gaudi::Parsers::MapGrammar
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @date 2007-12-06
     */
    bool parse 
    ( std::map<unsigned int, std::string>& result , 
      const std::string&          input  ) ;
    // ======================================================================== 
    /** parse the pair expression (map-component)  " 'name' :value" 
     *  
     *  @code 
     *  
     *  const std::string input = "'PackageName':GaudiKernel" ;
     *  std::string name  ;
     *  std::string value ;
     *  bool sc = Gaudi::Parsers::parse ( name , value , input ) ;
     *  if ( sc.isFailure() ) { ... } 
     *  std::cout <<  "\tParsed name  is " << name 
     *            <<  "\tParsed value is " << value << std::endl 
     *  @endcode 
     *  
     *  @param  name  (output) the parsed name of the component, defined 
     *                as 'name' or "name" before the column symbol ":", 
     *                the leading and trailing blans are omitted 
     *  @param  value (output) the parsed value of the component, 
     *                defined as everything after the column symbol ":" 
     *                till the end of the string
     *  @param  input (input) string to be parsed 
     *  @return status code 
     *  
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com 
     *  @author Vanya BELYAEV  ibelyaev@physics.syr.edu
     *  @date 2006-05-12 
     */
    bool parse
    ( std::string&       name  ,
      std::string&       value ,
      const std::string& input ) ;
    // ========================================================================    
  } // end of namespace Parsers  
} // end of namespace Gaudi
// ============================================================================
// The END 
// ============================================================================
#endif //GAUDIPROPERTYPARSERS_PARSERS_H
// ============================================================================
