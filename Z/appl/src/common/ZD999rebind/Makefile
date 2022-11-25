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

DBNAME	 = labokns
UID	 = nxtgene
PASWD	 = nxtgene

DBX		 = -g
#DBG		 = -D_TRACE
CFLAGS   = -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/appl/lib -lbmlcom
MAKEHOME = $(HOME)/appl/src/common/ZD999rebind
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
INCS	 = 
OBJS	 = $(OBJ_DIR)/ZD999rebind.o \

EXECM	 = ZD999rebind

message	 : $(EXECM)
	@echo Makeup

%.o		 : %.c $(INCS) Makefile
	cc -c $< $(CFLAGS) $(DBX) $(DBG)

install	 : message
	$(CP) -p $(EXECM) $(BIN_DIR)

clean	 :
	$(RM) $(EXECM) *.o

$(EXECM)	 : $(OBJS)
	cc -o $(EXECM) $(OBJS) $(LDFLAGS) $(DBX)
