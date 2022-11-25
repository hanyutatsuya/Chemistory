######################################################
# FILE NAME		: Makefile
# Exectable Module	: LD106
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

DBNAME   = KEA00DB
UID      = db2inst1
PASWD    = db2inst1


DBX		 = -g -Wall
DBG		 = -D_TRACE
CFLAGS   = -I$(HOME)/sqllib/include \
		   -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -lm \
		   -L$(HOME)/appl/lib -lbmlcom -lbmldb
BMLHOME  = $(HOME)/appl
MAKEHOME = $(HOME)/appl/src/calc/LD106
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
LIB_DB_DIR  = $(BMLHOME)/lib
ADD_LIB = \
	$(LIB_DB_DIR)/libbmlcom.a \
	$(LIB_DB_DIR)/libbmldb.a

INCS	 = $(INC_DIR)/LD106.h \
	   $(INC_DIR)/LD106_db.h 
OBJS	 = LD106.o \
	   LD106_chk.o \
	   LD106_dat.o \
	   LD106_mst.o \
	   common_str.o 

EXECM	 = LD106

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

LD106	 : $(OBJS) $(ADD_LIB)
	cc -o LD106 $(OBJS) $(LDFLAGS) $(DBX)
