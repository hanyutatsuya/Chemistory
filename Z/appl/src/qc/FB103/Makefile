######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbmldb.a
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   06/03/10   J.iijima Create
#
######################################################
CC       = /usr/bin/gcc 
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
DBNAME	 = KEA00DB
UID	 = db2inst1
PASWD	 = db2inst1
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc 
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/qc/FB103
EXE_DIR	 = $(HOME)/appl/src/qc/FB103
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/FB103
INCS =	$(INC_DIR)/FB103Jidokousei.h \
		$(INC_DIR)/F103ctrlkka.h	\
		$(INC_DIR)/F103ctrlknr.h	\
		$(INC_DIR)/F103kekka.h

OBJS =	$(OBJ_DIR)/FB103Jidokousei.o \
		$(OBJ_DIR)/F103clkka.o \
		$(OBJ_DIR)/F103clknr.o	\
		$(OBJ_DIR)/F103kekka.o 
		
SQLCS =	$(OBJ_DIR)/F103clkka.c \
	$(OBJ_DIR)/F103clknr.c \
	$(OBJ_DIR)/F103kekka.c

all	: $(TARGET)

$(TARGET)	:	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/FB103Jidokousei.o	:	$(SRC_DIR)/FB103Jidokousei.c $(INCS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/FB103Jidokousei.c -I$(INC_DIR)

$(OBJ_DIR)/F103clkka.c	:	$(SRC_DIR)/F103clkka.sqc $(INCS) 
	./embprep $(SRC_DIR)/F103clkka $(DBNAME) $(UID) $(PASWD)
$(OBJ_DIR)/F103clkka.o	:	$(SRC_DIR)/F103clkka.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/F103clkka.c

$(OBJ_DIR)/F103clknr.c	:	$(SRC_DIR)/F103clknr.sqc $(INCS) 
	./embprep $(SRC_DIR)/F103clknr $(DBNAME) $(UID) $(PASWD)
$(OBJ_DIR)/F103clknr.o	:	$(SRC_DIR)/F103clknr.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/F103clknr.c

$(OBJ_DIR)/F103kekka.c	:	$(SRC_DIR)/F103kekka.sqc $(INCS) 
	./embprep $(SRC_DIR)/F103kekka $(DBNAME) $(UID) $(PASWD)
$(OBJ_DIR)/F103kekka.o	:	$(SRC_DIR)/F103kekka.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/F103kekka.c

clean :
	$(RM) -f $(OBJS) $(TARGET) $(SQLCS)
