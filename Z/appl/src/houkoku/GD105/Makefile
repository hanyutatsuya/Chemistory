######################################################
# FILE NAME         : Makefile
# Exectable Module  : GD105
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   06/03/07   H.Suyama Create
#
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
DBNAME   = kea00db
UID      = db2inst1
PASWD    = db2inst1
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/houkoku/GD105
EXE_DIR  = $(HOME)/appl/src/houkoku/GD105
SRC_DIR  = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR  = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/GD105

INCS =  $(INC_DIR)/GD105Main.h \
        $(INC_DIR)/GD105KkaConvChk.h \
        $(INC_DIR)/GD105Sysknrmst.h \
        $(INC_DIR)/GD105Hkkknri.h \
        $(INC_DIR)/GD105Kekka.h \
        $(INC_DIR)/GD105Kanjya.h \
        $(INC_DIR)/GD105Kenzok.h \
        $(INC_DIR)/GD105KekkaConv.h \
        $(INC_DIR)/GD105Kkaconvknr.h \
        $(INC_DIR)/GD105Kkaconvmst.h

OBJS =  $(OBJ_DIR)/GD105Main.o \
        $(OBJ_DIR)/GD105KkaConvChk.o \
        $(OBJ_DIR)/GD105Sysknrmst.o \
        $(OBJ_DIR)/GD105Hkkknri.o \
        $(OBJ_DIR)/GD105Kekka.o \
        $(OBJ_DIR)/GD105sstknz.o \
        $(OBJ_DIR)/GD105GetKkassflg.o \
        $(OBJ_DIR)/GD105Kanjya.o \
        $(OBJ_DIR)/GD105Kenzok.o \
        $(OBJ_DIR)/GD105KekkaConv.o \
        $(OBJ_DIR)/GD105Kkaconvknr.o \
        $(OBJ_DIR)/GD105Kkaconvmst.o

all : $(TARGET)

$(TARGET)   :   $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

.c.o :
	$(CC) -c $< $(CFLAGS) $(DEBUG) $(FLG_INC) -o $@

clean :
	$(RM) -f $(OBJS) $(TARGET)
