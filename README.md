
This project contains an implementation of part of the SCA 4.1 specification. It also contains tooling to convert REDHAWK projects into projects that can run with the SCA framework

Several REDHAWK projects are includes in the samples directory (not that each of those projects includes a hidden file that describes the template that the project requires)

To convert each of the projects into an SCA 4.1 project, run:
sca-convert <project directory> <new projects directory>

To generate the project source code, cd into the project directory
sca-codegen Project.spd.xml

To build the project, cd into its cpp directory
./reconf && ./configure && make install

After successfully building and installing the component or device, it will be installed in either $SCAROOT/dev/devices or $SCAROOT/dom/components

To run the components or devices, the Python sandbox is needed. Programmable devices run as separate process; persona devices run as threads in the programmable device; components run as threads in persona executable devices

$ python

\>\>\> from sca.utils import sb

\>\>\> progdev = sb.launch('ProgrammableDevice')

\>\>\> persdev = sb.launch('PersonaDevice', host=progdev)

\>\>\> execdev = sb.launch('PersonaExecutableDevice', host=progdev)

\>\>\> comp = sb.launch('alloc_shm', host=execdev)

