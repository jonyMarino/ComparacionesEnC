#
##############################
# OOC Library makefile
# -----
# Object Oriented C Library
#
# Author: Laurent Deniau, Laurent.Deniau@cern.ch
#
# $Id: Makefile,v 1.7 2005/08/23 16:50:06 oachim Exp $
#
# For more information, please see the paper:
# http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
#
##############################
#

.EXPORT_ALL_VARIABLES:

#
# LIBRARY OOC
#

MODULE  = ooc
TARGET  = ooc
MAJOR   = 1
MINOR   = 0

#
# INCLUDE BASE MAKEFILE
#

ifndef $(TOPDIR)
TOPDIR = $(shell cd .. ; pwd)
include $(TOPDIR)/.config
endif

include $(TOPDIR)/Makefile.lib

#
# TESTSUITE
#

tests:
	@$(MAKE) -C testsuite tests

runtests:
	@$(MAKE) -C testsuite runtests

runspeeds:
	@$(MAKE) -C testsuite runspeeds

#
# MESSAGE
#

print:
	@echo ''
	@echo '**************************'
	@echo '** OOC-2.0 CORE LIBRARY **'
	@echo '**************************'
	@echo ''
