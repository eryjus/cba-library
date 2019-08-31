##===================================================================================================================
##  Makefile -- Build instructions for the CBA Runtime Library
##
##
##  -----------------------------------------------------------------------------------------------------------------
##
##     Date      Tracker  Version  Programmer  Description
##  -----------  -------  -------  ----------  ----------------------------------------------------------------------
##  2019-Aug-30  Initial   0.0.0      ADCL     Initial version
##
##===================================================================================================================


.SILENT:


##
## -- commands and flags
##    ------------------
GCC       = gcc -c
CFLAGS   += -I inc/
CFLAGS   += -I /usr/include/mysql-cppconn-8/

AR		  = ar -cr


##
## -- Some macros to make our job easier
##    ----------------------------------
LIB=libcba.a
SRC=$(sort $(subst src/,,$(wildcard src/*.cc)))
OBJ=$(subst .cc,.o,$(SRC))



.PHONY: all
all: lib/$(LIB) bin/test

bin/test: obj/$(OBJ)
	mkdir -p bin
	gcc -o $@ $< -lmysqlcppconn8 -lstdc++


lib/$(LIB): obj/$(OBJ)
	mkdir -p lib
	$(AR) $@ $<


obj/%.o: src/%.cc
	mkdir -p obj
	$(GCC) $(CFLAGS) -o $@ $<
