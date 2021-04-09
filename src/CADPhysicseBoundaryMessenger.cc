// CADPhysicsIonBoundaryMessenger.cc
//

#include "CADPhysicseBoundaryMessenger.hh"
#include "CADPhysicseBoundary.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"

CADPhysicseBoundaryMessenger::CADPhysicseBoundaryMessenger(CADPhysicseBoundary * mpga)
:target(mpga)
{
	IBDir = new G4UIdirectory("/process/eboundary/");
	IBDir->SetGuidance("Controls for the CADPhysicseBoundary process.");

	quantumReflectCmd = new G4UIcmdWithABool("/process/eboundary/quantumReflect",this);
	quantumReflectCmd->SetGuidance("Set the reflection coefficient to quantum (true) or classical (false)");
	quantumReflectCmd->SetParameterName("quantumReflect",true);
	quantumReflectCmd->SetDefaultValue(true);
	surfaceReflectCmd = new G4UIcmdWithABool("/process/eboundary/surfaceReflect",this);
	surfaceReflectCmd->SetGuidance("Set the surface reflection on (true) or off (false)");
	
	surfaceReflectCmd->SetParameterName("surfaceReflect",true);
	surfaceReflectCmd->SetDefaultValue(true);
}

CADPhysicseBoundaryMessenger::~CADPhysicseBoundaryMessenger()
{
	delete IBDir;
	delete quantumReflectCmd;
	delete surfaceReflectCmd;
}

void CADPhysicseBoundaryMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
	if( command==surfaceReflectCmd )
	{ target->SetSurfaceReflect(surfaceReflectCmd->GetNewBoolValue(newValue)); }

	if( command==quantumReflectCmd )
	{ target->SetQuantumReflect(quantumReflectCmd->GetNewBoolValue(newValue)); }
}

G4String CADPhysicseBoundaryMessenger::GetCurrentValue(G4UIcommand * command)
{
	// Print the current value of gamma (call by entering '?process/ionboundary/gamma' from the commmand line)
	G4String cv;
	if( command==quantumReflectCmd )
	{ cv = quantumReflectCmd->ConvertToString(target->GetQuantumReflect()); }
	if( command==surfaceReflectCmd )
	{ cv = surfaceReflectCmd->ConvertToString(target->GetSurfaceReflect()); }
	return cv;
}
