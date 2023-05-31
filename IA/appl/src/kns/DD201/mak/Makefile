######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbml.a
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   06/03/03   A.Yamada Create
#  2.0   08/12/02   K.Ameno X-MëŒâûèâî≈
#
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
#DEBUG	 = -g -D _TRACE -Wall
DEBUG	 = -g
CFLAGS   = -DDEBUG -I$(HOME)/sqllib/include
#lDFLAGS  = -ldb2 -lbml
LDFLAGS  = -lbmlcom -lm -lrt
BMLHOME  = $(HOME)/appl
MAKEHOME = $(HOME)/appl/src/kns/test/DD201
EXE_DIR  = $(HOME)/appl/src/kns/test/DD201/src
# EXE_DIR	 = $(HOME)/bin
LIB_DB_DIR  = $(BMLHOME)/lib
INC_DB_DIR  = $(BMLHOME)/inc
INC_SUB_DIR = $(BMLHOME)/inc
MAKE_DIR = $(MAKEHOME)/mak
SRC_DIR  = $(MAKEHOME)/src
INC_DIR  = $(MAKEHOME)/inc
OBJ_DIR	 = $(SRC_DIR)
TARGET  = $(EXE_DIR)/DD201
FLG_INC = -I$(INC_DB_DIR) -I$(INC_SUB_DIR) -I$(INC_DIR)
FLG_LIB = -L$(LIB_DB_DIR) -L$(HOME)/sqllib/lib
ADD_LIB	= \
	$(LIB_DB_DIR)/libbmlcom.a 
ADD_OBJ	= $(MAKEHOME)/../../comm/kns_common.o

INCS = \
	$(INC_DIR)/DD201.h		\
	$(INC_DIR)/DD40101.h	\
	$(INC_DIR)/Socket.h	\
	$(INC_DIR)/SndData.h	\
	$(INC_DIR)/RcvData.h	\
	$(INC_DIR)/Connect.h	\
	$(INC_DIR)/GetKenorder.h	\
	$(INC_DIR)/OutputKekka.h	\
	$(INC_DIR)/OutputComLog.h	\
	$(INC_DIR)/OutputCtrlkka.h	\
	$(INC_DIR)/OutputXbarm.h	\
	$(INC_DIR)/GetMaster.h \
	$(INC_DIR)/KSNSK_if.h \
	$(INC_DIR)/Kskbrmst2.h 


OBJS = \
	$(OBJ_DIR)/DD201.o	\
	$(OBJ_DIR)/DD40101.o	\
	$(OBJ_DIR)/Socket.o	\
	$(OBJ_DIR)/SndData.o	\
	$(OBJ_DIR)/RcvData.o	\
	$(OBJ_DIR)/Connect.o	\
	$(OBJ_DIR)/GetKenorder.o	\
	$(OBJ_DIR)/OutputKekka.o	\
	$(OBJ_DIR)/OutputComLog.o	\
	$(OBJ_DIR)/OutputCtrlkka.o	\
	$(OBJ_DIR)/OutputXbarm.o	\
	$(OBJ_DIR)/GetMaster.o	\
	$(OBJ_DIR)/common_str.o	\
	$(OBJ_DIR)/KSNSK_if.o 

all : $(TARGET)

$(OBJS) : $(INCS)

$(TARGET) : $(OBJS) $(ADD_LIB) $(ADD_OBJ)
	$(CC) -o $@ $(OBJS) $(ADD_OBJ) $(ADD_LIB) $(DEBUG) $(CFLAGS) $(FLG_INC) $(FLG_LIB) $(LDFLAGS)

.c.o :
	$(CC) -c $< $(CFLAGS) $(DEBUG) $(FLG_INC) -o $@

clean :
	$(RM) -f $(TARGET) $(OBJS)
