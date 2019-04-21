CFDIR = $(top_srcdir)/base

noinst_PROGRAMS = ProgrammableDevice

ProgrammableDevice_SOURCES = main.cpp ProgrammableDevice.cpp ProgrammableDevice_base.cpp ProgrammableDevice.h ProgrammableDevice_base.h ProgrammableDevice_prog_base.h entry_point.h struct_props.h
ProgrammableDevice_CXXFLAGS = -Wall $(BOOST_CPPFLAGS) -I$(CFDIR)/include  -I$(CFDIR)/bulkio/cpp/include  -I$(CFDIR)/include/sca/CF
ProgrammableDevice_LDADD = $(BOOST_REGEX_LIB) $(BOOST_SYSTEM_LIB) $(BOOST_THREAD_LIB) $(OMNIDYNAMIC_LIBS) $(OMNICOS_LIBS) $(CFDIR)/framework/libscacf.la $(CFDIR)/framework/idl/CF/libscaidl.la $(CFDIR)/bulkio/libbulkio-4.1.la $(CFDIR)/framework/idl/BULKIO/libscabulkioidl.la
# ProgrammableDevice_CXXFLAGS = -Wall $(BOOST_CPPFLAGS) $(OMNIORB_CFLAGS) $(OMNITHREAD_CFLAGS) $(OMNIDYNAMIC_CFLAGS)  $(redhawk_INCLUDES_auto) -I$(CFDIR)/include
# ProgrammableDevice_LDADD = $(BOOST_LDFLAGS) $(BOOST_THREAD_LIB) $(BOOST_SYSTEM_LIB) $(OMNICOS_LIBS) $(OMNITHREAD_LIBS) $(OMNIDYNAMIC_LIBS) $(CFDIR)/framework/libossiecf.la $(CFDIR)/framework/idl/libossieidl.la -ldl
# ProgrammableDevice_LDFLAGS = -Wall $(redhawk_LDFLAGS_auto)

