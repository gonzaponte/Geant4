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
//   - 03/12/04: based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaDetectorMessenger.hh"
#include "practicaDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithoutParameter.hh"


practicaDetectorMessenger::
practicaDetectorMessenger(practicaDetectorConstruction* practicaDet)
  :practicaDetector(practicaDet) { 
  //
  // Constructor with fully functionality
  //
  practicaDir = new G4UIdirectory("/practica/");
  practicaDir->SetGuidance("UI commands of practica program");
  
  detDir = new G4UIdirectory("/practica/det/");
  detDir->SetGuidance("Detector control");
  
  mediumMaterCmd = new G4UIcmdWithAString("/practica/det/setMediumMat",this);
  mediumMaterCmd->SetGuidance("Select Material of the Medium.");
  mediumMaterCmd->SetParameterName("mediumMat",false);
  mediumMaterCmd->SetDefaultValue("Air");
  mediumMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  detectorMaterCmd = new G4UIcmdWithAString("/practica/det/setDetectorMat",this);
  detectorMaterCmd->SetGuidance("Select Material of the Detector.");
  detectorMaterCmd->SetParameterName("detectorMat",false);
  detectorMaterCmd->SetDefaultValue("CsI");
  detectorMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  detectorOuterRadiusCmd = new G4UIcmdWithADoubleAndUnit("/practica/det/setDetectorOuterRadius",this);
  detectorOuterRadiusCmd->SetGuidance("Select the external radius of the Detector Tube.");
  detectorOuterRadiusCmd->SetParameterName("radiusDetectorTub",false); 
  detectorOuterRadiusCmd->SetRange("radiusDetectorTub>=0.");
  detectorOuterRadiusCmd->SetUnitCategory("Length");
  detectorOuterRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  detectorHalfLengthZCmd = new G4UIcmdWithADoubleAndUnit("/practica/det/setDetectorHalfLengthZ",this);
  detectorHalfLengthZCmd->SetGuidance("Select the halfLength of the Detector Tube.");
  detectorHalfLengthZCmd->SetParameterName("halfLengthDetectorTub",false); 
  detectorHalfLengthZCmd->SetRange("halfLengthDetectorTub>=0.");
  detectorHalfLengthZCmd->SetUnitCategory("HalfLength");
  detectorHalfLengthZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  updateCmd = new G4UIcmdWithoutParameter("/practica/det/update",this);
  updateCmd->SetGuidance("Update geometry.");
  updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  updateCmd->SetGuidance("if you changed geometrical value(s).");
  updateCmd->AvailableForStates(G4State_Idle);
  
  printCmd = new G4UIcmdWithoutParameter("/practica/det/print",this);
  printCmd->SetGuidance("Prints geometry.");
  printCmd->AvailableForStates(G4State_Idle);
  
}


practicaDetectorMessenger::~practicaDetectorMessenger() {
  //
  // Destructor
  //
  delete practicaDir;
  delete detDir;
  delete detectorMaterCmd;
  delete detectorOuterRadiusCmd;
  delete detectorHalfLengthZCmd;
  delete mediumMaterCmd;  
  delete updateCmd;
  delete printCmd;
}


void practicaDetectorMessenger::SetNewValue(G4UIcommand* command,
					    G4String newValue) {
  //
  // Setting the new values and connecting to detector constructor
  //
 
  if(command == detectorMaterCmd)
    practicaDetector->SetDetectorMaterial(newValue);

  if(command == mediumMaterCmd)
    practicaDetector->SetMediumMaterial(newValue);
  
  if(command == detectorOuterRadiusCmd)
    practicaDetector->SetDetectorOuterRadius(detectorOuterRadiusCmd->GetNewDoubleValue(newValue));

  if(command == detectorHalfLengthZCmd)
    practicaDetector->SetDetectorHalfLengthZ(detectorHalfLengthZCmd->GetNewDoubleValue(newValue));

  if( command == updateCmd ) { 
    practicaDetector->UpdateGeometry(); 
    practicaDetector->PrintDetectorParameters();
  }

  if( command == printCmd )
    { practicaDetector->PrintDetectorParameters(); }
}

