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


#ifndef PROPERTYSET_IMPL_H
#define PROPERTYSET_IMPL_H

#include <vector>
#include <string>
#include <sstream>
#include <map>

#include <boost/bind.hpp>

#include "sca/PropertyInterface.h"
#include "sca/ProcessThread.h"
#include "CF/CF.h"

namespace sca {
    class Value;
}

class PropertySet_impl : public virtual POA_CF::PropertySet
{

public:

    PropertySet_impl ();
    ~PropertySet_impl ();

    /*
     * Sets all the execparams passed in runtime
     */
    void setExecparamProperties(std::map<std::string, char*>&);

    // The core framework provides an implementation for this method.
    void
    configure (const CF::Properties& configProperties)
    throw (CF::PropertySet::PartialConfiguration,
           CF::PropertySet::InvalidConfiguration, CORBA::SystemException);

    // The core framework provides an implementation for this method.
    void
    query (CF::Properties& configProperties)
    throw (CF::UnknownProperties, CORBA::SystemException);


    // Preferred new-style properties.
    PropertyInterface* getPropertyFromId (const std::string&);
    PropertyInterface* getPropertyFromName (const std::string&);
   
   static CF::UTCTime _makeTime(short status, double wsec, double fsec) {
       CF::UTCTime _time;
       struct timeval tv;
       gettimeofday(&tv, NULL);
       if (status == -1) {
           _time.tcstatus = 1;
           _time.twsec = tv.tv_sec;
           _time.tfsec = tv.tv_usec/1e6;
       } else {
           _time.tcstatus = status;
           _time.twsec = wsec;
           _time.tfsec = fsec;
       }
       return _time;
   };

protected:

    virtual void setCommandLineProperty(const std::string& id, const sca::Value& value);

    /*CF::Properties
            propertySet;*/
    CF::DataType
    getProperty (CORBA::String_var id);
    void
    validate (CF::Properties property, CF::Properties& validProps,
              CF::Properties& invalidProps);

    /*
     * Adds a property with no initial value.
     */
    template <typename T>
    PropertyInterface* addProperty (T& value, 
                                    const std::string& id, 
                                    const std::string& name, 
                                    const std::string& mode,
                                    const std::string& units, 
                                    const std::string& action, 
                                    const std::string& kinds)
    {
        PropertyInterface* wrapper = PropertyWrapperFactory::Create(value);
        wrapper->configure(id, name, mode, units, action, kinds);
        wrapper->isNil(true);
        ownedWrappers.push_back(wrapper);
        propTable[wrapper->id] = wrapper;
        return wrapper;
    }

    /*
     * Adds a property with an initial value.
     */
    template <typename T, typename T2>
    PropertyInterface* addProperty (T& value, 
                                    const T2& initial_value, 
                                    const std::string& id, 
                                    const std::string& name,
                                    const std::string& mode, 
                                    const std::string& units, 
                                    const std::string& action,
                                    const std::string& kinds)
    {
        PropertyInterface* wrapper = addProperty(value, id, name, mode, units, action, kinds);
        value = initial_value;
        wrapper->isNil(false);
        return wrapper;
    }
    
    template <typename T2>
    PropertyInterface* addProperty (CF::UTCTime& value, 
                                    const T2& initial_value, 
                                    const std::string& id, 
                                    const std::string& name,
                                    const std::string& mode, 
                                    const std::string& units, 
                                    const std::string& action,
                                    const std::string& kinds)
    {
        PropertyInterface* wrapper = addProperty(value, id, name, mode, units, action, kinds);
        value = sca::time::utils::convert(initial_value);
        wrapper->isNil(false);
        return wrapper;
    }

    template <class C, typename T>
    void addPropertyChangeListener (const std::string& id, C* target, void (C::*func)(const T*, const T*))
    {
        try {
            PropertyWrapper<T>* wrapper = getPropertyWrapperById<T>(id);
            wrapper->addChangeListener(target, func);
        } catch (const std::invalid_argument& error) {
            std::cout<<"Cannot add change listener: " << error.what()<<std::endl;
        }
    }

    template <typename T>
    void addPropertyChangeListener (const std::string& id, void (*func)(const T*, const T*))
    {
        try {
            PropertyWrapper<T>* wrapper = getPropertyWrapperById<T>(id);
            wrapper->addChangeListener(func);
        } catch (const std::invalid_argument& error) {
            std::cout<<"Cannot add change listener: " << error.what()<<std::endl;
        }
    }

    template <typename Func>
    void addPropertyChangeListener (const char* id, Func func)
    {
        addPropertyChangeListener(std::string(id), func);
    }

    template <typename Target, typename Func>
    void addPropertyChangeListener (const char* id, Target target, Func func)
    {
        addPropertyChangeListener(std::string(id), target, func);
    }

    /*
     * Set a callback function to be invoked on an object other than the property owner whenever the given property changes
     */
    template <typename T, typename Target, typename Func>
    void addPropertyListener (T& value, Target target, Func func)
    {
        try {
            getPropertyWrapper(value)->addChangeListener(target, func);
        } catch (const std::invalid_argument& error) {
            std::cout<<"Cannot add change listener: " << error.what()<<std::endl;
        }
    }

