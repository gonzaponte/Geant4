#include "MyRunAction.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyDetectorConstruction.hh"
#include "MyRun.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"

MyRunAction::MyRunAction() : G4UserRunAction()
{ }

MyRunAction::~MyRunAction()
{ }

G4Run* MyRunAction::GenerateRun()
{
    return new MyRun;
}

void MyRunAction::BeginOfRunAction( const G4Run* )
{
    //inform the runManager to save random number seed
    //G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void MyRunAction::EndOfRunAction( const G4Run* run )
{
    G4int nEvents = run->GetNumberOfEvent();
    if ( !nEvents ) return;
    
    const MyRun* Run = static_cast<const MyRun*>(run);
    
    G4double edep  = Run->GetEdep();
    G4double edep2 = Run->GetEdep2();
    G4double rms = edep2 - edep*edep/nEvents;
    if  (rms > 0.) rms = std::sqrt(rms);
    else rms = 0.;
    
//    const MyDetectorConstruction* detectorConstruction
//    = static_cast<const MyDetectorConstruction*>
//    ( G4RunManager::GetRunManager()->GetUserDetectorConstruction() );
//    G4double mass = detectorConstruction->GetScoringVolume()->GetMass();
//    G4double dose = edep/mass;
//    G4double rmsDose = rms/mass;
    
    // Run conditions
    //  note: There is no primary generator action object for "master"
    //        run manager for multi-threaded mode.
    const MyPrimaryGeneratorAction* generatorAction
    = static_cast<const MyPrimaryGeneratorAction*>
    (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    
    G4String runCondition;
    if (generatorAction)
    {
        const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
        runCondition += particleGun->GetParticleDefinition()->GetParticleName();
        runCondition += " of ";
        G4double particleEnergy = particleGun->GetParticleEnergy();
        runCondition += G4BestUnit(particleEnergy,"Energy");
    }
    
    // Print
    //
    if (IsMaster()) {
        G4cout << G4endl
        << "--------------------End of Global Run-----------------------";
    }
    else {
        G4cout << G4endl
        << "--------------------End of Local Run------------------------";
    }
    
    G4cout  << G4endl
    << " The run consists of " << nEvents << " " << runCondition << G4endl
    << "------------------------------------------------------------"
    << G4endl << G4endl;
}


