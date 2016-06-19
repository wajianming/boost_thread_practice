#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([BoostThreadPractice], [0.1], [wajianming@mgmail.com])
AC_CONFIG_SRCDIR([src/dynamic_lib/thread.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AM_INIT_AUTOMAKE
LT_PREREQ([2.2])
LT_INIT([dlopen])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/bin/Makefile
                 src/dynamic_lib/Makefile
                 src/module/Makefile
                 src/static_lib/Makefile])
AC_OUTPUT
