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


#ifndef RESOURCECOMPONENT_H
#define RESOURCECOMPONENT_H

#include <string>
#include <map>
#include "CF/Component.h"
#include "CF/CFFullComponentRegistry.h"
#include "sca/CorbaUtils.h"
#include "sca/scaSupport.h"
#include "sca/UsesPort.h"
#include "sca/PropertySet_impl.h"
#include "sca/ThreadedComponent.h"
#include "sca/Port_impl.h"
#include "sca/prop_helpers.h"
#include "sca/PropertyMap.h"

class ResourceComponent: 
    public virtual POA_CF::ResourceComponent, public PropertySet_impl
{
public:
    template<class T>
    static void start_component(T*& component, int argc, char* argv[]) {
        // Initialize the component pointer to quiet warnings--it's not obvious
        // to the compiler that it eventually gets set before being read
        component = 0;

        // Bind the constructor adapter make_component() with the template type
        // and the component argument (explicitly by reference, so that the
        // caller gets the updated value) and pass along to the real
        // implementation
        start_component(boost::bind(&ResourceComponent::make_component<T>,boost::ref(component),_1,_2), argc, argv);
    }

    virtual ~ResourceComponent ();
    ResourceComponent (const char* _uuid);
    ResourceComponent (const char* _uuid, const char *label);

    /*
     * REDHAWK constructor. All properties are initialized before this constructor is called
     */
    virtual void constructor ();

    void setParentId( const std::string &parentid ) { _parent_id = parentid; };

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
    
    virtual void run ();
    virtual void halt ();
    
    virtual void setCurrentWorkingDirectory(std::string& cwd);
    virtual std::string& getCurrentWorkingDirectory();
    
    virtual void setAdditionalParameters(std::string &softwareProfile, std::string &application_registrar_ior, std::string &nic);

    /*
     * Register a function for notification when this Resource is released
     */
    template <class Func>
    void addReleaseListener(Func func)
    {
        _resourceReleased.add(func);
    }

    /*
     * Register a member function for notification when this Resource is released
     */
    template <class Target, class Func>
    void addReleaseListener(Target target, Func func)
    {
        _resourceReleased.add(target, func);
    }

    const std::string& getIdentifier() const;

    /*
     * Globally unique identifier for this Resource
     */
    std::string _identifier;
    /*
     * Name used to bind this Resource to the Naming Service
     */
    std::string naming_service_name;
    std::string _parent_id;

protected:
    virtual void setCommandLineProperty(const std::string& id, const sca::Value& value);

    const std::string& getDeploymentRoot() const;

    typedef std::map<std::string, PortBase*> PortServantMap;
    PortServantMap _portServants;
    
    /*
     * Boolean describing whether or not this Resource is started
     */
    bool _started;
    /*
     * Filename for the Resource's SPD file
     */
    std::string _softwareProfile;
    
    omni_mutex component_running_mutex;
    omni_condition component_running;

private:
    ResourceComponent(); // No default constructor
    ResourceComponent(ResourceComponent&);  // No copying

    // Adapter template function for component constructors. This is the only
    // part of component creation that requires type-specific knowledge.
    template <class T>
    static ResourceComponent* make_component(T*& component, const std::string& identifier, const std::string& name)
    {
        component = new T(identifier.c_str(), name.c_str());
        return component;
    }

    // Generic implementation of start_component, taking a function pointer to
    // a component constructor (via make_component).
    typedef boost::function<ResourceComponent* (const std::string&, const std::string&)> ctor_type;
    static void start_component(ctor_type ctor, int argc, char* argv[]);
    std::string currentWorkingDirectory;
    bool _initialized;
    std::string _deploymentRoot;

    sca::notification<void (ResourceComponent*)> _resourceReleased;

public:
    static ResourceComponent* create_component(ctor_type, const CF::Properties& parameters);
};
#endif
