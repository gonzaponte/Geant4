/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Hector Alvarez-Pol hapol@fpddux.usc.es
//*-- Date: 05/2005
//*-- Last Update:  01/02/07
// --------------------------------------------------------------
// Description:
//   Detector construction and complementary definitions
//
// --------------------------------------------------------------
// Comments:
//
//   - 24/05/05 Created based on calGamma simulation
//
// --------------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "practicaDetectorConstruction.hh"

#include "practicaDetectorMessenger.hh"

#include "G4RotationMatrix.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "globals.hh"


practicaDetectorConstruction::practicaDetectorConstruction()
  :   solidWorld(0), worldLog(0), worldPhys(0),
      mediumMaterial(0), detectorMaterial(0), defaultMaterial(0) {
  //
  // Constructor
  //

  //define material  
  DefineMaterials();

  //A set of materials are here preliminary defined
  SetMediumMaterial("Air");
  SetDetectorMaterial("CsI");

  //initial values; 
  //these are taken if there is no modification using messenger commands
  detectorOuterRadius = 20*mm;
  detectorHalfLengthZ = 50*mm;  

  // create commands for interactive definition of the calorimeter
  detectorMessenger = new practicaDetectorMessenger(this);
}

practicaDetectorConstruction::~practicaDetectorConstruction() {
  delete detectorMessenger;
}

G4VPhysicalVolume* practicaDetectorConstruction::Construct() {
  return ConstructSetup();
}

G4VPhysicalVolume* practicaDetectorConstruction::ConstructSetup() {
  //
  // Geometrical definition of the world and detector volume
  //

  //size of the experimental volume  
  G4double worldSizeX = 1*m;
  G4double worldSizeY = 1*m;
  G4double worldSizeZ = 1*m;
  
  solidWorld = new G4Box("World",                             //its name
			 worldSizeX,worldSizeY,worldSizeZ);   //its size
  
  worldLog = new G4LogicalVolume(solidWorld,          //its solid
				 mediumMaterial,      //its material
				 "World");            //its name
  
  worldPhys = new G4PVPlacement(0,                     //no rotation
				G4ThreeVector(),       //at (0,0,0)
				worldLog,              //its logical volume
				"World",               //its name
				0,                     //its mother  volume
				false,                 //no boolean operation
				0);                    //copy number
  
  
  //////////////////////////////////////////////////////////////////////
  //      DETECTOR:
  //  The detector volume
  //////////////////////////////////////////////////////////////////////

  G4double detectorCenterPosX = 0.*m;
  G4double detectorCenterPosY = 0.*m;
  G4double detectorCenterPosZ = 0.50*m;   //The center of the detector is 0.5m displaced
                                          //with respect to the origin of the world
  
  G4double detectorInnerRadius = 0*mm;
  
  G4Tubs* detectorTube;
  detectorTube = new G4Tubs("detectorTube",
			    detectorInnerRadius,
			    detectorOuterRadius,
			    detectorHalfLengthZ,
			    0,2*pi);
  
  G4LogicalVolume* detectorLog;                         //pointer to logic gas
  detectorLog = new G4LogicalVolume(detectorTube,       
				    detectorMaterial,
				    "detectorLog");
  
  detectorPhys = new G4PVPlacement(0,                                                   //no rotation
				   G4ThreeVector(detectorCenterPosX,                    //position
						 detectorCenterPosY,
						 detectorCenterPosZ),
				   detectorLog,"detectorPhys",worldLog,false,0);
  
  /////////////////////////////////////////////////////////////////////
  //   Add here other volumes if neccessary
  //
  /////////////////////////////////////////////////////////////////////

  //------------------------------------------------------------------ 
  //
  // Visualization attributes
  //
  worldLog->SetVisAttributes (G4VisAttributes::Invisible);
  //colours following the rgb notation
  G4VisAttributes* detectorVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
  detectorLog->SetVisAttributes(detectorVisAtt);
  
  return worldPhys;
}


void practicaDetectorConstruction::PrintDetectorParameters() {
  //
  // Printing the actual values of the detector parameters
  //
  
  //include here the printout of the parameters that could be selected by the messenger
  
}


void practicaDetectorConstruction::SetDetectorMaterial (G4String mat) {
  //
  // Sets the material the detector is made of
  //
  G4Material* pttoMaterial = G4Material::GetMaterial(mat);
  if (pttoMaterial) detectorMaterial = pttoMaterial;
}


void practicaDetectorConstruction::SetMediumMaterial(G4String mat) {
  //
  // Sets the material the medium is made of
  //
  G4Material* pttoMaterial = G4Material::GetMaterial(mat);
  if (pttoMaterial) mediumMaterial = pttoMaterial;
  
}


