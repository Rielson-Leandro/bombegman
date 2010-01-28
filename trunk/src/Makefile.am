bin_PROGRAMS = bombegman bombegman-server
noinst_HEADERS = 
bombegman_SOURCES = main.cpp misc.cpp gfx.cpp sfx.cpp main.h
bombegman_server_SOURCES = server-core.cpp server-core.h

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g
