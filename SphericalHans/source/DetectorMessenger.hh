/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Messenger for the detector construction
//
// --------------------------------------------------------------
// Comments:
//   - 03/12/04 Created based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef __DetectorMessenger
#define __DetectorMessenger

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorBuilder;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWithoutParameter;

class DetectorMessenger: public G4UImessenger
{
private:
  DetectorBuilder*     Detector;
  
  G4UIdirectory*             Dir;
  G4UIdirectory*             detDir;
  G4UIcmdWithAString*        mediumMaterCmd;   
  G4UIcmdWithAString*        detectorMaterCmd;   
  G4UIcmdWithADoubleAndUnit* detectorOuterRadiusCmd;
  G4UIcmdWithADoubleAndUnit* detectorHalfLengthZCmd;
  G4UIcmdWithoutParameter*   updateCmd;
  G4UIcmdWithoutParameter*   printCmd;
  
public:
  DetectorMessenger(DetectorBuilder* );
  ~DetectorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  //G4String GetCurrentValue(G4UIcommand*);
};

#endif

