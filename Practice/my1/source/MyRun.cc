#include "MyRun.hh"

MyRun::MyRun(): G4Run(), _edep(0.), _edep2(0.)
{ }

MyRun::~MyRun()
{ }

void MyRun::Merge( const G4Run* run )
{
    const MyRun* localRun = static_cast<const MyRun*>(run);
    _edep  += localRun->_edep;
    _edep2 += localRun->_edep2;
    
    G4Run::Merge(run);
}

void MyRun::AddEdep ( G4double edep )
{
    _edep  += edep;
    _edep2 += edep*edep;
}

