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
// Not copyrighted - public domain.
//
// This sample parser implementation was generated by CodeSynthesis XSD,
// an XML Schema to C++ data binding compiler. You may use it in your
// programs without any restrictions.
//

#ifndef CXX___XML_XSD_SAD_PIMPL_H
#define CXX___XML_XSD_SAD_PIMPL_H

#include "sad-pskel.h"
#include <ossie/logging/rh_logger.h>

namespace sad
{
  extern rh_logger::LoggerPtr parserLog;

  class softwareassembly_pimpl: public softwareassembly_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    description (const ::std::string&);

    virtual void
    componentfiles (::std::vector<ossie::ComponentFile>&);

    virtual void
    partitioning (const ossie::SoftwareAssembly::Partitioning&);

    virtual void
    assemblycontroller (const ::std::string&);

    virtual void
    connections (::std::vector<ossie::Connection>&);

    virtual void
    externalports (::std::vector<ossie::SoftwareAssembly::Port>&);

    virtual void
    externalproperties (::std::vector<ossie::SoftwareAssembly::Property>&);

    virtual void
    options (::std::vector<ossie::SoftwareAssembly::Option>&);

    virtual void
    usesdevicedependencies (::std::vector<ossie::UsesDevice>&);

    virtual void
    id (const ::std::string&);

    virtual void
    name (const ::std::string&);

    virtual ::std::auto_ptr<ossie::SoftwareAssembly::SAD>
    post_softwareassembly ();

