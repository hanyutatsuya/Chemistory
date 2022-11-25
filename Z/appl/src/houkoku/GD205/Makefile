######################################################
# FILE NAME         : Makefile
# Exectable Module  : GD205
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   07/06/05   Copy from GD105
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
MAKEHOME = $(HOME)/appl/src/houkoku/GD205
EXE_DIR  = $(HOME)/appl/src/houkoku/GD205
SRC_DIR  = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR  = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/GD205

INCS =  $(INC_DIR)/GD205Main.h \
        $(INC_DIR)/GD205Sysknrmst.h \
        $(INC_DIR)/GD205Hkkknri.h \
        $(INC_DIR)/GD205Kekka.h

OBJS =  $(OBJ_DIR)/GD205Main.o \
        $(OBJ_DIR)/GD205Sysknrmst.o \
        $(OBJ_DIR)/GD205Hkkknri.o \
        $(OBJ_DIR)/GD205Kekka.o \
        $(OBJ_DIR)/GD205sstknz.o \
        $(OBJ_DIR)/GD205Getdb.o
##        $(OBJ_DIR)/GD205GetKkassflg.o \
##        $(OBJ_DIR)/GD205wscd.o

all : $(TARGET)

$(TARGET)   :   $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/GD205Main.o  :   $(SRC_DIR)/GD205Main.c $(INCS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/GD205Main.c -I$(INC_DIR)

$(OBJ_DIR)/GD205Sysknrmst.o  :   $(SRC_DIR)/GD205Sysknrmst.sqc $(INC_DIR)/GD205Sysknrmst.h
	$(MAKEHOME)/embprep $(SRC_DIR)/GD205Sysknrmst $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/GD205Sysknrmst.c

$(OBJ_DIR)/GD205Hkkknri.o   :   $(SRC_DIR)/GD205Hkkknri.sqc $(INC_DIR)/GD205Hkkknri.h
	$(MAKEHOME)/embprep $(SRC_DIR)/GD205Hkkknri $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/GD205Hkkknri.c

$(OBJ_DIR)/GD205Kekka.o :   $(SRC_DIR)/GD205Kekka.sqc $(INC_DIR)/GD205Kekka.h
	$(MAKEHOME)/embprep $(SRC_DIR)/GD205Kekka $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/GD205Kekka.c

$(OBJ_DIR)/GD205sstknz.o :   $(SRC_DIR)/GD205sstknz.sqc $(INC_DIR)/GD205Kekka.h
	$(MAKEHOME)/embprep $(SRC_DIR)/GD205sstknz $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/GD205sstknz.c

$(OBJ_DIR)/GD205Getdb.o : $(SRC_DIR)/GD205Getdb.sqc $(INC_DIR)/GD205Kekka.h
	$(MAKEHOME)/embprep $(SRC_DIR)/GD205Getdb $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/GD205Getdb.c

##$(OBJ_DIR)/GD205GetKkassflg.o : $(SRC_DIR)/GD205GetKkassflg.sqc $(INC_DIR)/GD205Kekka.h
##	$(MAKEHOME)/embprep $(SRC_DIR)/GD205GetKkassflg $(DBNAME) $(UID) $(PASWD)
##	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/GD205GetKkassflg.c

##$(OBJ_DIR)/GD205wscd.o : $(SRC_DIR)/GD205wscd.sqc
##	$(MAKEHOME)/embprep $(SRC_DIR)/GD205wscd $(DBNAME) $(UID) $(PASWD)
##	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/GD205wscd.c

clean :
	$(RM) -f $(OBJS) $(TARGET)