void practicaDetectorConstruction::UpdateGeometry() {
  //
  //
  //  
  //DefineMaterials();//does not work correctly
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructSetup());
}


void practicaDetectorConstruction::DefineMaterials() { 
  //
  // Define the materials to be used  
  // (NOTE: it results impossible to define externally (via messenger)
  // the density of the gases, because the materials table is an static element
  // which remains constant from creation to the end of the program)
  //

  G4double a;  // atomic mass
  G4double z;  // atomic number
  
  G4Element* H  = new G4Element("Hydrogen" ,"H" , z= 1., a=   1.00794*g/mole);
  G4Element* N  = new G4Element("Nitrogen" ,"N" , z= 7., a=  14.00674*g/mole);
  G4Element* O  = new G4Element("Oxygen"   ,"O" , z= 8., a=   15.9994*g/mole);
  G4Element* Ge = new G4Element("Germanium","Ge", z=32., a=     72.61*g/mole);
  G4Element* Bi = new G4Element("Bismuth"  ,"Bi", z=83., a= 208.98038*g/mole);
  G4Element* Na = new G4Element("Sodium"   ,"Na", z=11., a=  22.98977*g/mole);
  G4Element* I  = new G4Element("Iodine"   ,"I",  z=53., a= 126.90447*g/mole);
  G4Element* Ba = new G4Element("Barium"   ,"Ba", z=56., a=   137.327*g/mole);
  G4Element* F  = new G4Element("Fluorine" ,"F",  z=9.,  a=18.9984032*g/mole);
  G4Element* C  = new G4Element("Carbon"   ,"C",  z=6.,  a=   12.0107*g/mole);
  G4Element* Ce = new G4Element("Cerium"   ,"Ce", z=58., a=   140.116*g/mole);
  G4Element* Cs = new G4Element("Cesium"   ,"Cs", z=55., a= 132.90545*g/mole);
  G4Element* La = new G4Element("Lanthanum","La", z=57., a=  138.9055*g/mole);
  G4Element* Br = new G4Element("Bromine"  ,"Br", z=35., a=    79.904*g/mole);
  G4Element* Lu = new G4Element("Lutecium" ,"Lu", z=71., a=   174.967*g/mole);
  G4Element* S  = new G4Element("Sulphur"  ,"S",  z=16., a=    32.066*g/mole);
  G4Element* Cd = new G4Element("Cadmium"  ,"Cd", z=48., a=   112.411*g/mole);
  G4Element* Zn = new G4Element("Zinc",     "Zn", z=30., a=     65.39*g/mole);
  G4Element* Te = new G4Element("Tellurium","Te", z=52., a=    127.60*g/mole);
  G4Element* W  = new G4Element("Tungsten" ,"W" , z=74., a=    183.84*g/mole);
  G4Element* Pb = new G4Element("Lead"     ,"Pb", z=82., a=    207.20*g/mole);

  //
  // define materials
  //
  G4double density;
  G4int ncomponents, natoms;
  G4double fractionmass;  
  
  G4Material* Vacuum =
    new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
		   kStateGas, 3.e-18*pascal, 2.73*kelvin);
  Vacuum->SetChemicalFormula("NOMATTER");

  //Air (default 1.290*mg/cm3)
  density = 1.290*mg/cm3;
  G4Material* Air = 
    new G4Material("Air", density, ncomponents=2);
  Air->AddElement(N, fractionmass=70.*perCent);
  Air->AddElement(O, fractionmass=30.*perCent);
  
  //Isobutane (default  2.67*mg/cm3 STP)
  density = 2.67*mg/cm3;
  G4Material* isobutane = 
    new G4Material("isoC4H10STP", density, ncomponents=2) ;
  isobutane->AddElement(C,4);
  isobutane->AddElement(H,10);
  
  //Isobutane (default  2.67*mg/cm3 STP)
  density = 2.67*mg/cm3;
  G4Material* isobutane01 = 
    new G4Material("isoC4H10_0.1", 0.001*density, ncomponents=2) ;
  isobutane01->AddElement(C,4);
  isobutane01->AddElement(H,10);

  G4Material* isobutane1 = 
    new G4Material("isoC4H10_1", 0.01*density, ncomponents=2) ;
  isobutane1->AddElement(C,4);
  isobutane1->AddElement(H,10);

  G4Material* isobutane10 = 
    new G4Material("isoC4H10_10", 0.1*density, ncomponents=2) ;
  isobutane10->AddElement(C,4);
  isobutane10->AddElement(H,10);

  G4Material* isobutane50 = 
    new G4Material("isoC4H10_50", 0.5*density, ncomponents=2) ;
  isobutane50->AddElement(C,4);
  isobutane50->AddElement(H,10);

  //Methane (default  0.7174*mg/cm3 STP)
  density = 0.7174*mg/cm3;
  G4Material* methane = 
    new G4Material("CH4", density, ncomponents=2) ;
  methane->AddElement(C,1);
  methane->AddElement(H,4);
  
  //Propane (default  2.005*mg/cm3 STP)
  density = 2.005*mg/cm3;
  G4Material* propane = 
    new G4Material("C3H8", density, ncomponents=2) ;
  propane->AddElement(C,3);
  propane->AddElement(H,8); 

  //Benzene (default  0.8786*g/cm3 STP)
  density = 0.8786*g/cm3;
  G4Material* benzene = 
    new G4Material("C6H6", density, ncomponents=2) ;
  benzene->AddElement(C,6);
  benzene->AddElement(H,6); 


  G4Material* H2O = 
    new G4Material("Water", density= 1.000*g/cm3, ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  H2O->SetChemicalFormula("H_2O");
  H2O->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);
  
  G4Material* BGO = 
    new G4Material("BGO", density= 7.10*g/cm3, ncomponents=3);
  BGO->AddElement(O , natoms=12);
  BGO->AddElement(Ge, natoms= 3);
  BGO->AddElement(Bi, natoms= 4);  
  
  G4Material* SodiumIodine = 
    new G4Material("NaI",density= 3.67*g/cm3,ncomponents=2);
  SodiumIodine->AddElement(Na , natoms=1);
  SodiumIodine->AddElement(I , natoms=1);

  G4Material* BariumFluoride = 
    new G4Material("BaF",density= 4.89*g/cm3,ncomponents=2);
  BariumFluoride->AddElement(Ba , natoms=1);
  BariumFluoride->AddElement(F , natoms=2);

  G4Material*  CesiumIodine= 
    new G4Material("CsI",density= 4.51*g/cm3,ncomponents=2);
  CesiumIodine->AddElement(Cs, natoms=1);
  CesiumIodine->AddElement(I, natoms=1);
  
  G4Material* CeriumFluoride = 
    new G4Material("CeF3",density= 6.16*g/cm3,ncomponents=2);
  CeriumFluoride->AddElement(Ce , natoms=1);
  CeriumFluoride->AddElement(F , natoms=3);
  
  G4Material* LantanumBromide = 
    new G4Material("LaBr3",density= 5.29*g/cm3,ncomponents=2);
  LantanumBromide->AddElement(La , natoms=1);
  LantanumBromide->AddElement(Br , natoms=3);
  
  G4Material*  LSO= 
    new G4Material("LSO",density= 7.4*g/cm3,ncomponents=3);
  LSO->AddElement(Lu , natoms=2);
  LSO->AddElement(S , natoms=1);
  LSO->AddElement(O , natoms=5);

  G4Material* CdZnTe=
    new G4Material("CdZnTe",density= 5.78*g/cm3 ,ncomponents=3);
  CdZnTe->AddElement(Cd, natoms=9);
  CdZnTe->AddElement(Zn, natoms=1);
  CdZnTe->AddElement(Te, natoms=10);

  G4Material* PWO=
    new G4Material("PWO",density= 8.28*g/cm3 ,ncomponents=3);
  PWO->AddElement(Pb, natoms=1);
  PWO->AddElement(W, natoms=1);
  PWO->AddElement(O, natoms=4);

  // Deuterium at 0.1 atm
  G4Material* Deuterium = 
    new G4Material("Deuterium", density= 0.0169*g/cm3, ncomponents=2);
  Deuterium->AddElement(H, natoms=1);
  Deuterium->AddElement(H, natoms=1);
  
  
  new G4Material("Silicon"    , z=14., a= 28.09*g/mole, density= 2.330*g/cm3);

  new G4Material("Germanium"  , z=32., a= 72.61*g/mole, density= 5.323*g/cm3);

  new G4Material("Iron"       , z=26., a= 55.85*g/mole, density= 7.870*g/cm3);

  new G4Material("Tungsten"   , z=74., a=183.85*g/mole, density= 19.30*g/cm3);

  new G4Material("Lead"       , z=82., a=207.19*g/mole, density= 11.35*g/cm3);

  new G4Material("Uranium"    , z=92., a=238.03*g/mole, density= 18.95*g/cm3);
  
  //
  //meterials printout 
  //
  //  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  
  //default materials of the World
  defaultMaterial  = Vacuum;
}






