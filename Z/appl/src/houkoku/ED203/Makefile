######################################################
# FILE NAME         : Makefile
# Exectable Module  : ED203
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
MAKEHOME = $(HOME)/appl/src/houkoku/ED203
EXE_DIR  = $(HOME)/appl/src/houkoku/ED203
SRC_DIR  = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR  = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/ED203

INCS =  $(INC_DIR)/ED203Main.h \
        $(INC_DIR)/ED203Hkkknri.h \
        $(INC_DIR)/ED203Kekka.h

OBJS =  $(OBJ_DIR)/ED203Main.o \
        $(OBJ_DIR)/ED203Hkkknri.o \
        $(OBJ_DIR)/ED203Kekka.o

all : $(TARGET)

$(TARGET)   :   $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/ED203Main.o  :   $(SRC_DIR)/ED203Main.c $(INCS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ED203Main.c -I$(INC_DIR)

$(OBJ_DIR)/ED203Hkkknri.o   :   $(SRC_DIR)/ED203Hkkknri.sqc $(INC_DIR)/ED203Hkkknri.h
	$(MAKEHOME)/embprep $(SRC_DIR)/ED203Hkkknri $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/ED203Hkkknri.c

$(OBJ_DIR)/ED203Kekka.o :   $(SRC_DIR)/ED203Kekka.sqc $(INC_DIR)/ED203Kekka.h
	$(MAKEHOME)/embprep $(SRC_DIR)/ED203Kekka $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/ED203Kekka.c

clean :
	$(RM) -f $(OBJS) $(TARGET)
