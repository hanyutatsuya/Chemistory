######################################################
# FILE NAME		: Makefile
# Exectable Module	: BD305
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
CP       = /bin/cp

DBNAME   = KEA00DB9
UID      = kea00dbt
PASWD    = kea00dbt


DBX		 = -g
DBG		 = -D_TRACE
CFLAGS   = -I$(HOME)/sqllib/include \
		   -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 \
		   -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/hansou/BD305
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
INCS	 = $(INC_DIR)/BD305.h 
OBJS	 = BD305.o \
		   BD305_01.o

EXECM	 = BD305

message	 : $(EXECM)
	@echo Makeup

%.o		 : %.sqc $(INCS) Makefile
	db2 connect to $(DBNAME) user $(UID) using $(PASWD)
	db2 prep $*.sqc bindfile using $*.bnd
	db2 bind $*.bnd
	db2 terminate
	cc -c $*.c $(CFLAGS) $(DBX) $(DBG)
	$(RM) $*.c

%.o		 : %.c $(INCS) Makefile
	cc -c $< $(CFLAGS) $(DBX) $(DBG)

install	 : message
	$(CP) -p $(EXECM) $(BIN_DIR)

clean	 :
	$(RM) $(EXECM) *.o

BD305	 : $(OBJS)
	cc -o BD305 $(OBJS) $(LDFLAGS) $(DBX)