    private:
    std::auto_ptr<ossie::SoftwareAssembly::SAD> _sad;
  };

  class componentfiles_pimpl: public virtual componentfiles_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    componentfile (const ::ossie::ComponentFile&);

    virtual ::std::vector<ossie::ComponentFile>&
    post_componentfiles ();
    
    private:
    std::vector<ossie::ComponentFile> componentFiles;
  };

  class componentfile_pimpl: public virtual componentfile_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    localfile (const ::std::string&);

    virtual void
    id (const ::std::string&);

    virtual void
    type (const ::std::string&);

    virtual ::ossie::ComponentFile
    post_componentfile ();
    
    private:
    std::auto_ptr<ossie::ComponentFile> componentFile;
  };

  class localfile_pimpl: public virtual localfile_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual ::std::string
    post_localfile ();
    
    private:
    std::string filename;
  };

  class partitioning_pimpl: public virtual partitioning_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    componentplacement (const ::ossie::ComponentPlacement&);

    virtual void
    hostcollocation (const ossie::SoftwareAssembly::HostCollocation&);

    virtual ::ossie::SoftwareAssembly::Partitioning
    post_partitioning ();
    
    private:
    std::auto_ptr<ossie::SoftwareAssembly::Partitioning> partitioning;
  };

  class componentplacement_pimpl: public virtual componentplacement_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    componentfileref (const ::std::string&);

    virtual void
    componentinstantiation (const ::ossie::ComponentInstantiation&);

    virtual const ::ossie::ComponentPlacement&
    post_componentplacement ();
    
    private:
    ossie::ComponentPlacement componentPlacement;
  };

  class componentfileref_pimpl: public virtual componentfileref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual ::std::string
    post_componentfileref ();
    
    private:
    std::string _refid;
  };

  class componentinstantiation_pimpl: public virtual componentinstantiation_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    usagename (const ::std::string&);

    virtual void
    componentproperties (ossie::ComponentPropertyList&);

    virtual void
    findcomponent (const ::std::string&);

    virtual void
    id (const ::std::string&);
    
    virtual void
    startorder (const ::std::string&);

    virtual void
    affinity (ossie::ComponentInstantiation::AffinityProperties&);

    virtual void
      loggingconfig (const ossie::ComponentInstantiation::LoggingConfig&);

    virtual void
    devicerequires (ossie::ComponentPropertyList&);

    virtual const ::ossie::ComponentInstantiation&
    post_componentinstantiation ();
    
    private:
    ossie::ComponentInstantiation componentInstantiation;
  };

  class affinity_pimpl: public virtual affinity_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    simpleref (const ossie::SimplePropertyRef&);

    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual void
    structref ( const ossie::StructPropertyRef&);

    virtual void
    structsequenceref (const ossie::StructSequencePropertyRef&);

    ossie::ComponentInstantiation::AffinityProperties&
    post_affinity ();

    private:
    ossie::ComponentInstantiation::AffinityProperties affinityProperties;
  };


  class loggingconfig_pimpl: public virtual loggingconfig_pskel, xml_schema::string_pimpl
  {
    public:

    virtual void pre ();

    virtual void level (const ::std::string&);

    virtual const ossie::ComponentInstantiation::LoggingConfig&
     post_loggingconfig ();
    
    private:
    ossie::ComponentInstantiation::LoggingConfig  info;
  };

  class devicerequires_pimpl: public virtual devicerequires_pskel
  {
    public:

    virtual void
    pre ();

    virtual void
    requires (const ossie::IdValue&);

    virtual ossie::ComponentPropertyList&
    post_devicerequires ();

    private:
    ossie::ComponentPropertyList  devicerequires;
  };



  class componentproperties_pimpl: public virtual componentproperties_pskel
  {
    public:

    virtual void
    pre ();

    virtual void
    simpleref (const ossie::SimplePropertyRef&);

    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual void
    structref (const ossie::StructPropertyRef&);

    virtual void
    structsequenceref (const ossie::StructSequencePropertyRef&);

    virtual ossie::ComponentPropertyList&
    post_componentproperties ();
    
    private:
    ossie::ComponentPropertyList  componentProperties;
  };

  class findcomponent_pimpl: public virtual findcomponent_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    componentresourcefactoryref ();

    virtual void
    namingservice (const ::std::string&);

    virtual ::std::string 
    post_findcomponent ();
    
    private:
    ::std::string namingservicename;
  };


  class componentresourcefactoryref_pimpl: public virtual componentresourcefactoryref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    resourcefactoryproperties ();

    virtual void
    refid (const ::std::string&);

    virtual void
    post_componentresourcefactoryref ();
  };

  class devicethatloadedthiscomponentref_pimpl: public virtual devicethatloadedthiscomponentref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual std::string
    post_devicethatloadedthiscomponentref ();

    private:
    std::string _refid;
  };

  class deviceusedbythiscomponentref_pimpl: public virtual deviceusedbythiscomponentref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual void
    usesrefid (const ::std::string&);

    virtual ::std::pair<std::string, std::string>
    post_deviceusedbythiscomponentref ();

    private:
    std::pair<std::string, std::string> info;
  };

  class deviceusedbyapplication_pimpl: public virtual deviceusedbyapplication_pskel
  {
  public:
      virtual void
      pre ();

      virtual void
      usesrefid (const ::std::string&);

      virtual ::std::string
      post_deviceusedbyapplication ();

  private:
      ::std::string usesRefId;

  };

  class resourcefactoryproperties_pimpl: public virtual resourcefactoryproperties_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    simpleref (const ossie::SimplePropertyRef&);

    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual void
    structref ( const ossie::StructPropertyRef&);

    virtual void
    structsequenceref (const ossie::StructSequencePropertyRef&);

    virtual void
    post_resourcefactoryproperties ();
  };

  class idvalue_pimpl: public virtual idvalue_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    id (const ::std::string&);

    virtual void
    value (const ::std::string&);

    virtual const ossie::IdValue&
    post_idvalue ();

    private:
    ossie::IdValue simple;
  };


  class simpleref_pimpl: public virtual simpleref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual void
    value (const ::std::string&);

    virtual const ossie::SimplePropertyRef&
    post_simpleref ();
    
    private:
    ossie::SimplePropertyRef simple;
  };

  class simplesequenceref_pimpl: public virtual simplesequenceref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    values (const ::std::vector<std::string>&);

    virtual void
    refid (const ::std::string&);

    virtual const ossie::SimpleSequencePropertyRef&
    post_simplesequenceref ();
    private:
    ossie::SimpleSequencePropertyRef simpleseq;
  };

  class structref_pimpl: public virtual structref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    simpleref (const ossie::SimplePropertyRef&);

    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual void
    refid (const ::std::string&);

    virtual const ossie::StructPropertyRef&
    post_structref ();

    private:
    ossie::StructPropertyRef structref;
  };

  class structsequenceref_pimpl: public virtual structsequenceref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
      structvalue (const ossie::ComponentPropertyMap& value);

    virtual void
    refid (const ::std::string&);

    virtual const ossie::StructSequencePropertyRef&
    post_structsequenceref ();

    private:
    ossie::StructSequencePropertyRef  structsequenceref;
  };

  class structvalue_pimpl: public virtual structvalue_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    simpleref (const ossie::SimplePropertyRef&);
 
    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual const ossie::ComponentPropertyMap&
    post_structvalue ();

    private:
    ossie::ComponentPropertyMap  values;
  };

  class values_pimpl: public virtual values_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    value (const ::std::string&);

    virtual ::std::vector<std::string>
    post_values ();

    private:
    ::std::vector<std::string> values;
  };

  class componentinstantiationref_pimpl: public virtual componentinstantiationref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual ::std::string
    post_componentinstantiationref ();

    private:
    std::string _refid;
  };

  class findby_pimpl: public virtual findby_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    namingservice (const ::std::string&);

    virtual void
    stringifiedobjectref (const ::std::string&);

    virtual void
    domainfinder (const ::std::pair<std::string, std::string>&);

    virtual ::ossie::FindBy
    post_findby ();

    private:
    std::auto_ptr<ossie::FindBy> findby;
  };

  class namingservice_pimpl: public virtual namingservice_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual ::std::string
    post_namingservice ();
    
    private:
    std::string _name;
  };

  class domainfinder_pimpl: public virtual domainfinder_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    type (const ::std::string&);

    virtual void
    name (const ::std::string&);

    virtual ::std::pair<std::string, std::string>
    post_domainfinder ();

    private:
    ::std::pair<std::string, std::string> domainfinder;

  };

  class hostcollocation_pimpl: public virtual hostcollocation_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    componentplacement (const ::ossie::ComponentPlacement&);

    virtual void
    usesdeviceref (const ::ossie::UsesDeviceRef&);

    virtual void
    reservation (const ::ossie::Reservation&);

    virtual void
    id (const ::std::string&);

    virtual void
    name (const ::std::string&);

    virtual ossie::SoftwareAssembly::HostCollocation
    post_hostcollocation ();

    private:
    std::auto_ptr<ossie::SoftwareAssembly::HostCollocation> hostcollocation; 
  };

  class usesdeviceref_pimpl: public virtual usesdeviceref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual const ossie::UsesDeviceRef&
    post_usesdeviceref ();

    private:
    ossie::UsesDeviceRef udevref;
  };

  class reservation_pimpl: public virtual reservation_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    kind (const ::std::string&);

    virtual void
    value (const ::std::string&);

    virtual const ossie::Reservation&
    post_reservation ();

    virtual std::string post_string ();

    private:
    ossie::Reservation resrv;
  };

  class assemblycontroller_pimpl: public virtual assemblycontroller_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    componentinstantiationref (const ::std::string&);

    virtual ::std::string
    post_assemblycontroller ();

    private:
    std::string _refid;
  };

  class connections_pimpl: public virtual connections_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    connectinterface (const ::ossie::Connection&);

    virtual ::std::vector<ossie::Connection>&
    post_connections ();

    private:
    ::std::vector<ossie::Connection> connections;
  };

  class connectinterface_pimpl: public virtual connectinterface_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    usesport (const ::ossie::UsesPort&);

    virtual void
    providesport (const ::ossie::ProvidesPort&);

    virtual void
    componentsupportedinterface (const ::ossie::ComponentSupportedInterface&);

    virtual void
    findby (const ::ossie::FindBy&);

    virtual void
    id (const ::std::string&);

    virtual ::ossie::Connection
    post_connectinterface ();

    private:
    std::auto_ptr<ossie::Connection> connection;
  };

  class usesport_pimpl: public virtual usesport_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    usesidentifier (const ::std::string&);

    virtual void
    componentinstantiationref (const ::std::string&);

    virtual void
    devicethatloadedthiscomponentref (const ::std::string&);

    virtual void
    deviceusedbythiscomponentref (const ::std::pair<std::string, std::string>&);

    virtual void
    deviceusedbyapplication (const ::std::string&);

    virtual void
    findby (const ::ossie::FindBy&);

    virtual ::ossie::UsesPort
    post_usesport ();

    private:
    std::auto_ptr<ossie::UsesPort> usesPort;
  };

  class providesport_pimpl: public virtual providesport_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    providesidentifier (const ::std::string&);

    virtual void
    componentinstantiationref (const ::std::string&);

    virtual void
    devicethatloadedthiscomponentref (const std::string&);

    virtual void
    deviceusedbythiscomponentref (const ::std::pair<std::string, std::string>&);

    virtual void
    deviceusedbyapplication (const ::std::string&);

    virtual void
    findby (const ::ossie::FindBy&);

    virtual ::ossie::ProvidesPort
    post_providesport ();

    private:
    std::auto_ptr<ossie::ProvidesPort> provPort;
  };

  class componentsupportedinterface_pimpl: public virtual componentsupportedinterface_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    supportedidentifier (const ::std::string&);

    virtual void
    componentinstantiationref (const ::std::string&);

    virtual void
    devicethatloadedthiscomponentref (const ::std::string&);

    virtual void
    deviceusedbythiscomponentref (const ::std::pair<std::string, std::string>&);

    virtual void
    deviceusedbyapplication (const ::std::string&);

    virtual void
    findby (const ::ossie::FindBy&);

    virtual ::ossie::ComponentSupportedInterface
    post_componentsupportedinterface ();

    private:
    std::auto_ptr<ossie::ComponentSupportedInterface> ciface;
  };

  class externalports_pimpl: public virtual externalports_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    port (const ossie::SoftwareAssembly::Port&);

    virtual ::std::vector<ossie::SoftwareAssembly::Port>&
    post_externalports ();

    private:
    std::vector<ossie::SoftwareAssembly::Port> extPorts;
  };

  class port_pimpl: public virtual port_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    externalname (const ::std::string&);

    virtual void
    description (const ::std::string&);

    virtual void
    usesidentifier (const ::std::string&);

    virtual void
    providesidentifier (const ::std::string&);

    virtual void
    supportedidentifier (const ::std::string&);

    virtual void
    componentinstantiationref (const ::std::string&);

    virtual ::ossie::SoftwareAssembly::Port
    post_port ();

    private:
    std::auto_ptr<ossie::SoftwareAssembly::Port> port;
  };

  class externalproperties_pimpl: public virtual externalproperties_pskel
  {
  public:
      virtual void
      pre ();

      virtual void
      property (const ossie::SoftwareAssembly::Property&);

      virtual ::std::vector<ossie::SoftwareAssembly::Property>&
      post_externalproperties ();

  private:
      std::vector<ossie::SoftwareAssembly::Property> extProps;
  };

  class property_pimpl: public virtual property_pskel
  {
  public:
      virtual void
      pre ();

      virtual void
      comprefid (const ::std::string&);

      virtual void
      propid (const ::std::string&);

      virtual void
      externalpropid (const ::std::string&);

      virtual ::ossie::SoftwareAssembly::Property
      post_property ();

  private:
      std::auto_ptr<ossie::SoftwareAssembly::Property> property;
  };

  class options_pimpl: public virtual options_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    option (const ossie::SoftwareAssembly::Option&);

    virtual ::std::vector<ossie::SoftwareAssembly::Option>&
    post_options ();

    private:
    std::vector<ossie::SoftwareAssembly::Option> extOptions;
  };

  class option_pimpl: public virtual option_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual void
    value (const ::std::string&);

    virtual ::ossie::SoftwareAssembly::Option
    post_option ();

    private:
    std::auto_ptr<ossie::SoftwareAssembly::Option> option;
  };

  class usesdevicedependencies_pimpl: public virtual usesdevicedependencies_pskel
  {
  public:
      virtual void
      pre ();

      virtual void
      usesdevice (const ossie::UsesDevice&);

      virtual ::std::vector<ossie::UsesDevice>&
      post_usesdevicedependencies ();

  private:
      std::vector<ossie::UsesDevice> usesDevices;
  };

  class usesdevice_pimpl: public virtual usesdevice_pskel
  {
  public:
      virtual void
      pre ();

      virtual void
      propertyref (const ossie::PropertyRef&);

      virtual void
      simpleref (const ossie::SimplePropertyRef&);

      virtual void
      simplesequenceref (const ossie::SimpleSequencePropertyRef&);

      virtual void
        structref (const ossie::StructPropertyRef&);

      virtual void
      structsequenceref (const ossie::StructSequencePropertyRef&);

      virtual void
      id (const ::std::string&);

      virtual void
      type (const ::std::string&);

      virtual ossie::UsesDevice
      post_usesdevice ();

  private:
      std::auto_ptr<ossie::UsesDevice> uses;
  };

  class propertyref_pimpl: public virtual propertyref_pskel
  {
  public:
      virtual void
      pre ();

      virtual void
      refid (const ::std::string&);

      virtual void
      value (const ::std::string&);

      virtual ::ossie::PropertyRef
      post_propertyref ();

  private:
      std::auto_ptr<ossie::SimplePropertyRef> propRef;
  };
}

#endif // CXX___XML_XSD_SAD_PIMPL_H
