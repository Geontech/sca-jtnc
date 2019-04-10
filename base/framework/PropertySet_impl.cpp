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


#include <iostream>

#include "sca/ThreadedComponent.h"
#include "sca/PropertySet_impl.h"
#include "sca/CorbaUtils.h"
#include <sca/prop_helpers.h>
#include "sca/concurrent.h"
#include "sca/PropertyMap.h"

PropertySet_impl::PropertySet_impl (): _propertyQueryTimestamp("QUERY_TIMESTAMP"), _propertiesInitialized(false)
{
}

PropertySet_impl::~PropertySet_impl ()
{
    // Clean up all property callback functors.
    propCallbacks.clear();
}

void PropertySet_impl::setExecparamProperties(std::map<std::string, char*>& execparams)
{
    std::map<std::string, char*>::iterator iter;
    for (iter = execparams.begin(); iter != execparams.end(); iter++) {
        const std::string id = iter->first;
        PropertyInterface* property = getPropertyFromId(id);
        // the property can belong to a resource, device, or Device/Domain
        // Manager.  If the property is not found, then it might be a resource
        // property passed through the nodeBooter to the DeviceManager
        if (property) {
            CORBA::Any val = sca::string_to_any(iter->second, property->type);
            property->setValue(val);
        } else {
            std::cout<<"Property: " << id << " is not defined, ignoring it!!"<<std::endl;
        }
    }
}

void PropertySet_impl::setCommandLineProperty(const std::string& id, const sca::Value& value)
{
    PropertyInterface* property = getPropertyFromId(id);
    // the property can belong to a resource, device, or Device/Domain
    // Manager.  If the property is not found, then it might be a resource
    // property passed through the nodeBooter to the DeviceManager
    if (property) {
        property->setValue(value, false);
    } else {
        std::cout<<"Property: " << id << " is not defined, ignoring it!!"<<std::endl;
    }
}

void
PropertySet_impl::configure (const CF::Properties& configProperties)
throw (CORBA::SystemException, CF::PropertySet::InvalidConfiguration,
       CF::PropertySet::PartialConfiguration)
{
    boost::mutex::scoped_lock lock(propertySetAccess);

    int validProperties = 0;
    CF::Properties invalidProperties;

    for (CORBA::ULong ii = 0; ii < configProperties.length(); ++ii) {
        PropertyInterface* property = getPropertyFromId((const char*)configProperties[ii].id);
        if (property && property->isConfigurable()) {
            try {
                std::vector<std::string>::iterator kind = property->kinds.begin();
                CORBA::Any before_value, after_value;
                property->getValue(before_value);
                property->setValue(configProperties[ii].value);
                property->getValue(after_value);
                std::string comparator("eq");
                if (sca::compare_anys(before_value, after_value, comparator)) {
                }
                executePropertyCallback(property->id);
                ++validProperties;
            } catch (std::exception& e) {
                std::cout<<"Setting property " << property->id << ", " << property->name << " failed.  Cause: " << e.what()<<std::endl;
                CORBA::ULong count = invalidProperties.length();
                invalidProperties.length(count + 1);
                invalidProperties[count].id = CORBA::string_dup(configProperties[ii].id);
                invalidProperties[count].value = configProperties[ii].value;
            } catch (CF::PropertySet::InvalidConfiguration& e) {
                throw;
            } catch (CORBA::Exception& e) {
                std::cout<<"Setting property " << property->id << " failed.  Cause: " << e._name()<<std::endl;
                CORBA::ULong count = invalidProperties.length();
                invalidProperties.length(count + 1);
                invalidProperties[count].id = CORBA::string_dup(configProperties[ii].id);
                invalidProperties[count].value = configProperties[ii].value;
            }
        } else {
            CORBA::ULong count = invalidProperties.length();
            invalidProperties.length(count + 1);
            invalidProperties[count].id = CORBA::string_dup(configProperties[ii].id);
            invalidProperties[count].value = configProperties[ii].value;
        }
    }

    if (invalidProperties.length () > 0) {
        if (validProperties > 0) {
            throw CF::PropertySet::PartialConfiguration(invalidProperties);
        } else {
            throw CF::PropertySet::InvalidConfiguration("No matching properties found", invalidProperties);
        }
    }
}


