######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbml.a
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   06/01/12   S.Tunekawa Create
#
#        06/08/11   Hiwa  TARGET‚ð.NEW‚É‚·‚é
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
BNAME    = kea00db
UID      = db2inst1
PASWD    = db2inst1
#DEBUG	 = -g -Wall
DEBUG	 = -g
##CFLAGS   = -DDEBUG -D_TRACE -I$(HOME)/sqllib/include
CFLAGS   = -DDEBUG -D_TRACE -DKKAFLTMST -I$(HOME)/sqllib/include
#CFLAGS   = -DDEBUG -I$(HOME)/sqllib/include -DDEBUG2 
LDFLAGS  = -ldb2 -lpthread -lm
BMLHOME  = $(HOME)/appl
MAKEHOME = $(HOME)/appl/src/kns/DD401
EXE_DIR	 = $(HOME)/appl/src/kns/DD401
LIB_DB_DIR  = $(BMLHOME)/lib
INC_DB_DIR  = $(BMLHOME)/inc
INC_SUB_DIR = $(BMLHOME)/inc
MAKE_DIR = $(MAKEHOME)/mak
SRC_DIR  = $(MAKEHOME)/src
INC_DIR  = $(MAKEHOME)/inc
OBJ_DIR	 = $(SRC_DIR)
#TARGET  = $(EXE_DIR)/DD401.a.NEW
TARGET  = $(EXE_DIR)/DD401
FLG_INC = -I$(INC_DB_DIR) -I$(INC_SUB_DIR) -I$(INC_DIR)
FLG_LIB = -L$(LIB_DB_DIR) -L$(HOME)/sqllib/lib
ADD_LIB	= \
	$(LIB_DB_DIR)/libbmlcom.a \
	$(LIB_DB_DIR)/libbmldb.a 

INCS = \
	$(INC_DIR)/DD401.h \
	$(INC_DB_DIR)/Kekka.h \
	$(INC_DB_DIR)/Ctrlkka.h	\
	$(INC_DIR)/KSNSK_if.h

OBJS = \
	$(OBJ_DIR)/DD401.o \
	$(OBJ_DIR)/DD401_01.o \
	$(OBJ_DIR)/Kjnmst.o \
	$(OBJ_DIR)/KekkaIrai.o \
	$(OBJ_DIR)/KekkaCount.o \
	$(OBJ_DIR)/KenorderCount.o \
	$(OBJ_DIR)/KmkmstSelectCD.o \
	$(OBJ_DIR)/KskbrmstChk.o \
	$(OBJ_DIR)/KenorderRealSelect.o \
	$(OBJ_DIR)/Kkafltmst2.o \
	$(OBJ_DIR)/common_str.o \
	$(OBJ_DIR)/KSNSK_if.o \
	$(OBJ_DIR)/Xbarm.o \
	$(OBJ_DIR)/RngchkmstSelectHnikbn.o


all : $(TARGET)

$(OBJS) : $(INCS)

$(TARGET) : $(OBJS) $(ADD_LIB)
	$(CC) -o $@ $(OBJS) $(ADD_LIB) $(DEBUG) $(CFLAGS) $(FLG_LIB) $(LDFLAGS)

.c.o :
	$(CC) -c $< $(CFLAGS) $(DEBUG) $(FLG_INC) -o $@

#.sqc.c :
#	db2 connect to $(BNAME) user $(UID) using $(PASWD)
#	db2 prep $< bindfile using bnd/$*.bnd package using $*
#	db2 bind ./bnd/$*.bnd
#	db2 terminate

clean :
	$(RM) -f $(TARGET) $(OBJS)
