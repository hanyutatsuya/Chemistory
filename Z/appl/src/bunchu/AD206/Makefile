######################################################
# FILE NAME		: Makefile
# Exectable Module	: AD206
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#
######################################################
CC	 = /usr/bin/gcc
AR	 = /usr/bin/ar
RM	 = /bin/rm
MV	 = /bin/mv
CP	 = /bin/cp

DBNAME   = KEA00DB
UID      = db2inst1
PASWD    = db2inst1

DBX		 = -g
DBG		 = -D_TRACE
##DBG		 = -D_TRACE -D_DEBUG_LOG
CFLAGS   = -I$(HOME)/sqllib/include \
		   -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 \
		   -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/bunchu/AD206
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET	 = $(EXE_DIR)/AD206
INCS	 = $(INC_DIR)/AD206.h 
OBJS	 = AD206.o \
		   AD206_01.o \
		   A206syskan.o \
		   lib_loging.o 

EXECM	 = AD206 

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

AD206	: $(OBJS)
	cc -o $(EXECM) $(OBJS) $(LDFLAGS) $(DBX)
