#
##############################
# OOC Utils makefile
# -----
# Object Oriented C Library
#
# Author: Laurent Deniau, Laurent.Deniau@cern.ch
#
# $Id: Makefile,v 1.4 2005/12/01 13:54:44 ldeniau Exp $
#
# For more information, please see the paper:
# http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
#
##############################
#

ifndef $(TOPDIR)
TOPDIR = $(shell cd .. ; pwd)
include $(TOPDIR)/.config
endif

#
# FILE LISTS
#


GETLIB_HDRLIST =
GETLIB_SRCLIST = getlib.c
GETLIB_OBJLIST = $(GETLIB_SRCLIST:.c=.o)
GETLIB_EXE     = getlib

#
# EXE
#

getlib: $(GETLIB_OBJLIST)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(GETLIB_OBJLIST) -o $(GETLIB_EXE)

$(GETLIB_OBJLIST): $(GETLIB_HDRLIST) $(GETLIB_SRCLIST)

#
# CLEAN
#

include $(TOPDIR)/Makefile.clean

cleangetlib:
	rm -f $(GETLIB_EXE)

cleanall: clean cleanobj cleancpp cleanbak cleangetlib
