#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "MyDetectorConstruction.hh"
#include "MyPhysicsList.hh"
#include "MyActionInitialization.hh"
#include "QBBC.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main( int argc, char** argv )
{
//    G4UIExecutive* ui = 0;
//    if ( argc == 1 )
//        ui = new G4UIExecutive(argc, argv);

    // construct the default run manager
    G4RunManager* runManager = new G4RunManager;
    
    // set mandatory initialization classes
    runManager->SetUserInitialization(new MyDetectorConstruction);
//    runManager->SetUserInitialization(new MyPhysicsList);    
    G4VModularPhysicsList* physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization( physicsList );
    runManager->SetUserInitialization(new MyActionInitialization);
    
    // initialize G4 kernel
    runManager->Initialize();
    
#ifdef G4VIS_USE
    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
#endif

    // get the pointer to the UI manager and set verbosities
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/run/verbose 1");
    UI->ApplyCommand("/event/verbose 1");
    UI->ApplyCommand("/tracking/verbose 1");
    
    if ( argc == 1 )
    {
#ifdef G4UI_USE
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
        UI->ApplyCommand("/control/execute init_vis.mac");
#else
        UI->ApplyCommand("/control/execute init.mac");
#endif
//        UI->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
#endif
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UI->ApplyCommand( command+fileName );
    }

    
    // start a run
    int numberOfEvent = 3;
    runManager->BeamOn(numberOfEvent);
    
    // job termination
    delete runManager;
    return 0;
}
//
//#ifdef G4VIS_USE
//    // Initialize visualization
//    G4VisManager* visManager = new G4VisExecutive;
//    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
//    // G4VisManager* visManager = new G4VisExecutive("Quiet");
//    visManager->Initialize();
//#endif
//    
//    // Get the pointer to the User Interface manager
//    G4UImanager* UImanager = G4UImanager::GetUIpointer();
//    
//    if (argc!=1) {
//        // batch mode
//        G4String command = "/control/execute ";
//        G4String fileName = argv[1];
//        UImanager->ApplyCommand(command+fileName);
//    }
//    else {
//        // interactive mode : define UI session
//#ifdef G4UI_USE
//        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
//#ifdef G4VIS_USE
//        UImanager->ApplyCommand("/control/execute init_vis.mac");
//#else
//        UImanager->ApplyCommand("/control/execute init.mac");
//#endif
//        ui->SessionStart();
//        delete ui;
//#endif
//    }
//    
//    // Job termination
//    // Free the store: user actions, physics_list and detector_description are
//    // owned and deleted by the run manager, so they should not be deleted
//    // in the main() program !
//    
//#ifdef G4VIS_USE
//    delete visManager;
//#endif
//    delete runManager;
//}
//
