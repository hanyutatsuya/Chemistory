######################################################
# FILE NAME		: Makefile
# Exectable Module	: ZD101
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

DBNAME	 = kea00db
UID	 = db2inst1
PASWD	 = db2inst1

DBX		 = -g
#DBG		 = -D_TRACE
CFLAGS   = -I$(HOME)/sqllib/include \
		   -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 \
		   -L$(HOME)/appl/lib -lbmlcom -lbmldb 
MAKEHOME = $(HOME)/appl/src/common/ZD101
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET	 = $(EXE_DIR)/ZD101
INCS	 = $(INC_DIR)/ZD101.h 
OBJS	 = $(OBJ_DIR)/ZD101.o \
		   $(OBJ_DIR)/ZD101_01.o 

EXECM	 = ZD101

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

ZD101	 : $(OBJS)
	cc -o ZD101 $(OBJS) $(LDFLAGS) $(DBX)
