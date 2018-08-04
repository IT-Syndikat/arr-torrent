#                                               -*- Autoconf -*-
AC_PREREQ([2.69])
AC_INIT([arr-torrent], [0.1], [bugs@arr-torrent.ninja], [arr-torrent], [https://arr-torrent.ninja])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])

AC_CONFIG_SRCDIR([daemon/command_server.cpp])
AC_CONFIG_HEADERS([config.h])

AC_LANG(C++)
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_14

# Checks for libraries.

PKG_CHECK_MODULES([libtorrent], [libtorrent-rasterbar >= 1.1.5])

AX_BOOST_BASE([1.62],, [AC_MSG_ERROR([need Boost, but it was not found on your system])])
AX_BOOST_ASIO


# Checks for header files.

AC_CHECK_HEADERS([json.hpp])


# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.


AC_CONFIG_FILES([
 Makefile
])

AC_OUTPUT
