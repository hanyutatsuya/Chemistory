######################################################
# FILE NAME		: Makefile
# Exectable Module	: AD107
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

DBX		 = -g
DBG		 = -D_TRACE
CFLAGS   = -I$(HOME)/sqllib/include \
		   -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 \
		   -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/bunchu/AD107
EXE_DIR	 = $(HOME)/appl/src/bunchu/AD107
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET	 = $(EXE_DIR)/AD107
INCS	 = $(INC_DIR)/AD107.h 
OBJS	 = AD107.o

EXECM	 = AD107

message	 : $(EXECM)
	@echo Åö Makeup Åö

%.o		 : %.c $(INCS) Makefile
	cc -c $< $(CFLAGS) $(DBX) $(DBG)

install	 : message
	$(CP) -p $(EXECM) $(BIN_DIR)

clean	 :
	$(RM) $(EXECM) *.o

AD107	 : $(OBJS)
	cc -o AD107 $(OBJS) $(LDFLAGS) $(DBX)
