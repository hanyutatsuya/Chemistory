#! /bin/csh -f

###################################################
# 日付フォーマットチェック
# 引数 $1 : 日付(YYYYMMDD)
# 戻値 0  : 正常終了
#      1  : エラー
###################################################
# 桁数チェック
# 8桁でない場合、usageを表示

echo $1 > input_value_$$.dat
if (`awk '{print length($1)}' input_value_$$.dat` != 8 ) then
  echo usage : $0 YYYYMMDD
  rm -f *_$$.dat
  exit 1
endif

# 値の妥当性チェック
# 入力値を分割して変数にセット
# 月、日については先頭の0を削除しておく

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

# 年のチェック ( 0000 - 9999 )

if ( ! `echo $YEAR | egrep '^[0-9]{4}$'` ) then
#  echo "YEAR check error."
  rm -f *_$$.dat
  exit 1
endif

# 月のチェック ( 1 - 12 )

if ( ! `echo $MONTH | egrep '^[1-9]$|^1[0-2]$'` ) then
#  echo "MONTH check error."
  rm -f *_$$.dat
  exit 1
endif

# 日のチェック ( 基本 : 1 - 31 )

if ( ! `echo $DAY | egrep '^[1-9]$|^[12][0-9]$|^3[01]$'` ) then
#  echo "DAY check error."
  rm -f *_$$.dat
  exit 1
endif

# 日のチェック ( 詳細 : 月ごとの最終日と閏年の考慮 )

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
