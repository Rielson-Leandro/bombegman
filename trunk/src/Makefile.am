bin_PROGRAMS = bombegman bombegman-server
noinst_HEADERS = 
bombegman_SOURCES = main.cpp gfx.cpp sfx.cpp main.h berror.cpp berror.h
bombegman_server_SOURCES = server-core.cpp server-core.h berror.cpp berror.h utils.cpp utils.h

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g
