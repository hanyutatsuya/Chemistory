######################################################
# FILE NAME         : Makefile
# Exectable Module  : JD112
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   06/03/23   H.Suyama Create
#
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
DBNAME   = kea00db
UID      = db2inst1
PASWD    = db2inst1
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -D_TRACE -g
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -lpthread -L$(HOME)/appl/lib -lbmlcom -lbmldb
AAA =  -L/usr/lib -lpthread
MAKEHOME = $(HOME)/appl/src/syoukai/JD112
EXE_DIR  = $(HOME)/appl/src/syoukai/JD112
SRC_DIR  = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR  = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/JD112

INCS =  $(INC_DIR)/JD112Main.h \
	$(INC_DIR)/JD112Sysknrmst.h \
	$(INC_DIR)/JD112Knssnkjyk.h \
	$(INC_DIR)/JD112Syukei.h

OBJS =  $(OBJ_DIR)/JD112Main.o \
	$(OBJ_DIR)/JD112Sysknrmst.o \
	$(OBJ_DIR)/JD112Knssnkjyk.o \
	$(OBJ_DIR)/JD112Syukei.o \
	$(OBJ_DIR)/JD112Memst.o

all : $(TARGET)

$(TARGET)   :   $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/JD112Main.o  :   $(SRC_DIR)/JD112Main.c $(INCS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/JD112Main.c -I$(INC_DIR)

$(OBJ_DIR)/JD112Sysknrmst.o   :   $(SRC_DIR)/JD112Sysknrmst.sqc $(INC_DIR)/JD112Sysknrmst.h
	$(MAKEHOME)/embprep $(SRC_DIR)/JD112Sysknrmst $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/JD112Sysknrmst.c

$(OBJ_DIR)/JD112Knssnkjyk.o   :   $(SRC_DIR)/JD112Knssnkjyk.sqc $(INC_DIR)/JD112Knssnkjyk.h
	$(MAKEHOME)/embprep $(SRC_DIR)/JD112Knssnkjyk $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/JD112Knssnkjyk.c

$(OBJ_DIR)/JD112Syukei.o   :   $(SRC_DIR)/JD112Syukei.sqc $(INC_DIR)/JD112Syukei.h
	$(MAKEHOME)/embprep $(SRC_DIR)/JD112Syukei $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/JD112Syukei.c

$(OBJ_DIR)/JD112Memst.o   :   $(SRC_DIR)/JD112Memst.sqc $(INCS)
	$(MAKEHOME)/embprep $(SRC_DIR)/JD112Memst  $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/JD112Memst.c

clean :
	$(RM) -f $(OBJS) $(TARGET)
