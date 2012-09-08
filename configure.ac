## libtidypp:
## a c++ wrapper around curl

AC_INIT([libtidypp], [1.0], [francesco1149@gmail.com], [tidypp],
        [http://code.google.com/p/tidypp/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_HEADERS([config.h tidyppconfig.h])
AC_PROG_CXX
LT_INIT([disable-static])

PKG_CHECK_MODULES([DEPS], [libtidy])
AC_SUBST([TIDYPP_SO_VERSION], [0:0:0])
AC_SUBST([TIDYPP_API_VERSION], [1.0])

AC_CONFIG_FILES([Makefile
                 tidypp-${TIDYPP_API_VERSION}.pc:tidypp.pc.in])
AC_OUTPUT
