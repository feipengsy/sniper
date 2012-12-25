// $Id: ParserActions.h,v 1.2 2007/05/24 14:41:21 hmd Exp $
// ============================================================================
// CVS tag $Name: GAUDI_v20r4-pre $ 
// ============================================================================
#ifndef JOBOPTIONSSVC_PARSERACTIONS_H 
#define JOBOPTIONSSVC_PARSERACTIONS_H 1
// ============================================================================
// Include files
// ============================================================================
// STD & STL
// ============================================================================
#include <string>
// ============================================================================
// Boost.Spirit.phoenix
// ============================================================================
#include <boost/spirit/phoenix.hpp>
// ============================================================================
// Boost.conversion
// ============================================================================
#include <boost/lexical_cast.hpp>
// ============================================================================
namespace Gaudi
{
  namespace Parsers
  {
    template <class T>
    class PushBackImpl
    {
      T&data;
     public:
      PushBackImpl(T &x):data(x){}
      template <class Arg>
        struct result{
          typedef void type;
        };

      template <class Arg>
        void eval(const Arg &x)const{
        data().push_back(x[phoenix::tuple_index<0>()]);
      }
    };
    template <class T,typename IT>
    class PushBackRefImpl
    {
      T& data;
      IT item;
     public:
      PushBackRefImpl(T &x,IT it):data(x),item(it){}
      template <class Arg>
        struct result{
          typedef void type;
        };

      template <class Arg>
      void eval(const Arg & /*x*/ )const{
        data().push_back(item);
      }
    };

    template <class T>
      class AssignBoolToStringImpl
      {
        T &data;
      public:
        AssignBoolToStringImpl(T &x):data(x){}
        template <class Arg>
          struct result{
            typedef void type;
          };

        template <class Arg>
        void eval(const Arg &x)const{
          data() = x[phoenix::tuple_index<0>()]?"1":"0";
        }
    };

    template <class T>
    inline typename phoenix::actor<PushBackImpl<T> > PushBack(T &x) {
      return PushBackImpl<T> (x);
    }
    template <class T,typename IT>
    inline typename phoenix::actor<PushBackRefImpl<T,IT> > PushBack(T &x,IT it) {
      return PushBackRefImpl<T,IT> (x,it);
    }

    template <class T> inline typename phoenix::actor<AssignBoolToStringImpl<T> > AssignBoolToString(T &x){
      return AssignBoolToStringImpl<T> (x);
    }
  } // end of namespace Parsers
} // end of namespace Gaudi

// ============================================================================
// The END 
// ============================================================================
#endif // JOBOPTIONSSVC_PARSERACTIONS_H
// ============================================================================
