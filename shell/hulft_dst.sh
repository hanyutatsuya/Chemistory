#*****************************************************************
#   �a�l�k�l���������V�X�e��
#
#   �V�X�e�����F������V�X�e��
#   �t�@�C�����Fhulft_dst.sh
#   �T      �v�F������t�i�˗��W�J�jHULFT��M�t�@�C���̐U�蕪��
#                   �e�X�g���p�U�蕪��
#   �N�����Ұ�
#           hulft_dst.sh
#*****************************************************************
#   No.Ver.    ���t           ���O          �R�����g
#---------------------------------------------------------------*
#   H000    95.09.20    INTEC.INC   CREATE
#*****************************************************************
#
#------------  ���s��۸��т̎w�� -----------------------------------
#-------------------------------------------------------------------

#
#   �e��ϐ��̐ݒ�
WK=/tmp/$$
# �t�@�C����M�p�f�B���N�g��
RECD=/apdata/today/online/host/Recv
# �����ς݃t�@�C���Ҕ��f�B���N�g��
ENDDIR=$RECD/sumi
# �װ�t�@�C���Ҕ��f�B���N�g��
ERRDIR=/apdata/today/online/host/err_Recv

KAN=$RECD/kan                   # ���ґ����t�@�C��
IRI=$RECD/iri                   # �˗����t�@�C��
BUN=$RECD/bun                   # �������ʃt�@�C��

PREF=PNC.                       # PNC�ғ��O��̔���p

DBG=$1                          # DEBUG MODE�w��

YMD=`date +%Y%m%d`

#-------------------------  ���̉����珈�����L�q  ------------------
echo "##### [`date`] �˗���M�����J�n #####"    >> $WK.uerr
echo " "                                        >> $WK.uerr

#
#   �t�@�C����M�p�f�B���N�g���ւ̈ړ�
cd $RECD

#
#   hulft�o�^�������̂���̃t�@�C�����ύX
#       ����Ǘ����s���̂Łu�����t�@�C����+seq�v�ɂăt�@�C�����쐬�����
#           (hulft.rirai.9999)
#       ��M�I������HULFT�����ϐ�$FILENM�ɍ쐬�����t�@�C������ݒ肷��
#

#mv $FILENM     PNC/"$PREF"HIP$YMD.$$
##cp  PNC/hulft.rirai   PNC/"$PREF"HIP$YMD.$$

#==========================================================================
#
#       �t�@�C���U�蕪��
#
#==========================================================================
#
for LS in `ls ./`
do
        echo "�������B�B�B[$LS]"

        # �f�B���N�g����ΏۊO��
        if [ -d $LS ]
        then
            echo "Directory ->  SKIP [$LS]" >> $WK.uerr
            continue
        fi

        # ���R�[�h�����擾
        RCNT=`grep -v "^HD" $LS | grep -v "^TR" | wc -l`
        if [ $RCNT -eq 0 ]
        then
            echo "HD TR ONLY ->  SKIP [$LS][$RCNT]" >> $WK.uerr
            mv $LS $ENDDIR/HDTR.$LS
            continue
        fi

        #   �f�[�^�t���[ID�̎擾
        DFLWID=`head -1 $LS | cut -b 31-40`

        echo "�Ώۃt�@�C��[$LS][$DFLWID][$RCNT]" >> $WK.uerr

        case    "$DFLWID"
        in
            "SIRAI002  "    )
                PREF=KAN.
                echo "$LS ---> $KAN/\"$PREF\"$LS" >> $WK.uerr
                mv $LS $KAN/"$PREF"$LS
                ;;
            "SIRAI004  "    )
                PREF=IRI.
                echo "$LS ---> $IRI/\"$PREF\"$LS" >> $WK.uerr
                mv $LS $IRI/"$PREF"$LS
                ;;
            "SBUNC003  "    )
                PREF=BUN.
                echo "$LS ---> $BUN/\"$PREF\"$LS" >> $WK.uerr
                mv $LS $BUN/"$PREF"$LS
                ;;
            *           )
                echo "$LS ---> �ΏۊO" >> $WK.uerr
                ;;
        esac
done

#==========================================================================
#
#       �I������
#
#==========================================================================
#
#   �t�@�C����M�p�f�B���N�g���ւ̈ړ�
cd $RECD

#   DBG
    CURDIR=`pwd`
    echo "�I������ START!! CURDIR=[$CURDIR]" >> $WK.uerr

exit 0

