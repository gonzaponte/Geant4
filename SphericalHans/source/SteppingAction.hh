/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Controls the actions to perform during the steps. Note
// that unneeded code lines at this point will affect performance.
//
// --------------------------------------------------------------
// Comments:
//   - 30/11/04 Created based on example/novice/N03 structure
//
// --------------------------------------------------------------
//
/////////////////////////////////////////////////////////////////

#ifndef __SteppingAction
#define __SteppingAction

#include "G4UserSteppingAction.hh"

class DetectorBuilder;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction( DetectorBuilder*, EventAction* );
   ~SteppingAction();

    void UserSteppingAction(const G4Step*);
    
  private:
    DetectorBuilder* detector;
    EventAction*     eventaction;
};

#endif
