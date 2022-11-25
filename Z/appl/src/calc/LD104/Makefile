######################################################
# FILE NAME         : Makefile
# Exectable Module  : LD104
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   19/12/07   BML.inc Create
#
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
DBNAME   = kea00db
UID      = db2inst1
PASWD    = db2inst1
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc
#LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb -g -Wall
MAKEHOME = $(HOME)/appl/src/calc/LD104
EXE_DIR  = $(HOME)/appl/src/calc/LD104
SRC_DIR  = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR  = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/LD104

INCS =  $(INC_DIR)/LD104.h \
        $(INC_DIR)/LD104Sysknrmst.h \
        $(INC_DIR)/LD104GetKekka.h

OBJS =  $(OBJ_DIR)/LD104.o \
        $(OBJ_DIR)/LD104Sysknrmst.o \
        $(OBJ_DIR)/LD104GetKekka.o

all : $(TARGET)

$(TARGET)   :   $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

.c.o :
	$(CC) -c $< $(CFLAGS) $(DEBUG) $(FLG_INC) -o $@

clean :
	$(RM) -f $(OBJS) $(TARGET)
