AC_PREREQ([2.69])
AC_INIT([coelacanth],[0.1],[meleneth@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects])

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB

AX_LUA_HEADERS
AX_LUA_LIBS
#AM_PATH_SDL this was sdl1.2
#AM_PATH_SDL2
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_MACRO_DIR([m4])

AM_PROG_AR

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h])

AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

AX_CXX_COMPILE_STDCXX_17()

# these are now autodetected
AC_CHECK_LIB([z], [zlibVersion])
AC_CHECK_LIB([m], [acos])
AC_CHECK_LIB([ogg], [oggpack_writeinit])
AC_CHECK_LIB([lzma], [lzma_index_buffer_decode])
AC_CHECK_LIB([vorbis], [vorbis_info_init])
AC_CHECK_LIB([vorbisfile], [ov_open])
AC_CHECK_LIB([png], [png_get_copyright])
AC_CHECK_LIB([jpeg], [jpeg_std_error])
AC_CHECK_LIB([tiff], [TIFFFdOpen])
AC_CHECK_LIB([pthread], [pthread_create])
AC_CHECK_LIB([GL], [glEnd])
#AC_CHECK_LIB([SDL_image], [IMG_Load]) this was sdl1.2

AC_LANG_PUSH([C++])
AC_LANG_POP([C++])

# these are still not working correctly, bastards!  So we are currently forceing them with LDADD

AC_CHECK_LIB([smpeg], [SMPEG_new])
AC_CHECK_LIB([mikmod], [Sample_Load])

AC_CHECK_LIB([iconv], [iconv_open])
AC_CHECK_LIB([mingw32], [main])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([atexit floor rint sqrt])

PKG_CHECK_MODULES([GTEST], [gtest_main])

AC_OUTPUT
