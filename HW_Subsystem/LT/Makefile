MODULE_NAME=XTEA_LT
MAIN=main_$(MODULE_NAME)
TESTBENCH=$(MODULE_NAME)_testbench

EXECUTABLE=bin/$(MODULE_NAME).x

SYSC=$$SYSTEMC_HOME

PLATFORM= $(shell uname -s)
ARC=$(shell getconf LONG_BIT)

ifeq ($(PLATFORM),Darwin)
SYSC_LIBDIR := $(SYSC)/lib-macosx
endif
ifeq ($(PLATFORM),Linux)
SYSC_LIBDIR := $(SYSC)/lib-linux
endif

ifeq ($(ARC),64)
SYSC_LIBDIR := $(SYSC_LIBDIR)64
endif

INCLUDE_DIRECTORIES_FLAGS=-I./include/ -I. -I$(SYSC)/include/

LIBS = $(SYSC_LIBDIR)/libsystemc.a -lpthread

CXX=g++
CFLAGS=-c
LD=g++

all: $(EXECUTABLE)

$(EXECUTABLE): obj/$(MAIN).o obj/$(TESTBENCH).o obj/$(MODULE_NAME).o
	@echo Building $@
	$(CXX) -g $(INCLUDE_DIRECTORIES_FLAGS) -o $@ $^ $(LIBS)

obj/$(MAIN).o : src/$(MAIN).cpp
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCLUDE_DIRECTORIES_FLAGS) -o $@ $<

obj/$(TESTBENCH).o : src/$(TESTBENCH).cpp include/$(TESTBENCH).hpp
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCLUDE_DIRECTORIES_FLAGS) -o $@ $<

obj/$(MODULE_NAME).o : src/$(MODULE_NAME).cpp include/$(MODULE_NAME).hpp
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCLUDE_DIRECTORIES_FLAGS) -o $@ $<

clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f $(EXECUTABLE)

.PHONY: all clean
