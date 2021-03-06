/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of SCA-JTNC bulkioInterfaces.
 *
 * SCA-JTNC bulkioInterfaces is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * SCA-JTNC bulkioInterfaces is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#ifndef __bulkio_shminputtransport_h
#define __bulkio_shminputtransport_h

#include <sca/PropertyMap.h>
#include <sca/ProvidesPort.h>

#include <BulkioTransport.h>

namespace bulkio {

    template <typename PortType>
    class ShmInputTransport;

    template <typename PortType>
    class ShmInputManager : public InputManager<PortType>
    {
    public:
        typedef ShmInputTransport<PortType> InputTransportType;

        ShmInputManager(InPort<PortType>* port);

        virtual std::string transportType();

        virtual CF::Properties transportProperties();

        virtual InputTransport<PortType>* createInputTransport(const std::string& transportId,
                                                               const sca::PropertyMap& properties);

        virtual sca::PropertyMap getNegotiationProperties(sca::ProvidesTransport* providesTransport);
    };
}

#endif // __bulkio_shminputtransport_h
