// CADPhysicsIonBoundaryMessenger.hh
//

#ifndef CADPhysicseBoundaryMessenger_h
#define CADPhysicseBoundaryMessenger_h 1

class CADPhysicseBoundary;
class G4UIdirectory;
class G4UIcmdWithABool;

#include "G4UImessenger.hh"
#include "globals.hh"

class CADPhysicseBoundaryMessenger: public G4UImessenger
{
public:
	CADPhysicseBoundaryMessenger(CADPhysicseBoundary* mpga);
	~CADPhysicseBoundaryMessenger();

	void SetNewValue(G4UIcommand * command,G4String newValues);
	G4String GetCurrentValue(G4UIcommand * command);

private:
	CADPhysicseBoundary* target;

	G4UIdirectory*          IBDir;

	// The only user command
//	G4UIcmdWithADouble*		reflectCmd;
	G4UIcmdWithABool*		quantumReflectCmd;
	G4UIcmdWithABool*		surfaceReflectCmd;
};

#endif
