# Mａｋｅｆｉｌｅ

include	$(HOME)/inc/make.inc

## ヘッダー & コンパイルフラグ
#DBGFLAG		=	-g -DDEBUGP -DDEBUGS -DDEBUGS2
DBGFLAG		=	-UDEBUGP -UDEBUGS -UDEBUGS2
CPPFLAG		=	$(DBGFLAG)
CCFLAG		=	$(CPPFLAG)
INCS		=	-I$(CINC) -I$(INCDIR) -I$(INC-I7)

## ライブラリ
LIB-CFILE	=	-ldb -lbml -lc -lm
LIBS		=	-L$(CLIB) $(LIB-I7) $(LIB-IFILE) $(LIB-CFILE)

## メインルーチン
NAME1		=	rpnmain
NAME2		=	rpnconv
NAME3		=	rpncalc

CSRC1		=	$(SRCDIR)/$(NAME1).c
COBJ1		=	$(OBJDIR)/$(NAME1).o

CSRC2		=	$(SRCDIR)/$(NAME2).c
COBJ2		=	$(OBJDIR)/$(NAME2).o

CSRC3		=	$(SRCDIR)/$(NAME3).c
COBJ3		=	$(OBJDIR)/$(NAME3).o

APINCS		=	$(COMINC) $(DBINC) $(SRCDIR)/rpncalc.h

# オブジェクト & 実行モジュール
COBJS		=	$(COBJ1) $(COBJ2) $(COBJ3)
PROGRAM1	=	$(BINDIR)/$(NAME1).exe

# コンパイル & リンク
all : $(PROGRAM1)

$(PROGRAM1):	$(COBJS)
	@echo Now Linking $(PROGRAM1)
	$(CC) $(COBJS) -o $(PROGRAM1) $(CCFLAG) $(LIBS) $(LIBFLAGS)

$(COBJ1):	$(CSRC1) $(APINCS)
	@echo Now C-Compiling $(CSRC1)....
	$(CC) $(CCFLAG) $(INCS) $(CSRC1) -c -o $(COBJ1)

$(COBJ2):	$(CSRC2) $(APINCS)
	@echo Now C-Compiling $(CSRC2)....
	$(CC) $(CCFLAG) $(INCS) $(CSRC2) -c -o $(COBJ2)

$(COBJ3):	$(CSRC3) $(APINCS)
	@echo Now C-Compiling $(CSRC3)....
	$(CC) $(CCFLAG) $(INCS) $(CSRC3) -c -o $(COBJ3)

clean:
	$(RM) -f $(PROGRAM1)
	$(RM) -f $(COBJS)

install:
	$(CP) $(PROGRAM1) $(INSDIR)

