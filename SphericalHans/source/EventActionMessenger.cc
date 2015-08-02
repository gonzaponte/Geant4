/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Messenger for the event actions
//
// --------------------------------------------------------------
// Comments:
//   - 03/12/04: based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaEventActionMessenger.hh"

#include "practicaEventAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "globals.hh"


practicaEventActionMessenger::practicaEventActionMessenger(practicaEventAction* EvAct)
:eventAction(EvAct) {
  //
  // Constructor
  //
  eventDir = new G4UIdirectory("/practica/event/");
  eventDir->SetGuidance("event control");
   
  DrawCmd = new G4UIcmdWithAString("/practica/event/drawTracks",this);
  DrawCmd->SetGuidance("Draw the tracks in the event");
  DrawCmd->SetGuidance("  Choice : none, charged, neutral, all(default)");
  DrawCmd->SetParameterName("choice",true);
  DrawCmd->SetDefaultValue("all");
  DrawCmd->SetCandidates("none charged neutral all");
  DrawCmd->AvailableForStates(G4State_Idle);

  rangeCmd = new G4UIcmdWithADoubleAndUnit("/practica/event/SetMultichannelRange",this);
  rangeCmd->SetGuidance("Sets the range of the multichannel");
  rangeCmd->SetParameterName("range",false);
  rangeCmd->SetUnitCategory("Energy");
  rangeCmd->SetRange("range>0.");
  rangeCmd->AvailableForStates(G4State_Idle);

  PrintCmd = new G4UIcmdWithAnInteger("/practica/event/printModulo",this);
  PrintCmd->SetGuidance("Print events modulo n");
  PrintCmd->SetParameterName("EventNb",false);
  PrintCmd->SetRange("EventNb>0");
  PrintCmd->AvailableForStates(G4State_Idle); 
}


practicaEventActionMessenger::~practicaEventActionMessenger() {
  //
  // Destructor
  //
  delete DrawCmd;
  delete PrintCmd;
  delete rangeCmd;
  delete eventDir;   
}


void practicaEventActionMessenger::SetNewValue(
                                        G4UIcommand* command,G4String newValue) {
  //
  // Setting the values from the interfaces
  // 
  if(command == DrawCmd)
    {eventAction->SetDrawFlag(newValue);}  

  if(command == rangeCmd)
    {eventAction->SetRange(rangeCmd->GetNewDoubleValue(newValue));}
       
  if(command == PrintCmd)
    {eventAction->SetPrintModulo(PrintCmd->GetNewIntValue(newValue));}
       
}

