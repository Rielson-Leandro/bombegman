AC_INIT([bombegman],[0.0],[],[],[http://bombegman.googlecode.com/])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

SDL_REQUIRED=1.2.0

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC

AM_PROG_LIBTOOL

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])


AM_PATH_SDL($SDL_REQUIRED,
            :,
	    AC_MSG_ERROR([SDL version $SDL_REQUIRED not found]))
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
CFLAGS="$CFLAGS $SDL_CFLAGS"
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

AC_CHECK_LIB(SDL_image, IMG_Load,
    [ LIBS="$LIBS -lSDL_image" ],
    AC_MSG_ERROR([SDL_image not found]))

AC_CHECK_LIB(SDL_gfx, SDL_initFramerate,
    [ LIBS="$LIBS -lSDL_gfx" ],
    AC_MSG_ERROR([SDL_gfx not found]))

AC_CHECK_LIB(SDL_mixer, Mix_OpenAudio,
    [ LIBS="$LIBS -lSDL_mixer" ],
    AC_MSG_ERROR([SDL_mixer not found]))

AC_CHECK_LIB(SDL_net, SDLNet_Init,
    [ LIBS="$LIBS -lSDL_net" ],
    AC_MSG_ERROR([SDL_net not found]))

AC_OUTPUT
