/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of REDHAWK core.
 * 
 * REDHAWK core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */


#ifndef AGGREGATEDEVICE_IMPL_H
#define AGGREGATEDEVICE_IMPL_H

#include <signal.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "CF/AggregateDevices.h"
#include "sca/DeviceComponent.h"
#include "sca/CorbaUtils.h"
#include "sca/scaSupport.h"
#include "sca/UsesPort.h"
#include "sca/PropertySet_impl.h"
#include "sca/Port_impl.h"

#ifndef ENABLE_LOGGING
#define ENABLE_LOGGING /* */
#define PREPARE_LOGGING(X)  /* X */
#define LOG_DEBUG(X,Y)  /* X,Y */
#endif

class AggregateExecutableDeviceComponent;

class AggregateExecutableDeviceComponent: public virtual POA_CF::AggregateExecutableDevice, public DeviceComponent
{
public:

    AggregateExecutableDeviceComponent (char*, char*, char*, char*);
    AggregateExecutableDeviceComponent (char*, char*, char*, char*, char*);
    AggregateExecutableDeviceComponent (char*, char*, char*, char*, CF::Properties capacities);
    AggregateExecutableDeviceComponent (char*, char*, char*, char*, CF::Properties capacities, char *compDev);
    ~AggregateExecutableDeviceComponent ();

    void  unload (const char* fileName) throw (CF::InvalidFileName, CF::InvalidState, CORBA::SystemException);
    void  load (CF::FileSystem_ptr fs, const char* fileName, CF::LoadableInterface::LoadType loadKind)
        throw (CF::LoadableInterface::LoadFail, 
                CF::InvalidFileName, 
                CF::LoadableInterface::InvalidLoadKind,
                CF::InvalidState, 
                CORBA::SystemException);
    void terminate (const CF::ExecutableInterface::ExecutionID_Type &executionId)
        throw (CF::InvalidState, CF::ExecutableInterface::InvalidProcess, CORBA::SystemException)
    {};

    bool hasRunningResources() {
        return false;
    };
    
    CF::ExecutableInterface::ExecutionID_Type* execute (
                        const char*             name, 
                        const CF::Properties&   options, 
                        const CF::Properties&   parameters )
            throw (
                CF::ExecutableInterface::ExecuteFail, 
                CF::InvalidFileName, 
                CF::ExecutableInterface::InvalidOptions, 
                CF::ExecutableInterface::InvalidParameters,
                CF::ExecutableInterface::InvalidFunction, 
                CF::InvalidState, 
                CORBA::SystemException )
    {
        return NULL;
    };

    CF::ObjectSequence* devices ()
    {
        CF::ObjectSequence_var retval = new CF::ObjectSequence();
        
        retval->length(_devices->length());
        for (unsigned int i=0; i<_devices->length(); i++) {
            retval[i] = _devices[i];
        }

        return retval._retn();
    }

    void addDevice(CORBA::Object_ptr associatedDevice, const char* identifier) throw (CF::InvalidObjectReference);
    void removeDevice(const char* identifier) throw (CF::InvalidObjectReference);

    /*char* identifier () throw (CORBA::SystemException);
    CORBA::Boolean started() throw (CORBA::SystemException);
    void start () throw (CF::ControllableInterface::StartError, CORBA::SystemException);
    void stop () throw (CF::ControllableInterface::StopError, CORBA::SystemException);
    void initialize () throw (CF::LifeCycle::InitializeError, CORBA::SystemException);
    void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);
    void connectUsesPorts(const CF::PortAccessor::Connections& portConnections) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException);
    void disconnectPorts(const CF::PortAccessor::Disconnections& portDisconnections) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException);
    void getProvidesPorts(CF::PortAccessor::Connections& portConnections ) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException);
    //void configure (const CF::Properties& configProperties) throw (CF::PropertySet::PartialConfiguration, CF::PropertySet::InvalidConfiguration, CORBA::SystemException);
    //void query (CF::Properties& configProperties) throw (CF::UnknownProperties, CORBA::SystemException);
    void runTest (CORBA::ULong TestID, CF::Properties& testValues) throw (CF::UnknownProperties, CF::TestableInterface::UnknownTest, CORBA::SystemException);
    CF::CapacityManagement::UsageType usageState ()throw (CORBA::SystemException);
    CORBA::Boolean allocateCapacity (const CF::Properties& capacities) throw (CF::InvalidState, CF::CapacityManagement::InvalidCapacity, CORBA::SystemException);
    void deallocateCapacity (const CF::Properties& capacities) throw (CF::InvalidState, CF::CapacityManagement::InvalidCapacity, CORBA::SystemException);
    CF::DeviceAttributes::OperationalType operationalState () throw (CORBA::SystemException);
    CF::AdministratableInterface::AdminType adminState ()throw (CORBA::SystemException);
    void adminState (CF::AdministratableInterface::AdminType _adminType);
    void addPort (const std::string& name, PortBase* servant);
    void addPort (const std::string& name, const std::string& description, PortBase* servant);
    void insertPort (const std::string& name, PortBase* servant);
    void deactivatePort (PortBase* servant);

    void setExecparamProperties(std::map<std::string, char*>&);
    virtual void  postConstruction( std::string &registrar_ior);
    
    template<class T>
    static void start_device(T** devPtr, struct sigaction sa, int argc, char* argv[]) {
        start_device(boost::bind(&DeviceComponent::make_device<T>,boost::ref(*devPtr),_1,_2,_3,_4), sa, argc, argv);
    }
    virtual void run ();
    virtual void halt ();
    void setAdditionalParameters(std::string &registrar_ior);
    std::string profile;

protected:
    typedef std::map<std::string, PortBase*> PortServantMap;
    PortServantMap _portServants;
    bool _started;
    void initializeCommonAttributes(const std::string _id);
    std::string _identifier;
    omni_mutex component_running_mutex;
    omni_condition component_running;
    CF::ComponentRegistry_ptr _deviceManagerRegistry;*/
    
protected:
    CF::ObjectSequence_var _devices;

private:
    template <class T>
    static AggregateExecutableDeviceComponent* make_device(T*& device, char* devMgrIOR, char* identifier, char* profile, char* compositeDeviceIOR)
    {
        if (compositeDeviceIOR) {
            // The AggregateDevice version of the constructor implicitly activates the new device,
            // which may be an unsafe behavior.
            device = new T(devMgrIOR, identifier, identifier, profile, compositeDeviceIOR);
        } else {
            device = new T(devMgrIOR, identifier, identifier, profile);
            PortableServer::ObjectId_var oid = sca::corba::RootPOA()->activate_object(device);
        }
        return device;
    }

    typedef boost::function<AggregateExecutableDeviceComponent* (char*, char*, char*, char*)> ctor_type;
    static void start_device(ctor_type ctor, struct sigaction sa, int argc, char* argv[]);

    AggregateExecutableDeviceComponent(); // Code that tries to use this constructor will not work
    AggregateExecutableDeviceComponent(AggregateExecutableDeviceComponent&); // No copying

};


#endif

