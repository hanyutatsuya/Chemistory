######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbml.a
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   06/03/03   A.Yamada Create
#  1.1   06/12/21   S.Nagata 実行モジュール生成位置を
#                            ソースディレクトリに変更
#  2.0   08/12/02   K.Ameno X-M対応初版
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
DEBUG	 = -g
#DEBUG	 = -g -Wall
CFLAGS   = -I$(HOME)/sqllib/include -I.
LDFLAGS  = -lbmlcom -lm -lrt
BMLHOME  = $(HOME)/appl
MAKEHOME = $(HOME)/appl/src/kns/test/comm
EXE_DIR  = $(HOME)/appl/src/kns/test/comm
LIB_DB_DIR  = $(BMLHOME)/lib
INC_DB_DIR  = $(BMLHOME)/inc
INC_SUB_DIR = $(BMLHOME)/inc
MAKE_DIR = $(MAKEHOME)/mak
SRC_DIR  = $(MAKEHOME)
INC_DIR  = $(MAKEHOME)
OBJ_DIR	 = $(SRC_DIR)
TARGET  = $(EXE_DIR)/kns_common.exe
FLG_INC = -I$(INC_DB_DIR) -I$(INC_SUB_DIR) -I$(INC_DIR)
FLG_LIB = -L$(LIB_DB_DIR) -L$(HOME)/sqllib/lib
ADD_LIB	= \
	$(LIB_DB_DIR)/libbmlcom.a 

INCS = \
	$(INC_DIR)/kns_common.h

SRCS = \
	$(SRC_DIR)/kns_common.c

OBJS = \
	$(OBJ_DIR)/kns_common.o

#all : $(TARGET)

#$(TARGET) : $(OBJS) $(ADD_LIB)
#	$(CC) -o $@ $(OBJS) $(ADD_LIB) $(DEBUG) $(CFLAGS) $(FLG_INC) $(FLG_LIB) $(LDFLAGS)
#	$(CC) -o $@ $(OBJS) $(ADD_LIB) $(CFLAGS) $(FLG_INC) $(FLG_LIB) $(LDFLAGS)

$(OBJS) : $(SRCS) $(INCS)
	$(CC) -c $(SRCS) $(CFLAGS) $(DEBUG) $(FLG_INC) -o $(OBJS)
#	$(CC) -c $< $(CFLAGS) $(FLG_INC) -o $@

clean :
#	$(RM) -f $(TARGET) $(OBJS)
	$(RM) -f $(OBJS)
