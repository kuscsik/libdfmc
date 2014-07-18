dnl Process this file with autoconf to produce a configure script.
AC_INIT(dfmcframework, 1.0, zoltan.kuscsik@dfmc.com)

AC_LANG([C++])
AC_PROG_CC([gcc cl cc])
AC_LANG_CPLUSPLUS
AC_PROG_CXX
CXXFLAGS='-Wall -std=gnu++0x'
AC_CHECK_HEADER(cstdint)

AC_CONFIG_AUX_DIR(include)
AC_CONFIG_SRCDIR(include/dfmc/demo/IDemoApp.hpp)
AC_CONFIG_HEADERS([include/config.h])

AC_SUBST([DFMCFRAMEWORK_SO_VERSION], [1:0:0])
AC_SUBST([DFMCFRAMEWORK_API_VERSION], [1.0])

dnl AC_DEFINE([DFMC_COMPILER_TR1_MEMORY],[],[dfmc specific memory define])
AC_DEFINE([EGL_API_DFB],[],[Use DirectFB EGL])
AC_DEFINE([LINUX], [], [Target platform])
LT_INIT([disable-static])
AM_INIT_AUTOMAKE

AC_DEFINE([DFMC_COMPILER_CPP11_THREADS], [], [Has C++11 threads])
AC_DEFINE([DFMC_HAS_DIRECTFB], [], [Enable DirectFB demo code])

AC_CONFIG_FILES([dfmcframework-${DFMCFRAMEWORK_API_VERSION}.pc:dfmcframework.pc.in])

AC_OUTPUT(Makefile)
