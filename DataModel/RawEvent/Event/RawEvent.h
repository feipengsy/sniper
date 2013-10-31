
//   **************************************************************************
//   *                                                                        *
//   *                      ! ! ! A T T E N T I O N ! ! !                     *
//   *                                                                        *
//   *  This file was created automatically by XmlObjDesc, please do not      *
//   *  delete it or edit it by hand.                                         *
//   *                                                                        *
//   *  If you want to change this file, first change the corresponding       *
//   *  xml-file and rerun the tools from XmlObjDesc (or run make if you      *
//   *  are using it from inside a Sniper-package).                           *
//   *                                                                        *
//   **************************************************************************

#ifndef SNIPER_RAWEVENT_RAWEVENT_H
#define SNIPER_RAWEVENT_RAWEVENT_H

// Include files
#include "TObject.h"

// Forward declarations

namespace JM 
{

  // Forward declarations

  /** @class RawEvent RawEvent.h
   *
   * Test event 
   *
   * @author liteng
   * created Mon Oct 28 11:53:48 2013
   * 
   */

  class RawEvent: public TObject
  {
  private:

    Int_t  m_Id;       // event sequential id
    double m_TotalMom; // total momentum
  

  protected:



  public:

    /// Default Constructor
    RawEvent() : m_Id(0),
                 m_TotalMom(2.8) {}
  
    /// Default Destructor
    virtual ~RawEvent() {}
  
    /// Retrieve const  
    /// event sequential id
  const Int_t& Id() const;
  
    /// Update  
    /// event sequential id
  void setId(const Int_t& value);
  
    /// Retrieve const  
    /// total momentum
  double TotalMom() const;
  
    /// Update  
    /// total momentum
  void setTotalMom(double value);
  

  ClassDef(RawEvent,1);   //For extensive RTTI(Run Time Type Information) and ROOT object I/O and inspection.
  

  }; // class RawEvent

} // namespace JM;

// -----------------------------------------------------------------------------
// end of class
// -----------------------------------------------------------------------------

// Including forward declarations

inline const Int_t& JM::RawEvent::Id() const 
{
  return m_Id;
}

inline void JM::RawEvent::setId(const Int_t& value) 
{
  m_Id = value;
}

inline double JM::RawEvent::TotalMom() const 
{
  return m_TotalMom;
}

inline void JM::RawEvent::setTotalMom(double value) 
{
  m_TotalMom = value;
}


#endif ///SNIPER_RAWEVENT_RAWEVENT_H
