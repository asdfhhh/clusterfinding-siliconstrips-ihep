# $Id: GNUmakefile,v 1.25 2010-01-11 14:29:03 gcosmo Exp $
# --------------------------------------------------------------
# GNUmakefile for DmpSimulation.  Xin Wu, 09/07/13.
# --------------------------------------------------------------

name := DmpSimu
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../..
endif

.PHONY: all
all:  had_list lib bin

had_list:
	@echo "Dampe Detector simulation executable"

G4ANALYSIS_USE := true

include $(G4INSTALL)/config/binmake.gmk

histclean:
	rm ${G4WORKDIR}/tmp/${G4SYSTEM}/${G4TARGET}/HistoManager.o


ifdef ROOTSYS
  CPPFLAGS += -I$(shell $(ROOTSYS)/bin/root-config --incdir)
  CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
  LDLIBS += $(shell $(ROOTSYS)/bin/root-config --libs)

   ifeq ($(G4SYSTEM),Linux-g++)
     LDLIBS += -Wl,-rpath,$(shell $(ROOTSYS)/bin/root-config --libdir)
   endif
endif
