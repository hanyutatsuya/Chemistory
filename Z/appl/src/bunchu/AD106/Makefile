######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbmldb.a
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   05/08/25   E.osda Create
#
######################################################
CC	 = /usr/bin/gcc
AR	 = /usr/bin/ar
RM	 = /bin/rm
MV	 = /bin/mv
CP	 = /bin/cp
DBNAME	 = kea00db
UID	 = db2inst1
PASWD	 = db2inst1
BUN_DIR  = $(HOME)/appl/src/bunchu/AD105
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -I$(BUN_DIR) -D_TRACE -g
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmldb -lbmlcom
LDFLAGS1 = $(BUN_DIR)/A105knja.o $(BUN_DIR)/A105irai.o
MAKEHOME = $(HOME)/appl/src/bunchu/AD106
EXE_DIR	 = $(HOME)/appl/src/bunchu/AD106
BIN_DIR  = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET	 = $(EXE_DIR)/AD106
INCS = \
		$(INC_DIR)/AD106.h

OBJS =	\
		$(OBJ_DIR)/AD106.o
EXECM = AD106

all	: $(TARGET)

message  : $(EXECM)
	@echo Makeup

$(TARGET)	:	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS1) $(LDFLAGS)

%.o		: %.sqc 
	embprep $* $(DBNAME) $(UID) $(PASWD)
	$(CC) $(CFLAGS) -c $*.c -I$(INC_DIR)
#	$(RM) $*.c

%.o      : %.c $(INCS) Makefile $(BUN_DIR)/A105irai.o $(BUN_DIR)/A105knja.o
	$(CC) $(CFLAGS) -c $< -I$(INC_DIR)

install : message
	$(CP) -p $(EXECM) $(BIN_DIR)

clean :
	$(RM) -f $(OBJS) $(TARGET)
