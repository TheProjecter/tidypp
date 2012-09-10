## tidypp:
## A c++ wrapper around HTML Tidy Lib

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

lib_LTLIBRARIES = libtidypp-@TIDYPP_API_VERSION@.la

libtidypp_@TIDYPP_API_VERSION@_la_CPPFLAGS = $(DEPS_CFLAGS)
libtidypp_@TIDYPP_API_VERSION@_la_LIBADD = -ltidy $(DEPS_LIBS)

libtidypp_@TIDYPP_API_VERSION@_la_SOURCES = src/attribute.cpp src/buffer.cpp \
	src/document.cpp src/inputsource.cpp src/mem.cpp src/node.cpp src/option.cpp \
	src/outputsink.cpp src/tidypp.cpp include/tidypp/attribute.hpp \
	include/tidypp/basic_wrapper.hpp include/tidypp/buffer.hpp \
	include/tidypp/document.hpp include/tidypp/inputsource.hpp \
	include/tidypp/io.hpp include/tidypp/mem.hpp include/tidypp/node.hpp \
	include/tidypp/option.hpp include/tidypp/outputsink.hpp include/tidypp/tidypp.hpp

libtidypp_@TIDYPP_API_VERSION@_la_LDFLAGS = -version-info $(TIDYPP_SO_VERSION)

tidypp_includedir=$(includedir)/tidypp-@TIDYPP_API_VERSION@/tidypp
tidypp_include_HEADERS = include/tidypp/attribute.hpp \
	include/tidypp/basic_wrapper.hpp include/tidypp/buffer.hpp \
	include/tidypp/document.hpp include/tidypp/inputsource.hpp \
	include/tidypp/io.hpp include/tidypp/mem.hpp include/tidypp/node.hpp \
	include/tidypp/option.hpp include/tidypp/outputsink.hpp include/tidypp/tidypp.hpp

tidypp_libincludedir = $(libdir)/tidypp-$(TIDYPP_API_VERSION)/include
nodist_tidypp_libinclude_HEADERS = tidyppconfig.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = tidypp-$(TIDYPP_API_VERSION).pc

dist_noinst_SCRIPTS = autogen.sh