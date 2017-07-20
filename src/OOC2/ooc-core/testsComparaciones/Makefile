#
##############################
# OOC TestSuite makefile
# -----
# Object Oriented C Library
#
# Author: Laurent Deniau, Laurent.Deniau@cern.ch
#
# $Id: Makefile,v 1.5 2005/10/25 13:04:50 oachim Exp $
#
# For more information, please see the paper:
# http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
#
##############################
#

#
# EXE NAME
#

EXE = tests

#
# CONFIGS
#

ifndef $(TOPDIR)
TOPDIR = $(shell cd ../.. ; pwd)
include $(TOPDIR)/.config
endif

CPPFLAGS += -I$(TOPDIR)/ooc-core
LDFLAGS   = -L$(TOPDIR) -ldl

#
# FILE LISTS
#

LIBLIST = -looc

#
# MAIN TARGETS
#

test: $(EXE)

runtests: test
	@./$(EXE)

runspeeds: test
	@./$(EXE) -s

#
# FILE LISTS
#

HDRLIST = $(shell $(FIND) -name '*.h' -print)
SRCLIST = $(shell $(FIND) -name '*.c' -print)
OBJLIST = $(SRCLIST:.c=.o)
DEPLIST = $(SRCLIST:.c=.d)

$(EXE): lib_ooc dep $(OBJLIST)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJLIST) -o $(EXE) $(LDFLAGS) $(LIBLIST)

#
# LIBOOC DEP
#

lib_ooc:
	@make -C $(TOPDIR)/ooc-core libs

#
# CLEAN
#

include $(TOPDIR)/Makefile.clean

cleanexe:
	rm -f $(EXE)

cleanall: clean cleanobj cleandep cleancpp cleanbak cleanexe

#
# BUILD DEPS
#

dep: $(DEPLIST)

%.d:%.c
	@echo 'creating dependencies of $<'
	@$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@~
	@$(SED) 's,\($(*F)\)\.o[ :]*,$(*D)/\1.o $@: ,g' < $@~ > $@
	@$(RM) -f $@~	

CMMDCLEAN = $(findstring clean,$(MAKECMDGOALS))
CMMDPRINT = $(findstring print,$(MAKECMDGOALS))
CMMDUNINS = $(findstring uninstall,$(MAKECMDGOALS))

ifeq ($(CMMDCLEAN)$(CMMDPRINT)$(CMMDUNINS),)
-include $(SRCLIST:.c=.d)
endif
