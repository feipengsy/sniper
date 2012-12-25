// $Id: ToStream.h,v 1.8 2008/10/30 23:38:46 marcocle Exp $
// ============================================================================
// CVS tag $Name: GAUDI_v20r4-pre $, version $Revision: 1.8 $
// ============================================================================
#ifndef GAUDIPROPERTYPARSERS_PARSERVALUETOSTREAM_H
#define GAUDIPROPERTYPARSERS_PARSERVALUETOSTREAM_H 1
// ============================================================================
// Include files
// ============================================================================
// STD & STL
// ============================================================================
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <sstream>

namespace Gaudi
{
  namespace Utils
  {
    // ========================================================================
    /** the generic implementation of the printout to the std::ostream 
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-05-12
     */
    template<class TYPE> 
    std::ostream& toStream ( const TYPE& obj, std::ostream& s ) ;
    
    // ========================================================================
    /** the printtout of the strings.
     *  the string is printed a'la Python using the quotes
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-05-12
     */     
    inline std::ostream& toStream 
    ( const std::string& obj , std::ostream& s )
    {
      if ( std::string::npos == obj.find('\'') )
      { s << "\'" << obj << "\'" ; }
      else 
      { s << "\"" << obj << "\"" ; }
      return s ;
    }
    /** the printout of boolean values "a'la Python"
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-09-09        
     */
    inline std::ostream& toStream 
    ( const bool         obj , std::ostream& s ) 
    { return s << ( obj ? "True" : "False" ) ; }
    /** the printout of float values with the reasonable precision
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-09-09        
     */
    inline std::ostream& toStream 
    ( const float        obj , std::ostream& s ) 
    { 
      const int  p = s.precision() ;
      return s << std::setprecision (  6 ) << obj << std::setprecision ( p ) ;
    }
    /** the printout of double values with the reasonable precision
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-09-09        
     */
    inline std::ostream& toStream 
    ( const double       obj , std::ostream& s ) 
    { 
      const int p = s.precision() ;
      return s << std::setprecision (  8 ) << obj << std::setprecision ( p ) ;
    }
    /** the printout of long double values with the reasonable precision
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-09-09        
     */
    inline std::ostream& toStream 
    ( const long double  obj , std::ostream& s ) 
    { 
      const int p = s.precision() ;
      return s << std::setprecision ( 10 ) << obj << std::setprecision ( p ) ;
    }
    // ========================================================================
    /** the partial template specialization of 
     *  <c>std::pair<KTYPE,VTYPE></c> printout 
     *  the pair is printed a'la Python tuple: " ( a , b )"
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-05-12
     */     
    template<class KTYPE, class VTYPE> 
    inline std::ostream& toStream 
    ( const std::pair<KTYPE,VTYPE>& obj, std::ostream& s)
    {
      s << "( "  ; 
      toStream ( obj.first  , s ) ;
      s << " , " ;
      toStream ( obj.second , s ) ;
      return s << " )" ;
    }
    // ========================================================================
    /** the partial template specialization of <c>std::vector<TYPE,ALLOCATOR></c> 
     *  printout. The vector is printed a'la Python list: "[ a, b, c ]"
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-05-12
     */     
    template<class TYPE,class ALLOCATOR> 
    inline std::ostream& toStream 
    ( const std::vector<TYPE,ALLOCATOR>& obj, std::ostream& s)
    {
      s << "[ ";
      for ( typename std::vector<TYPE,ALLOCATOR>::const_iterator cur = obj.begin() ;
            obj.end() != cur ; ++cur )
      {
        if ( obj.begin() != cur ) { s << " , "; }
        toStream ( *cur , s ) ;
      }
      return s << " ]";
    }
    // ========================================================================
    /** the partial template specialization of <c>std::list<TYPE,ALLOCATOR></c> 
     *  printout. The vector is printed a'la Python list: "[ a, b, c ]"
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2007-04-08
     */     
    template<class TYPE,class ALLOCATOR> 
    inline std::ostream& toStream 
    ( const std::list<TYPE,ALLOCATOR>& obj, std::ostream& s)
    {
      s << "[ ";
      for ( typename std::list<TYPE,ALLOCATOR>::const_iterator cur = obj.begin() ;
            obj.end() != cur ; ++cur )
      {
        if ( obj.begin() != cur ) { s << " , "; }
        toStream ( *cur , s ) ;
      }
      return s << " ]";
    }
    // ========================================================================
    /** the partial template specialization of <c>std::set<TYPE,CMP,ALLOCATOR></c> 
     *  printout. The vector is printed a'la Python list: "[ a, b, c ]"
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-05-12
     */     
    template<class TYPE,class CMP,class ALLOCATOR> 
    inline std::ostream& toStream 
    ( const std::set<TYPE,CMP,ALLOCATOR>& obj, std::ostream& s)
    {
      s << "[ ";
      for ( typename std::set<TYPE,CMP,ALLOCATOR>::const_iterator cur = obj.begin() ;
            obj.end() != cur ; ++cur )
      {
        if ( obj.begin() != cur ) { s << " , "; }
        toStream ( *cur , s ) ;
      }
      return s << " ]";
    }
    // ========================================================================
    /** the partial template specialization of 
     *  <c>std::map<KTYPE,VTYPE,CMP,ALLOCATOR></c> printout 
     *  the map is printed a'la Python dict: " ( a : b , c: d , e : f )"
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-05-12
     */    
    template<class KTYPE, class VTYPE,class CMP,class ALLOCATOR> 
    inline std::ostream& toStream 
    ( const std::map<KTYPE,VTYPE,CMP,ALLOCATOR>& obj, std::ostream& s )
    {
      s << "{ ";
      for ( typename std::map<KTYPE,VTYPE,CMP,ALLOCATOR>::const_iterator cur = 
              obj.begin() ; obj.end() != cur ; ++cur )
      {
        if ( obj.begin() != cur ) { s << " , " ; }
        toStream ( cur -> first  , s ) ;
        s << " : " ;
        toStream ( cur -> second , s ) ;
      }
      return s << " }";
    } 
    // ========================================================================
    /** the generic implementation of the printout to the std::ostream 
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-05-12
     */
    template<class TYPE> 
    inline std::ostream& toStream ( const TYPE& obj, std::ostream& s )
    { return s << obj ; } 
    
    // ========================================================================
    /** the generic implementation of the type conversion to the string 
     *  @author Alexander MAZUROV Alexander.Mazurov@gmail.com
     *  @author Vanya BELYAEV ibelyaev@physics.syr.edu
     *  @date 2006-05-12
     *  @see Gaudi::Utils::toStream
     *  @todo need to be compared with boost::lexical_cast 
     */
    template <class TYPE> 
    inline std::string   toString ( const TYPE& obj ) 
    {
      std::ostringstream s;
      toStream ( obj , s);
      return s.str();
    }

  } // end of namespace Utils 
} // end of namespace Gaudi 

// ============================================================================
// The END 
// ============================================================================
#endif
// ============================================================================

