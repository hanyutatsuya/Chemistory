######################################################
# FILE NAME		: Makefile
# Exectable Module	: cis_socket.c
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   99/04/12   Create
#
######################################################
CC = /usr/bin/cc
AR = /usr/bin/ar
RM = /bin/rm
MV = /bin/mv
#CFLAGS   = -qdbcs -DDEBUG2 -DTAIS -g
CFLAGS   = -DDEBUG -g
MAKEHOME = $(HOME)/appl/src/kns/DD204
EXE_DIR	 = $(MAKEHOME)/src
SRC_DIR	 = $(MAKEHOME)/src
INC_DIR  = $(MAKEHOME)/src
OBJ_DIR	 = $(MAKEHOME)/src
MAKE_DIR = $(MAKEHOME)/src
#DBINC_DIR = /usr/lpp/db2_05_00/include
#DB2_LIBDIR = /usr/lpp/db2_05_00/lib 

INC      = $(INC_DIR)/bml_socket.h
OBJS = $(OBJ_DIR)/bml_tstServ.o $(OBJ_DIR)/bml_socket.o
TARGET = $(EXE_DIR)/bml_tstServ

all	: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/bml_tstServ.o : $(SRC_DIR)/bml_tstServ.c $(INC)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/bml_tstServ.c -I$(INC_DIR)

$(OBJ_DIR)/bml_socket.o	:	$(SRC_DIR)/bml_socket.c $(INC)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/bml_socket.c -I$(INC_DIR)

clean :
	$(RM) -f $(OBJS) $(TARGET)

