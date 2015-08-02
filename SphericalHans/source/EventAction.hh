/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Actions to be performed before or after each event
//
// --------------------------------------------------------------
// Comments:
//
//   - 30/11/04 Created based on example/novice/N03 structure
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef __EventAction
#define __EventAction

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "RunAction.hh"

class EventActionMessenger;

class EventAction : public G4UserEventAction {

private: 


  //This variables will store the enegy and the track length 
  //for the tracks deposited in the detector
//  G4double  energyInDetector, trackLInDetector;
    

  G4String  drawFlag;
  G4int     printModulo;

  RunAction*  runAction;
  EventActionMessenger*  eventMessenger;

public:
  EventAction(RunAction*);
  ~EventAction();
  
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

  //this function adds the value of the energy and length of the step
  //in the local variables; it is called from the steps
  void AddDetector(G4double de, G4double dl) {energyInDetector += de;
                                              trackLInDetector += dl;}
  
  void SetDrawFlag   (G4String val)  {drawFlag = val;}
  void SetPrintModulo(G4int    val)  {printModulo = val;}
  void SetRange(G4double    val)     {runAction->SetRange(val);}
  
};

#endif

    
