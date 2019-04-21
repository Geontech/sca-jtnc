#
# This file is protected by Copyright. Please refer to the COPYRIGHT file 
# distributed with this source distribution.
# 
# This file is part of SCA-JTNC core.
# 
# SCA-JTNC core is free software: you can redistribute it and/or modify it under 
# the terms of the GNU Lesser General Public License as published by the Free 
# Software Foundation, either version 3 of the License, or (at your option) any 
# later version.
# 
# SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT 
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
# 
# You should have received a copy of the GNU Lesser General Public License 
# along with this program.  If not, see http://www.gnu.org/licenses/.
#
CFDIR = $(top_srcdir)/base
AM_CPPFLAGS = -I$(CFDIR)/include -I$(CFDIR)/include/sca -I$(CFDIR)/include/sca/CF -I$(CFDIR)/include/sca/BULKIO -I$(CFDIR)/include/sca/FRONTEND -I$(CFDIR)

scaName = BasicFEI
noinst_PROGRAMS = BasicFEI

BasicFEI_SOURCES = BasicFEI.cpp BasicFEI.h BasicFEI_base.cpp BasicFEI_base.h main.cpp struct_props.h template_impl.cpp
BasicFEI_CXXFLAGS = -Wall $(BOOST_CPPFLAGS) -I$(CFDIR) -I$(CFDIR)/include -I$(CFDIR)/bulkio/cpp/include -I$(CFDIR)/frontend/cpp -I$(CFDIR)/include/sca -I$(CFDIR)/include/sca/CF -I$(CFDIR)/include/sca/BULKIO -I$(CFDIR)/include/sca/FRONTEND
BasicFEI_LDADD = $(BOOST_LDFLAGS) $(BOOST_THREAD_LIB) $(BOOST_SYSTEM_LIB) $(BOOST_REGEX_LIB) $(OMNICOS_LIBS) $(OMNITHREAD_LIBS) $(OMNIDYNAMIC_LIBS) $(CFDIR)/framework/libscacf.la $(CFDIR)/bulkio/libbulkio-4.1.la $(CFDIR)/frontend/libfrontend-4.1.la $(CFDIR)/framework/idl/CF/libscaidl.la $(CFDIR)/framework/idl/BULKIO/libscabulkioidl.la $(CFDIR)/framework/idl/FRONTEND/libscafrontendidl.la
BasicFEI_LDFLAGS = -Wall