    /*
     * Set a callback function to be invoked whenever the given property changes
     */
    template <typename T, typename Func>
    void addPropertyListener (T& value, Func func)
    {
        try {
            getPropertyWrapper(value)->addChangeListener(func);
        } catch (const std::invalid_argument& error) {
            std::cout<<"Cannot add change listener: " << error.what()<<std::endl;
        }
    }

    /*
     * Set the implementation for querying the property value to call member function 'func'
     * on a class instance 'target'.
     */
    template <typename T, typename Target, typename Func>
    void setPropertyQueryImpl (T& value, Target target, Func func)
    {
        try {
            getPropertyWrapper(value)->setQuery(target, func);
        } catch (const std::exception& error) {
            std::cout<<"Cannot set query implementation: " << error.what()<<std::endl;
        }
    }

    /*
     * Set the implementation for querying the property value to call the function 'func'.
     */
    template <typename T, typename Func>
    void setPropertyQueryImpl (T& value, Func func)
    {
        try {
            getPropertyWrapper(value)->setQuery(func);
        } catch (const std::exception& error) {
            std::cout<<"Cannot set query implementation: " << error.what()<<std::endl;
        }
    }

    /*
     * Set the implementation for configuring the property value to call member function 'func'
     * on a class instance 'target'.
     */
    template <typename T, typename Target, typename Func>
    void setPropertyConfigureImpl (T& value, Target target, Func func)
    {
        try {
            getPropertyWrapper(value)->setConfigure(target, func);
        } catch (const std::exception& error) {
            std::cout<<"Cannot set configure implementation: " << error.what()<<std::endl;
        }
    }

    /*
     * Set the implementation for configuring the property value to call the function 'func'.
     */
    template <typename T, typename Func>
    void setPropertyConfigureImpl (T& value, Func func)
    {
        try {
            getPropertyWrapper(value)->setConfigure(func);
        } catch (const std::exception& error) {
            std::cout<<"Cannot set configure implementation: " << error.what()<<std::endl;
        }
    }

    /*
     * Set the callback for changes to a property to a member function on a class instance.
     * The member function must take a string argument (the identifier of the property that changed)
     * and return void.
     */
    template <class T>
    void setPropertyChangeListener (const std::string& id, T& target, void (T::*func)(const std::string&))
    {
        PropertyCallback cb;
        cb = boost::bind(func, &target, _1);
        setPropertyCallback(id, cb);
    }

    template <class T>
    void setPropertyChangeListener (const std::string& id, T* target, void (T::*func)(const std::string&))
    {
        PropertyCallback cb;
        cb = boost::bind(func, target, _1);
        setPropertyCallback(id, cb);
    }

    template <class T>
    PropertyWrapper<T>* getPropertyWrapperById (const std::string& id)
    {
        PropertyInterface* property = getPropertyFromId(id);
        if (!property) {
            throw std::invalid_argument("No property '" + id  + "'");
        }
        return castProperty<T>(property);
    }

    template <class T>
    PropertyWrapper<T>* getPropertyWrapper (T& value)
    {
        PropertyInterface* property = getPropertyFromAddress(&value);
        if (!property) {
            throw std::invalid_argument("No property associated with value");
        }
        return castProperty<T>(property);
    }

    PropertyInterface* getPropertyFromAddress(const void* address);

    /*
     * Set the callback for changes to a property to a global function.
     * The function must take a string argument (the identifier of the property that changed)
     * and return void.
     */
    typedef void (*PropertyCallbackFn)(const std::string&);
    void setPropertyChangeListener (const std::string& id, PropertyCallbackFn func);

    /*
     * Call the property change callback for the given identifier.
     */
    void executePropertyCallback (const std::string& id);
    
    // This mutex is used to deal with configure/query concurrency
    boost::mutex propertySetAccess;

    std::vector<PropertyInterface*> ownedWrappers;

    // Preferred new-style properties.
    typedef std::map<std::string, PropertyInterface*> PropertyMap;
    PropertyMap propTable;

    std::string _propertyQueryTimestamp;

private:
    template <typename T>
    PropertyWrapper<T>* castProperty(PropertyInterface* property)
    {
        PropertyWrapper<T>* wrapper = dynamic_cast<PropertyWrapper<T>*>(property);
        if (!wrapper) {
            std::ostringstream message;
            message << "Property '" << property->id << "' is of type '" << property->getNativeType() << "'"
                    << " (not '" << sca::traits<T>::name() << "')";
            throw std::invalid_argument(message.str());
        }
        return wrapper;
    }

    typedef sca::callback<void (const std::string&)> PropertyCallback;
    void setPropertyCallback (const std::string& id, PropertyCallback callback);

    typedef std::map<std::string, PropertyCallback> PropertyCallbackMap;
    PropertyCallbackMap propCallbacks;
    
    bool _propertiesInitialized;
};

#endif                                            /*  */
