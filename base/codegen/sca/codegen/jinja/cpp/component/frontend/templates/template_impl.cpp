/*#
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
 #*/
/*
 * necessary to allow FrontendTunerDevice template class to be split
 * into separate header and implementation files (.h and .cpp)
 */

#include "struct_props.h"
#include <frontend/fe_tuner_device.cpp>

/*{% if 'ScanningTuner' in component.implements %}*/
template class frontend::FrontendScanningTunerDevice<frontend_tuner_status_struct_struct>;
/*{% else %}*/
template class frontend::FrontendTunerDevice<frontend_tuner_status_struct_struct>;
/*{% endif %}*/
