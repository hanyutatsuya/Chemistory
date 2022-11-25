######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbmldb.a
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   05/08/25   E.osda Create
#  2.0   09/02/20   K.Ameno ‹Ù‹}EOSL‘Î‰ž
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
VER		= 1
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -g
##CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -D_TRACE -D_DEBUG_ -g
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/bunchu/AD205
EXE_DIR	 = $(HOME)/appl/src/bunchu/AD205
BIN_DIR  = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/AD205
INCS =	$(INC_DIR)/AD205Buntekai.h \
		$(INC_DIR)/A205knja.h	\
		$(INC_DIR)/A205irai.h	\
		$(INC_DIR)/A205zoku.h	\
		$(INC_DIR)/A205syskan.h \
		$(INC_DIR)/A205bunchu.h \
		$(INC_DIR)/A205ninsiki.h \
		$(INC_DIR)/A205knsgmst.h \
		$(INC_DIR)/A205korder.h \
		$(INC_DIR)/A205realchk.h \
		$(INC_DIR)/A205rngchk.h \
		$(INC_DIR)/A205sknchk.h \
		$(INC_DIR)/A205Jdkmk.h \
		$(INC_DIR)/A205kmkmst.h \
		$(INC_DIR)/A205kjnmst.h \
		$(INC_DIR)/A205wsseq.h \
		$(INC_DIR)/A205krkmk.h \
		$(INC_DIR)/A205trmst.h \
		$(INC_DIR)/A205rkmst.h

OBJS =	AD205Buntekai.o \
		AD205BunOther.o \
		A205irai.o	\
		A205knja.o	\
		A205zoku.o	\
		A205syskan.o \
		A205bunchu.o \
		A205ninsiki.o \
		A205knsgmst.o \
		A205korder.o \
		A205realchk.o \
		A205rngchk.o \
		A205sknchk.o \
		A205Jdkmk.o \
		A205kjnmst.o \
		A205kmkmst.o \
		A205wsseq.o \
		A205krkmk.o \
		A205trmst.o \
		A205cntBunchu.o \
		A205Calckmkmst.o \
		A205rkmst.o

EXECM = AD205

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
	$(RM) -f $(OBJS) $(TARGET)

