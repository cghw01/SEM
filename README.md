# SEM
Geant4 version of the low-energy electron scattering model.

# Installation
On UNIX systems:
* Make sure you have CMake (3.3 or higher) installed
* Install GDML and Xerces-C (see also the GEANT4 installation manual)
* CLHEP is optional, GEANT4 has its own version included
* Install GEANT4.10.05 patch 01 with GDML and Xerces-C enabled, a detailed description of this process can be found in the GEANT4 installation manual.
* The GEANT4 DATA is also necessary, so be sure to install this during the GEANT4 installation.

Before installation, make sure to run the `geant4.sh` script to setup the right environment variables (this script is placed in the /bin/ in the install directory)

Install the SEM low-energy extension in the usual Geant4 way, by creating a sister directory called SEM-build and change directory into this directory i.e.

    mkdir SEM-build
    cd SEM-build

Now run the cmake command to start the build process
cmake -DGeant4_DIR=~/Geant4/geant4.10.05.p01-install ../SEM

The above cmake command assumes that Geant4 version 10.05.p01 has been placed in the directory ~/Geant4/geant4.10.05.p01-install.
Now you can build the program by typing:

    make

or
    make -jN

where N is the number of processors on your computer. This creates an executable SEM.


# Some preliminaries
As usual with other geant4 programs you need to tell geant4 where the link libraries and data file exist. This can be
done with the command something like (according to where you installed geant4):
source ~/Geant4/geant4.10.05.p01-install/bin/geant4.sh 

after this you need to run the command (from the SEM-build directory)
source cadphysicsbase.sh

This latter command will cause the CADPHYSICS_BASE to point at ../SEM. First, this means that the directories mott and df need to exist in the SEM directory and you should run the SEM program only from the SEM-build directory which has been placed next to the SEM directory.
You might prefer that the CADPHYSICS_BASE environment variable points to an exact directory rather than a relative directory. In this case please edit the cadphysicsbase.sh file so that the export line says something like (according to where you placed the SEM directory) :
export CADPHYSICS_BASE="~/Geant4/SEM/"

# Running a simulation
After the installation, simply execute the following command from the SEM-build directory:
 
    ./run.sh

If the install directory was set to a different directory than the default directory, the environment variable `CADPHYSICS_BASE` has to be set to the install path `INSTALL_DIRECTORY`. In this case the example is started by:

    CADPHYSICS_BASE=INSTALL_DIRECTORY ./run.sh

e.g. in the case of the author, this would be:
    CADPHYSICS_BASE=~/Geant4/geant4.10.05.p01/SEM ./run.sh

This will start a simulation for alumina and a simulation for silicon as can be seen when `run.sh` is opened in a text editor.

# Setting up the simulation parameters
What exactly is simulated can be set in the files present in `Examples/Transmission`(these files also exist in the top directory of SEM). The sample material can be set in `run.sh` as mentioned before.
In `YieldCurve.mac` the following can be set:

The amount of primary particles per energy. In the example this is set to 500 in order to have a quick run:

    /control/alias NPE 500

The detectors can be set directional or not, if they are directional, the direction has to be set.

    /detectors/PlaneR/directional true
    /detectors/PlaneR/direction 0.0 0.0 1.0

In the example, the sample itself is also set as a detector, in this case multiple hits is enabled, so that the particles can be tracked inside the sample:

    /detectors/Sample/multipleHits true

The primary gun is placed in the geometry:

    /gps/pos/centre 0.0 0.0 0.0001 mm

The material of the sample is set to the material given in `run.sh`:

    /detectors/setmaterial LogSample {material}
And at last the energies for which the yield is simulated are set. The energy has to be given in eV:

    /control/foreach mac/energy.mac energy 1250
Note that in the expample only one energy is given, if multiple energies are desired e.g. 500, 1000 and 1500 eV:

    /control/foreach mac/energy.mac energy 500 1000 1500

The simulation geometry is defined in `BulkSample.gdml` and `YieldCurve.gdml`.
In `BulkSample.gdml` first the solids are defined, then the logical volumes are defined using the already defined solids. Then the logical volumes are placed in the `samplecontainer` and the physical volumes are defined.
The geometry in the example consists of a 500 nm thick membrane as sample with two detectors. One detector is placed above the sample, the reflection detector and one detector is placed below the sample, the transmission detector. Note that the top of the sample is at 0.0 on the z-axis, which means the primary gun is positioned above the sample in `YieldCurve.mac`.
In `YieldCurve.gdml` the `samplecontainer` is placed inside the `World` volume and the list of detectors is defined.

In the `mac` directory, two more mac files are present, `Pointsource.mac` and `energy.mac`.
In `Pointsource.mac` the particle source is setup.
`energy.mac` sets up the energy of the gun, not that here the energies from `YieldCurve.mac` are used.
It is also possible to set an energy window of the detectors (commented out in the example)
The output files are also se in `energy.mac`. In the example, the yields of the reflection and transmission detector are set as output as well as the hits for both detectors and the sample.
The hits of the sample can be used to reconstruct all electron tracks. If this is not necessary, the line

    /detectors/Sample/outputHits {directory}/EmissionSample_{material}_{energy}.dat
can be commented out. In this case, the sample can also be removed from the detectorlist in `YieldCurve.mac`.
