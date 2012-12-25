// $Id: ParseVectorsVector.cpp,v 1.5 2008/10/28 14:02:18 marcocle Exp $
// ============================================================================
// CVS tag $Name: GAUDI_v20r4-pre $, version $Revision: 1.5 $ 
// ============================================================================
// Include files
// ============================================================================
// Local
// ============================================================================
#include "Parsers.icpp"
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
    // vector< vector< TYPE > >
    // ========================================================================
    bool parse 
    ( std::vector< std::vector<std::string> >& result , 
      const std::string&                       input  )
    {
      VectorGrammar< VectorGrammar<StringGrammar> > g;
      return parse
        ( createIterator(input), 
          IteratorT(),
          g[var(result)=arg1],
          SkipperGrammar()).full ;
    }
    // ========================================================================
    bool parse 
    ( std::vector< std::vector<double> >& result , 
      const std::string&                  input  )
    {
      VectorGrammar< VectorGrammar< RealGrammar< double > > > g;
      return parse
        ( createIterator(input), 
          IteratorT(),
          g[var(result)=arg1],
          SkipperGrammar()).full;
    }
    // ========================================================================
    bool parse
    ( std::vector< std::pair< double , double > >& result , 
      const string&                                input  )
    {
      VectorGrammar<PairGrammar<RealGrammar<double>,RealGrammar<double> > > g;
      return parse
        ( createIterator(input), 
          IteratorT(),
          g[var(result)=arg1],
          SkipperGrammar()).full;
    }
    // ========================================================================
    bool parse
    ( std::vector< std::pair< int , int > >& result , 
      const string&                          input  )
    {
      VectorGrammar<PairGrammar<IntGrammar<int>,IntGrammar<int> > > g;
      return parse
        ( createIterator(input), 
          IteratorT(),
          g[var(result)=arg1],
          SkipperGrammar()).full;
    }
    // ========================================================================
  } // end of namespace Parsers
} // end of namespace Gaudi

// ============================================================================
// The END 
// ============================================================================


