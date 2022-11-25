#! /bin/csh -f

###################################################
# ���t�t�H�[�}�b�g�`�F�b�N
# ���� $1 : ���t(YYYYMMDD)
# �ߒl 0  : ����I��
#      1  : �G���[
###################################################
# �����`�F�b�N
# 8���łȂ��ꍇ�Ausage��\��

echo $1 > input_value_$$.dat
if (`awk '{print length($1)}' input_value_$$.dat` != 8 ) then
  echo usage : $0 YYYYMMDD
  rm -f *_$$.dat
  exit 1
endif

# �l�̑Ó����`�F�b�N
# ���͒l�𕪊����ĕϐ��ɃZ�b�g
# ���A���ɂ��Ă͐擪��0���폜���Ă���

set YEAR = `cut -c1-4 input_value_$$.dat`
if (`cut -c5-5 input_value_$$.dat` == 0) then
  set MONTH = `cut -c6-6 input_value_$$.dat`
else
  set MONTH = `cut -c5-6 input_value_$$.dat`
endif
if (`cut -c7-7 input_value_$$.dat` == 0) then
  set DAY = `cut -c8-8 input_value_$$.dat`
else
  set DAY = `cut -c7-8 input_value_$$.dat`
endif

# �N�̃`�F�b�N ( 0000 - 9999 )

if ( ! `echo $YEAR | egrep '^[0-9]{4}$'` ) then
#  echo "YEAR check error."
  rm -f *_$$.dat
  exit 1
endif

# ���̃`�F�b�N ( 1 - 12 )

if ( ! `echo $MONTH | egrep '^[1-9]$|^1[0-2]$'` ) then
#  echo "MONTH check error."
  rm -f *_$$.dat
  exit 1
endif

# ���̃`�F�b�N ( ��{ : 1 - 31 )

if ( ! `echo $DAY | egrep '^[1-9]$|^[12][0-9]$|^3[01]$'` ) then
#  echo "DAY check error."
  rm -f *_$$.dat
  exit 1
endif

# ���̃`�F�b�N ( �ڍ� : �����Ƃ̍ŏI���Ɖ[�N�̍l�� )

set ENDDAY = (31 28 31 30 31 30 31 31 30 31 30 31)
set LASTDAY = $ENDDAY[$MONTH]

if ($MONTH == 2 && $YEAR % 4 == 0 && $YEAR % 100 != 0) then
    @ LASTDAY += 1
else if ($MONTH == 2 && $YEAR % 400 == 0 ) then
    @ LASTDAY += 1
endif

if ( $DAY > $LASTDAY ) then
#  echo "DAY check error."
  rm -f *_$$.dat
  exit 1
endif

#echo OK

rm -f *_$$.dat

exit 0
