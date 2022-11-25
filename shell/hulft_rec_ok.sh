:
#*****************************************************************
#   �a�l�k�l���������V�X�e��
#
#   �V�X�e�����F������V�X�e��
#   �t�@�C�����Fhulft_rec_ok.sh
#	�T      �v�F������t�i�˗��W�J�jHULFT��M�t�@�C���̐U�蕪��
#				  ( HULFT��M OK ���N��shell )
#
#*****************************************************************
#	No.Ver.    ���t           ���O          �R�����g
#---------------------------------------------------------------*
#	H000	2006.03.17	INTEC.INC	CREATE
#	H001	2006.06.01	INTEC.INC	UPDATE  �Y��dir��mv �� rename
#*****************************************************************
#
#------------  ���s��۸��т̎w�� -----------------------------------
#-------------------------------------------------------------------

#
#	�e��ϐ��̐ݒ�
WK=/tmp/$$
# �t�@�C����M�p�f�B���N�g��
RECD=/apdata/today/online/host/Recv
# �����ς݃t�@�C���Ҕ��f�B���N�g��
ENDDIR=$RECD/sumi
# �װ�t�@�C���Ҕ��f�B���N�g��
ERRDIR=/apdata/today/online/host/err_Recv

KAN=$RECD/kan					# ���ґ����t�@�C��
IRI=$RECD/iri					# �˗����t�@�C��
BUN=$RECD/bun					# �������ʃt�@�C��
KKA=$RECD/kka					# ���T�e���C�g���ʃt�@�C��

DBG=$1							# DEBUG MODE�w��

YMD=`date +%Y%m%d`

#
#	LOG OUTPUT VARIABLE
PROCESSID=$$
WKUPAPP=$0

#-------------------------  ���̉����珈�����L�q  ------------------
#
#	�t�@�C����M�p�f�B���N�g���ւ̈ړ�	
cd $RECD

#
#	hulft�o�^�������̂���̃t�@�C�����ύX
#		����Ǘ����s���̂Łu�����t�@�C����+seq�v�ɂăt�@�C�����쐬�����
#			(hulft.rirai.9999)
#		��M�I������HULFT�����ϐ�$FILENM�ɍ쐬�����t�@�C������ݒ肷��
#

#
# �t�@�C���̗L��
if [ -s $FILENM ]
then
	echo " "
else
	#----------------
	#	LOG OUTPUT
	#----------------
	MESSAGE="File[$FILENM] does not exist"

	sh hulft_ins_log.sh "W" $PROCESSID $WKUPAPP "$MESSAGE" 

	#	DBG
	if [ "$DBG" = "-DBG" ] ; then
		echo "File[$FILENM] does not exist"
	fi

	#	�����I��
	exit 0
fi

#	���ϐ�����f�B���N�g�����������t�@�C���������o��
LS=`basename $FILENM`
##mv $FILENM	$LS

#==========================================================================
#		
#		�t�@�C���U�蕪��
#		
#==========================================================================
while true
do
	#
	# ���R�[�h�����擾  HD TR�݂̂�SKIP
	RCNT=`grep -v "^HD" $LS | grep -v "^TR" | wc -l`
	if [ $RCNT -eq 0 ] 
	then
		#	DBG
		if [ "$DBG" = "-DBG" ] ; then
			echo "[$LS]HD TR ONLY RCNT[$RCNT]"
		fi

		#	�����σf�B���N�g���Ɉړ�
		mv $LS $ENDDIR/HDTR.$LS
		break
	fi

	#
	#	�f�[�^�t���[ID�̎擾
	DFLWID=`head -1 $LS | cut -b 31-40`

	#	DBG
	if [ "$DBG" = "-DBG" ] ; then
		echo "�Ώۃt�@�C��[$LS][$DFLWID]"
	fi

	#
	#	�f�[�^�t���[ID�̎擾
	case	"$DFLWID"
	in
		"SIRAI002  "	)
			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "���ґ��� -> [$KAN/KAN.$LS]"
			fi
			mv  $LS			$KAN/$LS
			rename $KAN/$LS $KAN/KAN.$LS $KAN/$LS
			break
			;;
		"SIRAI004  "	)
			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "�˗���� -> [$IRI/IRI.$LS]"
			fi
			mv  $LS			$IRI/$LS
			rename $IRI/$LS $IRI/IRI.$LS $IRI/$LS
			break
			;;
		"SBUNC003  "	)
			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "�������� -> [$BUN/BUN.$LS]"
			fi
			mv  $LS			$BUN/$LS
			rename $BUN/$LS $BUN/BUN.$LS $BUN/$LS
			break
			;;
		"EHOKO002  "	)
			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "���T�e���C�g���� -> [$KKA/KKA.$LS]"
			fi
			mv  $LS			$KKA/$LS
			rename $KKA/$LS $KKA/KKA.$LS $KKA/$LS
			break
			;;
		*			)
			#----------------
			#	LOG OUTPUT
			#----------------
			MESSAGE="HULFT��M�@�f�[�^�t���[ID�ΏۊO[$LS][$DFLWID]"

			sh hulft_ins_log.sh "W" $PROCESSID $WKUPAPP "$MESSAGE" 

			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "�ΏۊO -> [$ENDDIR/$LS][$DFLWID]"
			fi
			mv $LS $ENDDIR/$LS
			break
			;;
	esac

	#	�����͂P�񂾂�
	break
done

#==========================================================================
#		
#		�I������
#		
#==========================================================================
#
#	�t�@�C����M�p�f�B���N�g���ւ̈ړ�	
cd $RECD

#
#	�����I���t�@�C���̈ړ�
for i in `find $KAN $IRI $BUN  -name "END*" -print `
do
	mv $i  $ENDDIR
done

#
#  ���ԃt�@�C���̸ر
##rm $WK*

exit 0
