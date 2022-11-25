######################################################
# FILE NAME         : Makefile
# Exectable Module  : GD102
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
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -D_TRACE -g
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/houkoku/GD102
EXE_DIR  = $(HOME)/appl/src/houkoku/GD102
SRC_DIR  = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR  = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/GD102

INCS =  $(INC_DIR)/GD102Main.h \
        $(INC_DIR)/GD102Hkkknri.h

OBJS =  $(OBJ_DIR)/GD102Main.o \
        $(OBJ_DIR)/GD102Hkkknri.o

all : $(TARGET)

$(TARGET)   :   $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/GD102Main.o  :   $(SRC_DIR)/GD102Main.c $(INCS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/GD102Main.c -I$(INC_DIR)

$(OBJ_DIR)/GD102Hkkknri.o   :   $(SRC_DIR)/GD102Hkkknri.sqc $(INC_DIR)/GD102Hkkknri.h
	$(MAKEHOME)/embprep $(SRC_DIR)/GD102Hkkknri $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/GD102Hkkknri.c

clean :
	$(RM) -f $(OBJS) $(TARGET)
