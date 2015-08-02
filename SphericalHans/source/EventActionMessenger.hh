/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol  hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Messenger for the event actions
//
// --------------------------------------------------------------
// Comments:
//   - 03/12/04 Created based on example/novice/N03 structure
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef __EventActionMessenger
#define __EventActionMessenger

#include "globals.hh"
#include "G4UImessenger.hh"

class EventAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;

class EventActionMessenger: public G4UImessenger
{
public:
  EventActionMessenger(EventAction*);
  ~EventActionMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  EventAction*               eventAction;
  G4UIdirectory*             eventDir;   
  G4UIcmdWithAString*        DrawCmd;
//  G4UIcmdWithADoubleAndUnit* rangeCmd;
//  G4UIcmdWithAnInteger*      PrintCmd; 
};

#endif
