SUBDIRS = src

bombegmandocdir = ${prefix}/doc/bombegman
bombegmandoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(bombegmandoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(bombegmandocdir)

ACLOCAL_AMFLAGS= -I m4
