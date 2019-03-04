/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of SCA-JTNC core.
 * 
 * SCA-JTNC core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */


#ifndef DEVICE_IMPL_H
#define DEVICE_IMPL_H

#include <signal.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "CF/DeviceComponent.h"
#include "CF/CFFullComponentRegistry.h"
#include "sca/CorbaUtils.h"
#include "sca/scaSupport.h"
#include "sca/UsesPort.h"
#include "sca/PropertySet_impl.h"
#include "sca/ThreadedComponent.h"
#include "sca/Port_impl.h"

#ifndef ENABLE_LOGGING
#define ENABLE_LOGGING /* */
#define PREPARE_LOGGING(X)  /* X */
#define LOG_DEBUG(X,Y)  /* X,Y */
#endif

class DeviceComponent;

class DeviceComponent: public virtual POA_CF::DeviceComponent, public PropertySet_impl
{
public:

    DeviceComponent (char*, char*, char*, char*);
    DeviceComponent (char*, char*, char*, char*, char*);
    DeviceComponent (char*, char*, char*, char*, CF::Properties);
    DeviceComponent (char*, char*, char*, char*, CF::Properties, char*);
    ~DeviceComponent ();

    char* identifier () throw (CORBA::SystemException);
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
    CF::AggregateDevice_ptr compositeDevice();
    void adminState (CF::AdministratableInterface::AdminType _adminType);
    void addPort (const std::string& name, PortBase* servant);
    void addPort (const std::string& name, const std::string& description, PortBase* servant);
    void insertPort (const std::string& name, PortBase* servant);
    void deactivatePort (PortBase* servant);
    void setUsageState (CF::CapacityManagement::UsageType newUsageState);
    void setAdminState (CF::AdministratableInterface::AdminType new_adminState);

    bool isLocked();
    bool isDisabled ();
    bool isBusy ();
    bool isIdle ();

    void setExecparamProperties(std::map<std::string, char*>&);
    virtual void  postConstruction( std::string &registrar_ior);
    
    template<class T>
    static void start_device(T** devPtr, struct sigaction sa, int argc, char* argv[]) {
        start_device(boost::bind(&DeviceComponent::make_device<T>,boost::ref(*devPtr),_1,_2,_3,_4), sa, argc, argv);
    }
    template<class T>
    static void start_lib_device(T** devPtr, struct sigaction sa, int argc, char* argv[]) {
        start_lib_device(boost::bind(&DeviceComponent::make_device<T>,boost::ref(*devPtr),_1,_2,_3,_4), sa, argc, argv);
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
    std::string compDev_ior;
    omni_mutex component_running_mutex;
    omni_condition component_running;
    CF::ComponentRegistry_ptr _deviceManagerRegistry;
    CF::FullComponentRegistry_ptr _deviceManagerFullRegistry;
    CF::CapacityManagement::UsageType _usageState;
    CF::AdministratableInterface::AdminType _adminState;
    CF::AggregateDevice_ptr _aggregateDevice;

private:
    template <class T>
    static DeviceComponent* make_device(T*& device, char* devMgrIOR, char* identifier, char* profile, char* compositeDeviceIOR)
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

    typedef boost::function<DeviceComponent* (char*, char*, char*, char*)> ctor_type;
    static void start_device(ctor_type ctor, struct sigaction sa, int argc, char* argv[]);

    DeviceComponent(); // Code that tries to use this constructor will not work
    DeviceComponent(DeviceComponent&); // No copying

public:
    static void start_lib_device(ctor_type ctor, struct sigaction sa, int argc, char* argv[]);

};


#endif

