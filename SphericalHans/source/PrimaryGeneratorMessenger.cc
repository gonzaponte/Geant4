/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol  hapol@fpddux.usc.es
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
//*-- modified by:
// --------------------------------------------------------------
// Description:
//   Messenger for the primary event generator.
//
// --------------------------------------------------------------
// Comments:
//   - 03/12/04: based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaPrimaryGeneratorMessenger.hh"

#include "practicaPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3Vector.hh"      
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4Ions.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

practicaPrimaryGeneratorMessenger::practicaPrimaryGeneratorMessenger(practicaPrimaryGeneratorAction* actarSimGun)
  : actarSimActionGun(actarSimGun) {
  //
  // Constructor including commands definition
  //
  particleTable = G4ParticleTable::GetParticleTable();

  G4bool omitable;
  G4UIparameter* parameter;

  gunDir = new G4UIdirectory("/practica/gun/");
  gunDir->SetGuidance("PrimaryGenerator control");
  
  listCmd = new G4UIcmdWithoutParameter("/practica/gun/List",this);
  listCmd->SetGuidance("List available particles.");
  listCmd->SetGuidance(" Invoke G4ParticleTable.");
  
  particleCmd = new G4UIcmdWithAString("/practica/gun/particle",this);
  particleCmd->SetGuidance("Select the incident particle.");
  particleCmd->SetGuidance(" (proton is default)");
  particleCmd->SetGuidance(" (ion can be specified for shooting ions)");
  particleCmd->SetParameterName("particle",false);
  particleCmd->SetDefaultValue("proton");
  G4String candidateList;
  G4int nPtcl = particleTable->entries();
  for(G4int i=0;i<nPtcl;i++) {
    if(!(particleTable->GetParticle(i)->IsShortLived())) {
      candidateList += particleTable->GetParticleName(i);
      candidateList += " ";
    }
  }
  candidateList += "ion ";
  particleCmd->SetCandidates(candidateList);

  flatDistributionCmd = new G4UIcmdWithAString("/practica/gun/flatDistribution",this);
  flatDistributionCmd->SetGuidance("Simulates beam shape.");
  flatDistributionCmd->SetGuidance("  Choice : on, off(default)");
  flatDistributionCmd->SetParameterName("choice",true);
  flatDistributionCmd->SetDefaultValue("off");
  flatDistributionCmd->SetCandidates("on off");
  flatDistributionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  //commands affecting individual particles 
  energyCmd  = new G4UIcmdWithADoubleAndUnit("/practica/gun/energy",this);
  energyCmd->SetGuidance("Sets the kinetic energy of the primary particle");
  energyCmd->SetParameterName("energy",false);
  energyCmd->SetRange("energy>=0.");
  energyCmd->SetUnitCategory("Energy"); 
  energyCmd->SetDefaultValue(20.);
  energyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  directionCmd = new G4UIcmdWith3Vector("/practica/gun/direction",this);
  directionCmd->SetGuidance("Set momentum direction.");
  directionCmd->SetGuidance("Direction needs not to be a unit vector.");
  directionCmd->SetParameterName("Px","Py","Pz",true,true); 
  directionCmd->SetRange("Px != 0 || Py != 0 || Pz != 0");
  
  positionCmd = new G4UIcmdWith3VectorAndUnit("/practica/gun/position",this);
  positionCmd->SetGuidance("Set starting position of the particle.");
  positionCmd->SetParameterName("X","Y","Z",true,true);
  positionCmd->SetDefaultUnit("cm");
  //positionCmd->SetUnitCategory("Length");
  //positionCmd->SetUnitCandidates("microm mm cm m km");

  timeCmd = new G4UIcmdWithADoubleAndUnit("/practica/gun/time",this);
  timeCmd->SetGuidance("Set initial time of the particle.");
  timeCmd->SetParameterName("t0",true,true);
  timeCmd->SetDefaultUnit("ns");
  //timeCmd->SetUnitCategory("Time");
  //timeCmd->SetUnitCandidates("ns ms s");
  
  polCmd = new G4UIcmdWith3Vector("/practica/gun/polarization",this);
  polCmd->SetGuidance("Set polarization.");
  polCmd->SetParameterName("Px","Py","Pz",true,true); 
  polCmd->SetRange("Px>=-1.&&Px<=1.&&Py>=-1.&&Py<=1.&&Pz>=-1.&&Pz<=1.");

  numberCmd = new G4UIcmdWithAnInteger("/practica/gun/number",this);
  numberCmd->SetGuidance("Set number of particles to be generated.");
  numberCmd->SetParameterName("N",true,true);
  numberCmd->SetRange("N>0");

  ionCmd = new G4UIcommand("/practica/gun/ion",this);
  ionCmd->SetGuidance("Set properties of ion to be generated.");
  ionCmd->SetGuidance("[usage] /practica/gun/ion Z A Q E");
  ionCmd->SetGuidance("        Z:(int) AtomicNumber");
  ionCmd->SetGuidance("        A:(int) AtomicMass");
  ionCmd->SetGuidance("        Q:(int) Charge of Ion (in unit of e)");
  ionCmd->SetGuidance("        E:(double) Excitation energy (in keV)");
  
  G4UIparameter* param;
  param = new G4UIparameter("Z",'i',false);
  param->SetDefaultValue("1");
  ionCmd->SetParameter(param);
  param = new G4UIparameter("A",'i',false);
  param->SetDefaultValue("1");
  ionCmd->SetParameter(param);
  param = new G4UIparameter("Q",'i',true);
  param->SetDefaultValue("0");
  ionCmd->SetParameter(param);
  param = new G4UIparameter("E",'d',true);
  param->SetDefaultValue("0.0");
  ionCmd->SetParameter(param);
  
}

