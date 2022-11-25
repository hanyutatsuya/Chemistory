######################################################
# FILE NAME		: Makefile
# Exectable Module	: libbml.a
#
# Create Torigeer for Tokyo AIS Co.
#
#  VER   DATE       HISTORY
# ----- ---------- -----------------------------------
#  1.0   05/06/14   E.osda Create
#
######################################################
CC       = /usr/bin/gcc
AR       = /usr/bin/ar
RM       = /bin/rm
MV       = /bin/mv
CFLAGS   = -DDEBUG -g
LDFLAGS  = -ldb2
MAKEHOME = $(HOME)/appl
EXE_DIR	 = $(MAKEHOME)/lib
SRC_COM_DIR	 = $(MAKEHOME)/src/lib/common
SRC_LOG_DIR	 = $(MAKEHOME)/src/lib/log
SRC_DB_DIR	 = $(MAKEHOME)/src/lib/db
INC_DIR  = $(MAKEHOME)/inc
OBJ_DIR	 = $(MAKEHOME)/src/lib/obj
DB2_INC_DIR	 = $(HOME)/sqllib/include
MAKE_DIR = $(MAKEHOME)/src/lib
FLG_INC = -I$(INC_DIR) -I$(DB2_INC_DIR)

INCS_DB = \
	$(INC_DIR)/Apllog.h	\
	$(INC_DIR)/Asyrackknri.h	\
	$(INC_DIR)/Asyscdlmst.h	\
	$(INC_DIR)/Batchknri.h	\
	$(INC_DIR)/Bscmtmst.h	\
	$(INC_DIR)/Bssikka.h	\
	$(INC_DIR)/Bssizok.h	\
	$(INC_DIR)/Bunchu.h	\
	$(INC_DIR)/Calckmkmst.h	\
	$(INC_DIR)/Chikenzok.h	\
	$(INC_DIR)/Chk100mst.h	\
	$(INC_DIR)/Chksbtmst.h	\
	$(INC_DIR)/Cmtmst.h	\
	$(INC_DIR)/Ctrlijhtmst.h	\
	$(INC_DIR)/Ctrlkka.h	\
	$(INC_DIR)/Ctrlknr.h	\
	$(INC_DIR)/Ctrlmst.h	\
	$(INC_DIR)/Ctrlsbtmst.h	\
	$(INC_DIR)/Defprmst.h	\
	$(INC_DIR)/Eigmst.h	\
	$(INC_DIR)/Fkptchkmst.h	\
	$(INC_DIR)/Hkkknri.h	\
	$(INC_DIR)/Hyjkmk.h	\
	$(INC_DIR)/Ijyosya.h	\
	$(INC_DIR)/Irai.h	\
	$(INC_DIR)/Jdkmkmst.h	\
	$(INC_DIR)/Kanjya.h	\
	$(INC_DIR)/Kekka.h	\
	$(INC_DIR)/Kekkafree.h	\
	$(INC_DIR)/Kenorder.h	\
	$(INC_DIR)/Kenpos.h	\
	$(INC_DIR)/Kenzok.h	\
	$(INC_DIR)/Kgymdmst.h	\
	$(INC_DIR)/Kinkmmst.h	\
	$(INC_DIR)/Kjnmst.h	\
	$(INC_DIR)/Kkafltmst.h	\
	$(INC_DIR)/Kkahskmst.h	\
	$(INC_DIR)/Kmkbtutest.h	\
	$(INC_DIR)/Kmkgmst.h	\
	$(INC_DIR)/Kmkmst.h	\
	$(INC_DIR)/Knkmhmzk.h	\
	$(INC_DIR)/Knkyulot.h	\
	$(INC_DIR)/Knokgnmst.h	\
	$(INC_DIR)/Knsgmst.h	\
	$(INC_DIR)/Knsseqknri.h	\
	$(INC_DIR)/Knssnkjyk.h	\
	$(INC_DIR)/Kntidunknown.h	\
	$(INC_DIR)/Krkmkmst.h	\
	$(INC_DIR)/Kskbrmst.h	\
	$(INC_DIR)/Mechmst.h	\
	$(INC_DIR)/Melinemst.h	\
	$(INC_DIR)/Memst.h	\
	$(INC_DIR)/Messagemst.h	\
	$(INC_DIR)/Ninsiki.h	\
	$(INC_DIR)/Onlmst.h	\
	$(INC_DIR)/Prcsmst.h	\
	$(INC_DIR)/Realchk.h	\
	$(INC_DIR)/Rireki.h	\
	$(INC_DIR)/Rkmst.h	\
	$(INC_DIR)/Rngchkmst.h	\
	$(INC_DIR)/Rrkchkmst.h	\
	$(INC_DIR)/Secmst.h	\
	$(INC_DIR)/Skchkmst.h	\
	$(INC_DIR)/Skrymst.h	\
	$(INC_DIR)/Slide.h	\
	$(INC_DIR)/Soukan.h	\
	$(INC_DIR)/Sstkjmst.h	\
	$(INC_DIR)/Sstsrmst.h	\
	$(INC_DIR)/Standard.h	\
	$(INC_DIR)/Stdmst.h	\
	$(INC_DIR)/Sysknrmst.h	\
	$(INC_DIR)/Trayknri.h	\
	$(INC_DIR)/Trmst.h	\
	$(INC_DIR)/Trrakhmzk.h	\
	$(INC_DIR)/Tschkmst.h	\
	$(INC_DIR)/Usermst.h	\
	$(INC_DIR)/Xbarm.h	\
	$(INC_DIR)/Xbarmmst.h	\
	$(INC_DIR)/Xebskflg.h	\
	$(INC_DIR)/Xeerrmst.h	\
	$(INC_DIR)/Zairmst.h	\
	$(INC_DIR)/bml_DBCom.h

