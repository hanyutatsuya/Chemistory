######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbmldb.a
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   05/08/25   J.iijima Create
#
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
DBNAME	 = KEA00DB
UID	 = db2inst1
PASWD	 = db2inst1
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -g
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/qc/FD101
EXE_DIR	 = $(HOME)/appl/src/qc/FD101
#MAKEHOME = $(HOME)/appl/src/common/FD101
#EXE_DIR	 = $(HOME)/appl/src/common/FD101
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/FD101
INCS =	$(INC_DIR)/F101ctrlijhmst.h	\
		$(INC_DIR)/F101ctrlkka.h	\
		$(INC_DIR)/FD101IjouChk.h

OBJS =	$(OBJ_DIR)/F101clijhmst.o \
		$(OBJ_DIR)/F101clka.o	\
		$(OBJ_DIR)/FD101IjouChk.o

SQLCS =	$(OBJ_DIR)/F101clijhmst.c \
		$(OBJ_DIR)/F101clka.c


all	: $(TARGET)

$(TARGET)	:	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/FD101IjouChk.o	:	$(SRC_DIR)/FD101IjouChk.c $(INCS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/FD101IjouChk.c -I$(INC_DIR)

$(OBJ_DIR)/F101clijhmst.c	:	$(SRC_DIR)/F101clijhmst.sqc $(INCS)
	./embprep $(SRC_DIR)/F101clijhmst $(DBNAME) $(UID) $(PASWD)
$(OBJ_DIR)/F101clijhmst.o	:	$(SRC_DIR)/F101clijhmst.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/F101clijhmst.c

$(OBJ_DIR)/F101clka.c	:	$(SRC_DIR)/F101clka.sqc $(INCS)
	./embprep $(SRC_DIR)/F101clka $(DBNAME) $(UID) $(PASWD)
$(OBJ_DIR)/F101clka.o	:	$(SRC_DIR)/F101clka.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/F101clka.c

clean :
	$(RM) -f $(OBJS) $(TARGET) $(SQLCS)
