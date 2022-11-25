######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbmldb.a
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.01  07/03/13   T.Wajima Update
#
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
CP       = /bin/cp
DBNAME	 = kea00db
UID    	 = db2inst1
PASWD    = db2inst1
VER		= 9
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -g
##CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -D_TRACE -D_DEBUG_ -g
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -lm -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/kosei/FD103
EXE_DIR	 = $(HOME)/appl/src/kosei/FD103
BIN_DIR  = $(HOME)/appl/src/kosei/FD103
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/FD103
INCS =	$(INC_DIR)/FD103.h

OBJS =	FD103.o \
		CheckHist.o \
		KoseiKaHi.o \
		jidoKousei.o

EXECM = FD103

all	: $(TARGET)

message  : $(EXECM)
	@echo Makeup

$(TARGET)	:	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o		: %.sqc $(INCS)
	./embprep01 $* $(DBNAME) $(UID) $(PASWD) $(VER)
	$(CC) $(CFLAGS) -c $*.c -I$(INC_DIR)
#	$(RM) $*.c

%.o      : %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -I$(INC_DIR)

install	: message
	$(CP) -p $(EXECM) $(BIN_DIR)

clean :
	$(RM) -f $(OBJS) $(TARGET) *.bnd

