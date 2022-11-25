######################################################
# FILE NAME		: Makefile
# Exectable Module	: BD401
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#
######################################################
RM       = /bin/rm
CP       = /bin/cp

DBX		 = -g
CFLAGS   = -I$(HOME)/sqllib/include \
		   -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/appl/lib -lbmlcom 
MAKEHOME = $(HOME)/appl/src/common/ZD999IA
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
INCS	 = ZD999IA.h 
OBJS	 = ZD999IA.o 

EXECM	 = ZD999IA

message	 : $(EXECM)
	@echo Makeup

%.o		 : %.c $(INCS) Makefile
	cc -c $< $(CFLAGS) $(DBX) $(DBG)

install	 : message
	$(CP) -p $(EXECM) $(BIN_DIR)

clean	 :
	$(RM) $(EXECM) *.o

ZD999IA	 : $(OBJS)
	cc -o ZD999IA $(OBJS) $(LDFLAGS) $(DBX)
