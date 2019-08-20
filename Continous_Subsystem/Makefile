SYSTEMC=$$SYSTEMC_HOME
SYSTEMC_AMS=$$SCAMS_HOME


EXECUTABLE=bin/plant.x
CONTROLLER=Controller_TLM
VALVE=Valve
TANK=Water_tank
MAIN=main_ams
TB = AMS-testbench

TLM = TLM
RTL = RTL
AMS = AMS
TRANS = transactor

PLATFORM= $(shell uname -s)
ARCH=$(shell getconf LONG_BIT)

ifeq ($(PLATFORM),Darwin)
SYSC_LIBDIR := $(SYSTEMC)/lib-macosx
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-macosx
endif
ifeq ($(PLATFORM),Linux)
SYSC_LIBDIR := $(SYSTEMC)/lib-linux
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-linux
endif

ifeq ($(ARCH),64)
SYSC_LIBDIR := $(SYSC_LIBDIR)64
SCAMS_LIBDIR := $(SCAMS_LIBDIR)64
endif

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a   $(SYSC_LIBDIR)/libsystemc.a -lpthread

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/ -I$(SYSTEMC_AMS)/include


CXX=g++
CFLAGS= -c
LD=g++

all: $(EXECUTABLE)

clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f $(EXECUTABLE)
	@rm -f water.vcd

$(EXECUTABLE): obj/$(MAIN).o \
	obj/$(TB).o \
	obj/$(VALVE).o \
	obj/$(TANK).o \
	obj/$(AMS)-$(RTL)_$(TRANS).o \
	obj/$(RTL)-$(TLM)_$(TRANS).o \
	obj/$(CONTROLLER).o \
	obj/$(TLM)-$(RTL)_$(TRANS).o \
	obj/$(RTL)-$(AMS)_$(TRANS).o 

	@echo Building $@
	@ $(LD) -o $@ $(INCDIR) $^ $(LIBS)
#MAIN
obj/$(MAIN).o: src/$(MAIN).cpp
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
#TESTBENCH
obj/$(TB).o: src/$(TB).cpp include/$(TB).hpp
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
#CONTROLLER
obj/$(CONTROLLER).o: src/$(CONTROLLER).cpp include/$(CONTROLLER).hpp
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
#TLM-RTL
obj/$(TLM)-$(RTL)_$(TRANS).o: src/$(TLM)-$(RTL)_$(TRANS).cpp \
							  include/$(TLM)-$(RTL)_$(TRANS).hpp
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
#RTL-AMS
obj/$(RTL)-$(AMS)_$(TRANS).o: src/$(RTL)-$(AMS)_$(TRANS).cpp \
							  include/$(RTL)-$(AMS)_$(TRANS).hpp
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
#VALVOLA
obj/$(VALVE).o: src/$(VALVE).cpp include/$(VALVE).hpp 
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
#TANK
obj/$(TANK).o: src/$(TANK).cpp include/$(TANK).hpp
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
#AMS-RTL
obj/$(AMS)-$(RTL)_$(TRANS).o: src/$(AMS)-$(RTL)_$(TRANS).cpp \
							  include/$(AMS)-$(RTL)_$(TRANS).hpp
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
#RTL-TLM
obj/$(RTL)-$(TLM)_$(TRANS).o: src/$(RTL)-$(TLM)_$(TRANS).cpp \
							  include/$(RTL)-$(TLM)_$(TRANS).hpp
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

.PHONY: all clean	


