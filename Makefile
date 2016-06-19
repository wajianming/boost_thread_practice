# Configure Input
# Package-related substitution variables
package        = BoostThreadPractice
version        = 0.1
tarname        = boostthreadpractice
distdir        = $(tarname)-$(version)

# Prefix-related substitution variables
prefix         = /usr/local
exec_prefix    = ${prefix}
bindir         = ${exec_prefix}/bin

# Tool-related substitution variables
CC             = gcc
DEFS           = -DHAVE_CONFIG_H
LIBS           = 
CFLAGS         = -g -O2
CPPFLAGS       = 
INSTALL        = /usr/bin/install -c
INSTALL_DATA   = ${INSTALL} -m 644
INSTALL_PROGRAM= ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}

# VPATH-related substitution variables
top_builddir   = .
builddir       = .
srcdir         = .



#TARGET1: refer to src/Makefile
#1. go into src folder
#2. run target "all" in src/Makefile
all clean check install uninstall:
	$(MAKE) -C src $@

#TARGET2: creates distribution, refers to TARGET3
dist: $(distdir).tar.gz

#TARGET3: generate software package
#ultimately depends on TARGET4
$(distdir).tar.gz: $(distdir)
	tar chof - $(distdir) | gzip -9 -c >$(distdir).tar.gz
	rm -rf $(distdir)

#TARGET4: create package distribution directory
$(distdir):
	mkdir -p $(distdir)/src
	cp $(srcdir)/configure $(distdir)
	cp $(srcdir)/config.h.in $(distdir)
	cp $(srcdir)/install-sh $(distdir)
	cp $(srcdir)/Makefile.in $(distdir)
	cp -rf $(srcdir)/src $(distdir)
    
distcheck: $(distdir).tar.gz
	gzip -cd $+ | tar xvf -
	cd $(distdir); ./configure
	$(MAKE) -C $(distdir) all check
	$(MAKE) -C $(distdir) DESTDIR=$${PWD}/$(distdir)/_inst install uninstall
	$(MAKE) -C $(distdir) clean
	rm -rf $(distdir)
	@echo "*** Package $(distdir).tar.gz is ready for distribution."

Makefile: Makefile.in config.status
	./config.status $@

config.status: configure
	./config.status --recheck

FORCE:
	-rm -rf $(distdir) &>/dev/null
	-rm $(distdir).tar.gz &>/dev/null
	
.PHONY: FORCE all clean check dist distcheck install uninstall
