######################################################
# FILE NAME		: Makefile
# Exectable Module	: MD101
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

DBX		 = -g
CFLAGS   = -I. -I$(HOME)/sqllib/include -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/ZS050/MD101
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
INCS	 = $(INC_DIR)/MD101.h 
OBJS	 = MD101.o
#OBJS	 = MD101.o \
		   lib_loging.o 

EXECM	 = MD101

message	 : $(EXECM)
	@echo Makeup

%.o		 : %.sqc $(INCS)
	cc -c $*.c $(CFLAGS) $(DBX)
	$(RM) $*.c

%.o		 : %.c $(INCS)
	cc -c $< $(CFLAGS) $(DBX) $(DBG)

install	 : message
	$(CP) -p $(EXECM) $(BIN_DIR)

clean	 :
	$(RM) $(EXECM) *.o

MD101	 : $(OBJS)
	cc -o MD101 $(OBJS) $(LDFLAGS) $(DBX)