practicaPrimaryGeneratorMessenger::~practicaPrimaryGeneratorMessenger() {
  //
  // Destructor  
  //
  delete gunDir;
  delete listCmd;
  delete particleCmd;
  delete energyCmd;  
  delete directionCmd;  
  delete positionCmd;
  delete timeCmd;
  delete polCmd;
  delete numberCmd;
  delete ionCmd;  
  delete flatDistributionCmd; 
}

void practicaPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, 
						    G4String newValues) { 
  //
  // Setting the values from the interface
  // 
  if( command==listCmd )
    particleTable->DumpTable();
  
  if( command == particleCmd ) {
    if (newValues =="ion") {
      fShootIon = true;
    } else {
      fShootIon = false;
      G4ParticleDefinition* pd = particleTable->FindParticle(newValues);
      if(pd != 0)
	{ actarSimActionGun->SetParticleDefinition( pd ); }
    }
  }
  
  if( command == flatDistributionCmd )
    actarSimActionGun->SetFlatDistributionFlag(newValues);  
  
  if( command == energyCmd )
    actarSimActionGun->SetParticleEnergy(energyCmd->GetNewDoubleValue(newValues));

  if( command==directionCmd )
    actarSimActionGun->SetParticleMomentumDirection(directionCmd->GetNew3VectorValue(newValues)); 
  
  if( command==positionCmd )
    actarSimActionGun->SetParticlePosition(positionCmd->GetNew3VectorValue(newValues));

  if( command==timeCmd )
    actarSimActionGun->SetParticleTime(timeCmd->GetNewDoubleValue(newValues)); 
  
  if( command==polCmd )
    actarSimActionGun->SetParticlePolarization(polCmd->GetNew3VectorValue(newValues)); 

  if( command==numberCmd )
    actarSimActionGun->SetNumberOfParticles(numberCmd->GetNewIntValue(newValues));

  if( command==ionCmd )
    IonCommand(newValues); 
}


G4String practicaPrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==directionCmd )
  { cv = directionCmd->ConvertToString(actarSimActionGun->GetParticleMomentumDirection()); }
  else if( command==particleCmd )
  { cv = actarSimActionGun->GetParticleDefinition()->GetParticleName(); }
  else if( command==energyCmd )
  { cv = energyCmd->ConvertToString(actarSimActionGun->GetParticleEnergy(),"GeV"); }
  else if( command==positionCmd )
  { cv = positionCmd->ConvertToString(actarSimActionGun->GetParticlePosition(),"cm"); }
  else if( command==timeCmd )
  { cv = timeCmd->ConvertToString(actarSimActionGun->GetParticleTime(),"ns"); }
  else if( command==polCmd )
  { cv = polCmd->ConvertToString(actarSimActionGun->GetParticlePolarization()); }
  else if( command==numberCmd )
  { cv = numberCmd->ConvertToString(actarSimActionGun->GetNumberOfParticles()); }
  else if( command==ionCmd )
  { 
    if (fShootIon) {
      cv = ItoS(fAtomicNumber) + " " + ItoS(fAtomicMass) + " ";
      cv += ItoS(fIonCharge);
    } else {
      cv = "";
    }  
  }    
  return cv;
}


void practicaPrimaryGeneratorMessenger::IonCommand(G4String newValues) {
  //
  // Particular behavior of the ion command. Ion state should be selected.
  //
  if (fShootIon) {
    G4Tokenizer next( newValues );
    // check argument
    fAtomicNumber = StoI(next());
    fAtomicMass = StoI(next());
    G4String sQ = next();
    if (sQ.isNull()) {
      fIonCharge = fAtomicNumber;
    } else {
	fIonCharge = StoI(sQ);
      sQ = next();
      if (sQ.isNull()) {
        fIonExciteEnergy = 0.0;
      } else {
        fIonExciteEnergy = StoD(sQ) * keV;
      }
    }

    G4ParticleDefinition* ion;
    ion =  particleTable->GetIon( fAtomicNumber, fAtomicMass, fIonExciteEnergy);
    if (ion==0) {
      G4cout << "##################################################################"
	     << G4endl
	     << "#######   practicaPrimaryGeneratorMessenger::IonCommand()  #######" 
	     << "Ion with Z=" << fAtomicNumber
	     << " A=" << fAtomicMass << "can not be defined" << G4endl;
      G4cout << "##################################################################"
	     << G4endl;
    } else {
      actarSimActionGun->SetParticleDefinition(ion);
      actarSimActionGun->SetParticleCharge(fIonCharge*eplus);
    }
  } else {
    G4cout << "##################################################################"
	   << G4endl
	   << "#######   practicaPrimaryGeneratorMessenger::IonCommand()  #######"
	   << "Set /gun/particle to ion before using /gun/ion command" << G4endl;
    G4cout << "##################################################################"
	   << G4endl; 
  }
}