void
PropertySet_impl::query (CF::Properties& configProperties)
throw (CORBA::SystemException, CF::UnknownProperties)
{
    boost::mutex::scoped_lock lock(propertySetAccess);

    // For queries of zero length, return all id/value pairs in propertySet.
    if (configProperties.length () == 0) {
        PropertyMap::iterator jj = propTable.begin();
        for (CORBA::ULong ii = 0; ii < propTable.size(); ++ii) {
            if (jj->second->isQueryable()) {
                configProperties.length(configProperties.length()+1);
                configProperties[configProperties.length()-1].id = CORBA::string_dup(jj->second->id.c_str());
                if (jj->second->isNilEnabled()) {
                    if (jj->second->isNil()) {
                        configProperties[configProperties.length()-1].value = CORBA::Any();
                    } else {
                        jj->second->getValue(configProperties[configProperties.length()-1].value);
                    }
                } else {
                    jj->second->getValue(configProperties[configProperties.length()-1].value);
                }
            }
            ++jj;
        }
    } else {
        // For queries of length > 0, return all requested pairs in propertySet
        CF::Properties invalidProperties;

        // Returns values for valid queries in the same order as requested
        for (CORBA::ULong ii = 0; ii < configProperties.length (); ++ii) {
            const std::string id = (const char*)configProperties[ii].id;
            if (id == _propertyQueryTimestamp) {
                configProperties[ii].value <<= _makeTime(-1,0,0);
                continue;
            }
            PropertyInterface* property = getPropertyFromId(id);
            if (property && property->isQueryable()) {
                if (property->isNilEnabled()) {
                    if (property->isNil()) {
                        configProperties[ii].value = CORBA::Any();
                    } else {
                        property->getValue(configProperties[ii].value);
                    }
                } else {
                    property->getValue(configProperties[ii].value);
                }
            } else {
                CORBA::ULong count = invalidProperties.length();
                invalidProperties.length(count + 1);
                invalidProperties[count].id = CORBA::string_dup(configProperties[ii].id);
                invalidProperties[count].value = configProperties[ii].value;
            }
        }

        if (invalidProperties.length () != 0) {
            throw CF::UnknownProperties(invalidProperties);
        }
    }
}

PropertyInterface* PropertySet_impl::getPropertyFromId (const std::string& id)
{
  PropertyMap::iterator property = propTable.find(id);
  if (property != propTable.end()) {
    return property->second;
  }
  return 0;
}

PropertyInterface* PropertySet_impl::getPropertyFromName (const std::string& name)
{
    for (PropertyMap::iterator property = propTable.begin(); property != propTable.end(); ++property) {
        if (name == property->second->name) {
            return property->second;
        }
    }
    return 0;
}

PropertyInterface* PropertySet_impl::getPropertyFromAddress(const void* address)
{
    for (PropertyMap::iterator property = propTable.begin(); property != propTable.end(); ++property) {
        if (property->second->matchesAddress(address)) {
            return property->second;
        }
    }
    return 0;
}

void
PropertySet_impl::validate (CF::Properties property,
                            CF::Properties& validProps,
                            CF::Properties& invalidProps)
{
    for (CORBA::ULong ii = 0; ii < property.length (); ++ii) {
        std::string id((const char*)property[ii].id);
        if (getPropertyFromId(id)) {
            CORBA::ULong count = validProps.length();
            validProps.length(count + 1);
            validProps[count].id = property[ii].id;
            validProps[count].value = property[ii].value;
        } else {
            CORBA::ULong count = invalidProps.length();
            invalidProps.length(count + 1);
            invalidProps[count].id = property[ii].id;
            invalidProps[count].value = property[ii].value;
        }
    }
}

CF::DataType PropertySet_impl::getProperty (CORBA::String_var _id)
{
    CF::DataType value;
    std::string id = (const char*)(_id);
    PropertyInterface* property = getPropertyFromId(id);
    if (property) {
        value.id = CORBA::string_dup(_id);
        property->getValue(value.value);
    }
    return value;
}

void PropertySet_impl::setPropertyChangeListener (const std::string& id, PropertyCallbackFn func)
{
    PropertyCallback cb;
    cb = func;
    setPropertyCallback(id, cb);
}

void PropertySet_impl::executePropertyCallback (const std::string& id)
{
    PropertyCallbackMap::iterator func = propCallbacks.find(id);
    if (propCallbacks.end() == func) {
        return;
    }
    (func->second)(id);
}

void PropertySet_impl::setPropertyCallback (const std::string& id, PropertyCallback callback)
{
    std::string propId;

    // Check whether the supplied id is actually a property name; if so, map the name
    // to an id, otherwise assume that 'id' is really a property id.
    PropertyInterface* property = getPropertyFromName(id);
    if (property) {
        propId = property->id;
    } else {
        // Check if property exists
        if (!getPropertyFromId(id)){
            std::cout<<"Setting listener for property " << id << " that does not exist"<<std::endl;
        }
        propId = id;
    }
    propCallbacks[propId] = callback;
}
