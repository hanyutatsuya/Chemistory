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
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
CP       = /bin/cp
DBNAME	 = kea00db
UID	 = db2inst1
PASWD	 = db2inst1
VER	 = 0
CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -D_TRACE -g
#CFLAGS   = -I$(HOME)/sqllib/include -I$(HOME)/appl/inc -D_TRACE -g -Wall
LDFLAGS  = -L$(HOME)/sqllib/lib -ldb2 -L$(HOME)/appl/lib -lbmlcom -lbmldb
MAKEHOME = $(HOME)/appl/src/bunchu/AD105
EXE_DIR	 = $(HOME)/appl/src/bunchu/AD105
BIN_DIR  = $(HOME)/bin
SRC_DIR	 = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(MAKEHOME)
MAKE_DIR = $(MAKEHOME)
TARGET  = $(EXE_DIR)/AD105
INCS =	$(INC_DIR)/AD105Buntekai.h \
		$(INC_DIR)/A105knja.h	\
		$(INC_DIR)/A105irai.h	\
		$(INC_DIR)/A105zoku.h	\
		$(INC_DIR)/A105syskan.h \
		$(INC_DIR)/A105bunchu.h \
		$(INC_DIR)/A105ninsiki.h \
		$(INC_DIR)/A105knsgmst.h \
		$(INC_DIR)/A105korder.h \
		$(INC_DIR)/A105realchk.h \
		$(INC_DIR)/A105rngchk.h \
		$(INC_DIR)/A105sknchk.h \
		$(INC_DIR)/A105Jdkmk.h \
		$(INC_DIR)/A105kmkmst.h \
		$(INC_DIR)/A105kjnmst.h \
		$(INC_DIR)/A105wsseq.h \
		$(INC_DIR)/A105krkmk.h \
		$(INC_DIR)/A105trmst.h \
		$(INC_DIR)/A105rkmst.h

OBJS =	AD105Buntekai.o \
		AD105BunOther.o \
		A105irai.o	\
		A105knja.o	\
		A105zoku.o	\
		A105syskan.o \
		A105bunchu.o \
		A105ninsiki.o \
		A105knsgmst.o \
		A105korder.o \
		A105realchk.o \
		A105rngchk.o \
		A105sknchk.o \
		A105Jdkmk.o \
		A105kjnmst.o \
		A105kmkmst.o \
		A105wsseq.o \
		A105krkmk.o \
		A105cntBunchu.o \
		A105trmst.o \
		A105Calckmkmst.o \
		A105rkmst.o

EXECM = AD105

all	: $(TARGET)

message  : $(EXECM)
	@echo Makeup

$(TARGET)	:	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o		: %.sqc $(INCS)
	./embprep01 $* $(DBNAME) $(UID) $(PASWD) $(VER)
	$(CC) $(CFLAGS) -c $*.c -I$(INC_DIR)
	$(RM) $*.c

%.o      : %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -I$(INC_DIR)

install	: message
	$(CP) -p $(EXECM) $(BIN_DIR)

clean :
	$(RM) -f $(OBJS) $(TARGET)

