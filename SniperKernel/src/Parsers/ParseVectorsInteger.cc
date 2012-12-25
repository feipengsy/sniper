// $Id: ParseVectorsInteger.cpp,v 1.2 2007/05/24 14:39:11 hmd Exp $
// ============================================================================
// CVS tag $Name: GAUDI_v20r4-pre $, version $Revision: 1.2 $ 
// ============================================================================
// Include files
// ============================================================================
// Local
// ============================================================================
#include "Parsers.icpp"
// ============================================================================

// ============================================================================
/** @file 
 *
 *  Implementation of the parsing functions for std::vetctor<TYPE>
 *  
 *  For adding new type you should have only grammar class which recognize 
 *  this type. Then by combining this grammar with such already implemented 
 *  grammars  like VectorGrammar, MapGrammar, PairGrammar you can very simply
 *  implement container types which will work with your type.
 *
 *  If you want your type can be handled in property file - see ValueGrammar
 *  in JobOptionsSvc which lays in GaudiSvc.
 *
 *  @author Alexander MAZUROV  Alexander.Mazurov@gmail.com
 *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
 *  @date   2006-05-12 
 */
// ============================================================================
namespace Gaudi
{ 
  namespace Parsers
  {
    // ========================================================================
    bool parse ( vector<short>&              result , 
                       const string&               input  )
    { return parse_integer_vector ( result , input ) ; }
    // ========================================================================
    bool parse ( vector<unsigned short>&     result , 
                       const string&               input  )
    { return parse_integer_vector ( result , input ) ; }
    // ========================================================================
    bool parse ( vector<int>&                result , 
                       const string&               input  )
    { return parse_integer_vector ( result , input ) ; }
    // ========================================================================
    bool parse ( vector<unsigned int>&       result , 
                       const string&               input  )
    { return parse_integer_vector ( result , input ) ; }
    // ========================================================================
    bool parse ( vector<long>&               result , 
                       const string&               input  )
    { return parse_integer_vector ( result , input ) ; }
    // ========================================================================
    bool parse ( vector<unsigned long>&      result , 
                       const string&               input  )
    { return parse_integer_vector ( result , input ) ; }
    // ========================================================================
    bool parse ( vector<long long>&          result , 
                       const string&               input  ) 
    { return parse_integer_vector ( result , input ) ; }
    // ========================================================================
    bool parse ( vector<unsigned long long>& result , 
                       const string&               input  )
    { return parse_integer_vector ( result , input ) ; }

  } // end of namespace Parsers
} // end of namespace Gaudi

// ============================================================================
// The END 
// ============================================================================