OBJS_DB = \
	$(SRC_DB_DIR)/Apllog.o	\
	$(SRC_DB_DIR)/Asyrackknri.o	\
	$(SRC_DB_DIR)/Asyscdlmst.o	\
	$(SRC_DB_DIR)/Batchknri.o	\
	$(SRC_DB_DIR)/Bscmtmst.o	\
	$(SRC_DB_DIR)/Bssikka.o	\
	$(SRC_DB_DIR)/Bssizok.o	\
	$(SRC_DB_DIR)/Bunchu.o	\
	$(SRC_DB_DIR)/Calckmkmst.o	\
	$(SRC_DB_DIR)/Chikenzok.o	\
	$(SRC_DB_DIR)/Chk100mst.o	\
	$(SRC_DB_DIR)/Chksbtmst.o	\
	$(SRC_DB_DIR)/Cmtmst.o	\
	$(SRC_DB_DIR)/Ctrlijhtmst.o	\
	$(SRC_DB_DIR)/Ctrlkka.o	\
	$(SRC_DB_DIR)/Ctrlknr.o	\
	$(SRC_DB_DIR)/Ctrlmst.o	\
	$(SRC_DB_DIR)/Ctrlsbtmst.o	\
	$(SRC_DB_DIR)/Defprmst.o	\
	$(SRC_DB_DIR)/Eigmst.o	\
	$(SRC_DB_DIR)/Fkptchkmst.o	\
	$(SRC_DB_DIR)/Hkkknri.o	\
	$(SRC_DB_DIR)/Hyjkmk.o	\
	$(SRC_DB_DIR)/Ijyosya.o	\
	$(SRC_DB_DIR)/Irai.o	\
	$(SRC_DB_DIR)/Jdkmkmst.o	\
	$(SRC_DB_DIR)/Kanjya.o	\
	$(SRC_DB_DIR)/Kekka.o	\
	$(SRC_DB_DIR)/Kekkafree.o	\
	$(SRC_DB_DIR)/Kenorder.o	\
	$(SRC_DB_DIR)/Kenpos.o	\
	$(SRC_DB_DIR)/Kenzok.o	\
	$(SRC_DB_DIR)/Kgymdmst.o	\
	$(SRC_DB_DIR)/Kinkmmst.o	\
	$(SRC_DB_DIR)/Kjnmst.o	\
	$(SRC_DB_DIR)/Kkafltmst.o	\
	$(SRC_DB_DIR)/Kkahskmst.o	\
	$(SRC_DB_DIR)/Kmkbtutest.o	\
	$(SRC_DB_DIR)/Kmkgmst.o	\
	$(SRC_DB_DIR)/Kmkmst.o	\
	$(SRC_DB_DIR)/Knkmhmzk.o	\
	$(SRC_DB_DIR)/Knkyulot.o	\
	$(SRC_DB_DIR)/Knokgnmst.o	\
	$(SRC_DB_DIR)/Knsgmst.o	\
	$(SRC_DB_DIR)/Knsseqknri.o	\
	$(SRC_DB_DIR)/Knssnkjyk.o	\
	$(SRC_DB_DIR)/Kntidunknown.o	\
	$(SRC_DB_DIR)/Krkmkmst.o	\
	$(SRC_DB_DIR)/Kskbrmst.o	\
	$(SRC_DB_DIR)/Mechmst.o	\
	$(SRC_DB_DIR)/Melinemst.o	\
	$(SRC_DB_DIR)/Memst.o	\
	$(SRC_DB_DIR)/Messagemst.o	\
	$(SRC_DB_DIR)/Ninsiki.o	\
	$(SRC_DB_DIR)/Onlmst.o	\
	$(SRC_DB_DIR)/Prcsmst.o	\
	$(SRC_DB_DIR)/Realchk.o	\
	$(SRC_DB_DIR)/Rkmst.o	\
	$(SRC_DB_DIR)/Rngchkmst.o	\
	$(SRC_DB_DIR)/Rrkchkmst.o	\
	$(SRC_DB_DIR)/Secmst.o	\
	$(SRC_DB_DIR)/Skchkmst.o	\
	$(SRC_DB_DIR)/Skrymst.o	\
	$(SRC_DB_DIR)/Slide.o	\
	$(SRC_DB_DIR)/Soukan.o	\
	$(SRC_DB_DIR)/Sstkjmst.o	\
	$(SRC_DB_DIR)/Sstsrmst.o	\
	$(SRC_DB_DIR)/Standard.o	\
	$(SRC_DB_DIR)/Stdmst.o	\
	$(SRC_DB_DIR)/Sysknrmst.o	\
	$(SRC_DB_DIR)/Trayknri.o	\
	$(SRC_DB_DIR)/Trmst.o	\
	$(SRC_DB_DIR)/Trrakhmzk.o	\
	$(SRC_DB_DIR)/Tschkmst.o	\
	$(SRC_DB_DIR)/Usermst.o	\
	$(SRC_DB_DIR)/Xbarm.o	\
	$(SRC_DB_DIR)/Xbarmmst.o	\
	$(SRC_DB_DIR)/Xebskflg.o	\
	$(SRC_DB_DIR)/Xeerrmst.o	\
	$(SRC_DB_DIR)/Zairmst.o	\
	$(SRC_DB_DIR)/bml_DBCom.o

TARGET  = $(EXE_DIR)/libbmldb.a

all	: $(TARGET)

$(TARGET)	:	$(OBJS_DB)
	$(AR) r $(TARGET) $(OBJS_DB)

%.o		:	%.c
	$(CC) $(CFLAGS) -c $< $(FLG_INC)

clean :
	$(RM) -f $(TARGET) $(OBJS_DB)
