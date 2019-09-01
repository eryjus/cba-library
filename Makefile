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
## -- Some macros to help with the build
##    ----------------------------------
TGT = libcba.a
SRC = $(sort $(subst src/,,$(wildcard src/*.cc)))
OBJ = $(subst .cc,.o,$(SRC))
TST = $(sort $(subst tst/,,$(wildcard tst/*.cc)))
EXE = $(subst .cc,,$(TST))

CFLAGS += -I inc/
CFLAGS += -I /usr/include/mysql-cppconn-8/
CFLAGS += -std=c++14

CC = gcc -c
AR = ar rcs


##
## -- This is the main target
##    -----------------------
.phony: all
all: lib/$(TGT) bin/$(EXE)
	rm -f core.*


##
## -- This is the main static library we are intending to build
##    ---------------------------------------------------------
lib/$(TGT): $(addprefix obj/,$(OBJ)) Makefile
	echo "AR     " $@
	mkdir -p lib
	$(AR) $@ $(addprefix obj/,$(OBJ))


##
## -- Compile a .cc source to an object
##    ---------------------------------
obj/%.o: src/%.cc Makefile
	echo "CC     " $<
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ $<


##
## -- Execute a test
##    --------------
bin/%: tst/%.cc lib/$(TGT) Makefile
	echo "TEST   " $<
	mkdir -p bin
	gcc $(CFLAGS) -Llib -o $@ $< -lcba -lmysqlcppconn8 -lstdc++
	$@