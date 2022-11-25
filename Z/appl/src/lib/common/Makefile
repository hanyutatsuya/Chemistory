######################################################
# FILE NAME     : Makefile
# Exectable Module  : libbmlcom.a
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#
######################################################
CC          = /usr/bin/gcc
AR          = /usr/bin/ar
RM          = /bin/rm
MV          = /bin/mv
CP          = /bin/cp

BML_INC     =  -I.
BML_OBJ     = bml_date.o \
			  bml_db.o \
			  bml_dmm.o \
			  bml_misc.o \
			  lib_bmllog.o \
			  lib_bmlprm.o \
			  lib_loging.o
TARGET      = $(HOME)/appl/lib/libbmlcom.a

message     :   $(TARGET)
	@echo Makeup

%.o :   %.c 
	cc -c $< -I. -I/home/kea00sys/sqllib/include

clean       :
	$(RM) *.o

$(TARGET)	:	$(BML_OBJ)
	ar r $(TARGET) $(BML_OBJ)

