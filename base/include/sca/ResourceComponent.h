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


#ifndef RESOURCE_COMPONENT_H
#define RESOURCE_COMPONENT_H

#include <signal.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "CF/ResourceComponent.h"
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

class ResourceComponent;

class ResourceComponent: public virtual POA_CF::ResourceComponent, public PropertySet_impl
{
public:

    ResourceComponent (char*, char*, char*, char*);
    /*DeviceComponent (char*, char*, char*, char*, char*);
    DeviceComponent (char*, char*, char*, char*, CF::Properties);
    DeviceComponent (char*, char*, char*, char*, CF::Properties, char*);*/
    ~ResourceComponent ();

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
    void addPort (const std::string& name, PortBase* servant);
    void addPort (const std::string& name, const std::string& description, PortBase* servant);
    void insertPort (const std::string& name, PortBase* servant);
    void deactivatePort (PortBase* servant);

    void setExecparamProperties(std::map<std::string, char*>&);
    virtual void  postConstruction( std::string &registrar_ior);
    
    template<class T>
    static void start_component(T** compPtr, struct sigaction sa, int argc, char* argv[]) {
        start_component(boost::bind(&ResourceComponent::make_component<T>,boost::ref(*devPtr),_1,_2,_3,_4), sa, argc, argv);
    }
    template<class T>
    static void start_lib_component(T** devPtr, struct sigaction sa, int argc, char* argv[]) {
        start_lib_component(boost::bind(&ResourceComponent::make_component<T>,boost::ref(*devPtr),_1,_2,_3,_4), sa, argc, argv);
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

private:
    template <class T>
    static ResourceComponent* make_component(T*& component, char* registryIOR, char* identifier, char* profile)
    {
        component = new T(registryIOR, identifier, identifier, profile);
        PortableServer::ObjectId_var oid = sca::corba::RootPOA()->activate_object(device);
        return component;
    }

    typedef boost::function<ResourceComponent* (char*, char*, char*, char*)> ctor_type;
    static void start_component(ctor_type ctor, struct sigaction sa, int argc, char* argv[]);

    ResourceComponent(); // Code that tries to use this constructor will not work
    ResourceComponent(ResourceComponent&); // No copying

public:
    static void start_lib_component(ctor_type ctor, struct sigaction sa, int argc, char* argv[]);

};


#endif

