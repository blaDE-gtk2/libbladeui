AM_CPPFLAGS = \
	-DGLIB_DISABLE_DEPRECATION_WARNINGS \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libbladeui-glade\" \
	$(PLATFORM_CPPFLAGS)

SUBDIRS = \
	icons

if HAVE_GLADEUI
##
## Glade module
##
glademoduledir = \
	$(GLADEUI_MODULEDIR)

glademodule_LTLIBRARIES = \
	libbladeuiglade.la

libbladeuiglade_la_SOURCES  = \
	libbladeui-glade.c

libbladeuiglade_la_CFLAGS = \
	$(GLADEUI_CFLAGS) \
	$(LIBBLADEUTIL_CFLAGS) \
	$(PLATFORM_CFLAGS)

libbladeuiglade_la_LDFLAGS = \
	-no-undefined \
	-avoid-version \
	-module \
	$(PLATFORM_LDFLAGS)

libbladeuiglade_la_LIBADD = \
	$(top_builddir)/libbladeui/libbladeui-1.la \
	$(LIBBLADEUTIL_LIBS) \
	$(GLADEUI_LIBS)

##
## Glade catalog xml file
##
gladecatalogdir = \
	$(GLADEUI_CATALOGDIR)
gladecatalog_DATA = \
	libbladeui.xml
@INTLTOOL_XML_NOMERGE_RULE@
endif

if HAVE_GLADEUI2
##
## Glade module
##
glademoduledir = \
	$(GLADEUI2_MODULEDIR)

glademodule_LTLIBRARIES = \
	libbladeuiglade2.la

libbladeuiglade2_la_SOURCES  = \
	libbladeui-glade.c

libbladeuiglade2_la_CFLAGS = \
	$(GLADEUI2_CFLAGS) \
	$(LIBBLADEUTIL_CFLAGS) \
	$(PLATFORM_CFLAGS)

libbladeuiglade2_la_LDFLAGS = \
	-no-undefined \
	-avoid-version \
	-module \
	$(PLATFORM_LDFLAGS)

libbladeuiglade2_la_LIBADD = \
	$(top_builddir)/libbladeui/libbladeui-2.la \
	$(LIBBLADEUTIL_LIBS) \
	$(GLADEUI2_LIBS)

##
## Glade catalog xml file
##
gladecatalogdir = \
	$(GLADEUI2_CATALOGDIR)
gladecatalog_DATA = \
	libbladeui-2.xml
@INTLTOOL_XML_NOMERGE_RULE@
endif

CLEANFILES = \
	libbladeui.xml	\
	libbladeui-2.xml

EXTRA_DIST = \
	libbladeui.xml.in	\
	libbladeui-2.xml.in

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
