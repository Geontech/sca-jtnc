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
#ifndef __bulkio_shmoutputtransport_h
#define __bulkio_shmoutputtransport_h

#include <sca/PropertyMap.h>
#include <sca/UsesPort.h>

#include <BulkioTransport.h>

namespace bulkio {

    template <typename PortType>
    class ShmOutputTransport;

    template <typename PortType>
    class ShmOutputManager : public OutputManager<PortType>
    {
    public:
        typedef ShmOutputTransport<PortType> TransportType;
        typedef typename PortType::_ptr_type PtrType;

        ShmOutputManager(OutPort<PortType>* port);

        virtual std::string transportType();

        virtual CF::Properties transportProperties();

        virtual OutputTransport<PortType>* createOutputTransport(PtrType object,
                                                                 const std::string& connectionId,
                                                                 const sca::PropertyMap& properties);

        virtual sca::PropertyMap getNegotiationProperties(sca::UsesTransport* transport);

        virtual void setNegotiationResult(sca::UsesTransport* transport, const sca::PropertyMap& properties);

    private:
        std::string _hostname;
    };

}

#endif // __bulkio_shmoutputtransport_h
