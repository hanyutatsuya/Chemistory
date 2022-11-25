######################################################
# FILE NAME		: Makefile
# Exectable Module	: RirekiConv
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
DBG		 = -D_TRACE
CFLAGS   = -I$(HOME)/appl/inc -I.
LDFLAGS  = 
MAKEHOME = $(HOME)/appl/src/common/RirekiConv
BIN_DIR	 = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
INCS	 = 

RirekiConv	 : RirekiConv.c $(INCS) Makefile 
	cc -o RirekiConv RirekiConv.c $(CFLAGS) $(LDFLAGS) $(DBX)
