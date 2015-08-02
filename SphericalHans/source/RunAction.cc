/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol (hapol@fpddux.usc.es)
//*-- Date: 11/2004
//*-- Last Update: 01/02/07
// --------------------------------------------------------------
// Description:
//   Controls the actions to perform before and after a run.
//
// --------------------------------------------------------------
// Comments:
//   - 30/11/04 Created based on example/novice/N03 structure
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "fstream"
#include "iomanip"

using namespace std;

practicaRunAction::practicaRunAction(){
  //
  // Constructor. Makes nothing
  //

  //Setting some initial values: multichannel range
  range = 12.0*MeV;
}


practicaRunAction::~practicaRunAction(){
  //
  // Destructor
  //
}


void practicaRunAction::BeginOfRunAction(const G4Run* aRun) {
  //
  // Actions to perform at the beginning og the run
  // 

  G4cout << "##################################################################"
	 << G4endl 
	 << "###############   practicaRunAction::BeginOfRunAction()  ##############" 
	 << G4endl
	 << "###    Run " << aRun->GetRunID() << " start." << G4endl;
  G4cout << "##################################################################"
	 << G4endl;
  
  //reseting the multichannel histogram
  for(G4int i=0;i<4096;i++)
    multichannel[i]=0;


  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);

}


void practicaRunAction::EndOfRunAction(const G4Run* aRun) {
  //
  // Actions to perform at the end of the run
  //


  G4int theRunID = aRun->GetRunID();
  char fileName[100];

  //writing the values of the multichannel in an output file
  sprintf(fileName,"%s%i%s%2.2f%s","multi_run",aRun->GetRunID(),"_range_",range,"MeV.dat");
  ofstream outputFile(fileName);

  for(G4int i=0;i<4096;i++)
    outputFile << setw(6) << i << setw(10) << multichannel[i] << G4endl;
      
  outputFile.close();
}


void practicaRunAction::StoreEnergy(G4double energy) {
  //
  // Storing the energy deposited in the detector from each 
  // event in the multichannel array
  //

  G4int bin = (G4int) (4096 * (energy/range));
  if(bin > 4095) bin = 4095;
  multichannel[bin] += 1;
  //G4cout << "bin "<< bin << " adds a count and have " 
  //     <<multichannel[bin] << " counts "<<G4endl;

}
