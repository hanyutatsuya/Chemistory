/************************************************************************/
/*																		*/
/*		ＢＭＬ様向け検査システム										*/
/*																		*/
/*		システム名：次世代												*/
/*		ファイル名：bml_date.c											*/
/*		概要      ：日付操作共通関数									*/
/*																		*/
/************************************************************************/

/************************************************************************/
/*  Ver.	日付			名前			修正内容					*/
/* -------------------------------------------------------------------- */
/*	1.00	2005/06/14		E.Osada			Create						*/
/************************************************************************/

/************************************************************************/
/*	インクルード宣言													*/
/************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bml_date.h"

/************************************************************************/
/*	ｄｅｆｉｎｅ定義													*/
/************************************************************************/
#define IS_LEAP_YEAR(year) ((year)%400 == 0 || ((year)%100 != 0 && (year)%4 == 0))

/************************************************************************/
/*	グローバル宣言														*/
/************************************************************************/
static BmlDateHolidayInfo theDefaultHolidays[]={
   {  1,  1},       {  1, 15, TRUE},
   {  2, 11, TRUE},
   {  3, 20, TRUE},
   {  4, 29, TRUE},
   {  5,  3},       {  5,  4},       {  5,  5, TRUE},
   {  7, 20, TRUE},
   {  9, 15, TRUE}, {  9, 23, TRUE},
   { 10, 10, TRUE},
   { 11,  3, TRUE}, { 11, 23, TRUE},
   { 12, 23, TRUE},
   {  0} // End mark
};

static BmlDateHolidayInfo *theHolidays=theDefaultHolidays;
static BmlDateHolidayInfo *userHolidays=NULL;

static ULONG daysOfMonthN[]=
{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static ULONG daysOfMonthL[]=
{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *dayOfWeek[]=
{"日", "月", "火", "水", "木", "金", "土"};

static ULONG dayOfYearN[] =
{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static ULONG dayOfYearL[] =
{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

/************************************************************************/
/*	プロトタイプ宣言													*/
/************************************************************************/
static BOOL convertIntegerDate(ULONG*);

/************************************************************************/
/*	関数名		：ZbmlDateGetToday()									*/
/*	機能概要	：システム日付を取得する								*/
/* 	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付の設定先			*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateGetToday(BmlDate *date)
{
    unsigned long now;
    struct tm *tm;

    if (NULL == date)
	return FALSE;

    time((long *)&now);
    tm = localtime((long *)&now);
    date->year  = tm->tm_year+1900;
    date->month = tm->tm_mon+1;
    date->day   = tm->tm_mday;

    return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlDateIsValid()										*/
/*	機能概要	：日付情報の妥当性をチェックする						*/
/* 	入力																*/
/*	 第１引数	：BmlDate*	date		チェックするシステム日付		*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateIsValid(BmlDate *date)
{
    if (NULL == date)
	return FALSE;

    if (date->month <= 0)
	return FALSE;
    else if (date->month > 12)
	return FALSE;

    if (date->day <= 0)
	return FALSE;

    if (date->day > ZbmlDateDaysOfMonth(date->year, date->month))
	return FALSE;

    return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlDateAsString()									*/
/*	機能概要	：システム日付を"YYYY-MM-DD"の文字列に変換する			*/
/* 	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/*	 第２引数	：char*		str			変換文字列設定先				*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateAsString(BmlDate *date, char *str)
{
    if (NULL == date || NULL == str)
        return FALSE;

    sprintf(str, "%04d-%02d-%02d", date->year, date->month, date->day);
    return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlDateAsString2()									*/
/*	機能概要	：システム日付を"YY-MM-DD"の文字列に変換する			*/
/* 	入力																*/
/*	 第１引数   :　BmlDate*	date		システム日付					*/
/*	 第２引数   :　char*	str			変換文字列設定先				*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateAsString2(BmlDate *date, char *str)
{
    if (NULL == date || NULL == str)
        return FALSE;

    sprintf(str, "%02d-%02d-%02d", date->year%100, date->month, date->day);
    return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlDateAsStringW()									*/
/*	機能概要	：システム日付を和暦文字列に変換する					*/
/* 	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/*	 第２引数	：char*		str			変換文字列設定先				*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
static struct{
    char *era;
    BmlDate date;
}eraArray[]={
    {"H", {1989,  1,  7}},
    {"S", {1926, 11, 25}},
    {"T", {1912,  7, 30}},
    {"M", {1868,  1,  9}},
    {NULL}};

BOOL ZbmlDateAsStringW(BmlDate *date, char *str)
{
    int i;
    if (NULL == date || NULL == str)
        return FALSE;

    for (i=0; eraArray[i].era; i++){
		BmlDate *bdate = &eraArray[i].date;

		if (date->year > bdate->year ||
		    (date->year == bdate->year && date->month > bdate->month) ||
		    (date->year == bdate->year && date->month == bdate->month &&
		     date->day >= bdate->day)){
		    sprintf(str, "%s%02d-%02d-%02d", 
			    eraArray[i].era, 
			    date->year-bdate->year+1,
			    date->month,
			    date->day);
		}
    }

    sprintf(str, "E%02d-%02d-%02d", date->year, date->month, date->day);

    return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlDateAsInteger()									*/
/*	機能概要	：システム日付を日単位に変換する						*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/*	 第２引数	：ULONG*		valueOut	変換日設定先				*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateAsInteger(BmlDate *date, ULONG *valueOut)
{
    if (NULL == date || NULL == valueOut)
        return FALSE;

    *valueOut = date->year*10000 + date->month*100 + date->day;

    return TRUE;
}


/************************************************************************/
/*	関数名		：ZbmlDateFromString()									*/
/*	機能概要	：システム日付"YYYYMMDD"or"YYMMDD"文字列に変換する		*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/*	 第２引数	：char*		str			設定先							*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateFromString(BmlDate *date, char *str)
{
    char buff[256];
    char *pb, *pe;
    char *seps = "/-.";
    char *nums = "0123456789";
    BmlDate today;

    if (NULL == date || NULL == str)
	return FALSE;

    ZbmlDateGetToday(&today);

    strcpy(buff, str);
    pb = buff;

    if ((pe = strpbrk(pb, seps)) == NULL){
		int len = strlen(buff);
		if ((len != 8 && len != 6 && len != 4) || strspn(buff, nums) < len) {
	    	return FALSE;
		}

		if (len == 8) {
	    	sscanf(buff, "%04d%02d%02d", &date->year, &date->month, &date->day);
		} else if (len == 6) {
	    	sscanf(buff, "%02d%02d%02d", &date->year, &date->month, &date->day);
		}else{
	    	date->year = today.year;
	    	sscanf(buff, "%02d%02d", &date->month, &date->day);
		}
    }
    else{
		if (pb == pe)
	    	return FALSE;

		*pe = 0;
		date->year = atoi(pb);
		pb = pe+1;

		if ((pe = strpbrk(pb, seps)) == NULL || pb == pe) {
	    	return FALSE;
		}

		*pe = 0;
		date->month = atoi(pb);
		pb = pe+1;

		date->day = atoi(pb);
    }

    if (date->year < 100)
	date->year += (today.year/100)*100;

    return ZbmlDateIsValid(date);
}


/************************************************************************/
/*	関数名		：ZbmlDateFromInteger()									*/
/*	機能概要	：日単位の日付をシステム日付に変換する					*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/*	 第２引数	：ULONG*	value		日								*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateFromInteger(BmlDate *date, ULONG value)
{
    if (NULL == date)
	return FALSE;

    date->year  = value/10000;
    date->month = (value/100) % 100;
    date->day   = value % 100;

    if (date->month < 0) {
		date->month = 1;
    }else if (date->month > 12) {
		date->month = 12;
	}
    if (date->day < 0) {
		date->day = 1;
    }else{
		int days = ZbmlDateDaysOfMonth(date->year, date->month);
		if (date->day > days) {
	    	date->day = days;
		}
    }

    return TRUE;
}


/************************************************************************/
/*	関数名		：ZbmlDateDayOfWeek()									*/
/*	機能概要	：システム日付の曜日を数値で返す						*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/* 	出力																*/
/*	 正常：1->7															*/
/*	 異常：0															*/
/************************************************************************/
int ZbmlDateDayOfWeek(BmlDate *date)
{
    return (ZbmlDateDayNumber(date)+1)%7;
}


/************************************************************************/
/*	関数名		：ZbmlDateDayOfWeekName()								*/
/*	機能概要	：システム日付の曜日を漢字で返す						*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/* 	出力																*/
/*	 正常：「日」～「土」												*/
/*	 異常：0															*/
/************************************************************************/
char* ZbmlDateDayOfWeekName(BmlDate *date)
{
    return dayOfWeek[ZbmlDateDayOfWeek(date)];
}


/************************************************************************/
/*	関数名		：ZbmlDateDayOfYear()									*/
/*	機能概要	：システム日付月の最終日を返す							*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/* 	出力																*/
/*	 正常：システム日付月の最終日										*/
/*	 異常：0															*/
/************************************************************************/
ULONG ZbmlDateDayOfYear(BmlDate *date)
{
    ULONG *array;

    if (NULL == date)
	return 0;

    array = IS_LEAP_YEAR(date->year) ? dayOfYearL : dayOfYearN;

    return array[date->month-1]+date->day;
}

    
/************************************************************************/
/*	関数名		：ZbmlDateDayNumber()									*/
/*	機能概要	：システム日付の日単位を返す							*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/* 	出力																*/
/*	 正常：指定月の最終日												*/
/*	 異常：0															*/
/************************************************************************/
ULONG ZbmlDateDayNumber(BmlDate *date)
{
    ULONG doc, yoc;

    if (NULL == date)
	return 0L;

    doc = ZbmlDateDayOfYear(date);
    yoc = (ULONG)date->year - 1900L;

    return doc + (yoc-1)*365+(yoc-1)/4-(yoc-1)/400;
}

/************************************************************************/
/*	関数名		：ZbmlDateGetDayType()									*/
/*	機能概要	：システム日付から土日又は平日かを判断する。			*/
/*	入力																*/
/*	 第１引数	：BmlDate*			date		システム日付			*/
/*	 第２引数	：BmlDateDayType*	typeOut								*/
/* 	出力																*/
/*	 正常：土日又は平日													*/
/*	 異常：0															*/
/************************************************************************/
BOOL ZbmlDateGetDayType(BmlDate *date, BmlDateDayType *typeOut)
{
    int dow;

    if (NULL == date || NULL == typeOut)
	return FALSE;

    dow = ZbmlDateDayOfWeek(date);

    if (dow == 0){
        *typeOut = DT_Sunday;
		return TRUE;
    }

    if (dow == 6){
        *typeOut = DT_Saturday;
		return TRUE;
    }

    *typeOut = DT_WeekDay;

    return TRUE;
}


/************************************************************************/
/*	関数名		：ZbmlDateDaysOfMonth()									*/
/*	機能概要	：指定月の最終日を返す									*/
/*	入力																*/
/*	 第１引数	：int	year		年									*/
/*	 第２引数	：int	month		月									*/
/* 	出力																*/
/*	 正常：指定月の最終日												*/
/*	 異常：0															*/
/************************************************************************/
int   ZbmlDateDaysOfMonth(int year, int month)
{
    if (month < 1 || month > 12)
	return 0;

    return IS_LEAP_YEAR(year) ? daysOfMonthL[month-1] : daysOfMonthN[month-1];
}


/************************************************************************/
/*	関数名		：ZbmlDateDaysOfYear()									*/
/*	機能概要	：指定年の年間日数を返す								*/
/*	入力																*/
/*	 第１引数	：int	year		年									*/
/* 	出力																*/
/*	 正常：指定年の年間日数												*/
/*	 異常：0															*/
/************************************************************************/
int   ZbmlDateDaysOfYear(int year)
{
    return IS_LEAP_YEAR(year) ? 366 : 365;
}


/************************************************************************/
/*	関数名		：ZbmlDateIsLeapYear()									*/
/*	機能概要	：閏年チェック											*/
/*	入力																*/
/*	 第１引数	：int	year		年									*/
/* 	出力																*/
/*	 1：閏年															*/
/*	 0：通常年															*/
/************************************************************************/
BOOL  ZbmlDateIsLeapYear(int year)
{
    return IS_LEAP_YEAR(year);
}


/************************************************************************/
/*	関数名		：ZbmlDateAddDays()										*/
/*	機能概要	：システム日付から指定日数前後の日付を取得する			*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/*	 第２引数	：int		days		日数							*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL  ZbmlDateAddDays(BmlDate *date, int days)
{
    return ZbmlDateAdd(date, 0, 0, days);
}


/************************************************************************/
/*	関数名		：ZbmlDateAdd()											*/
/*	機能概要	：システム日付から指定日数前後の日付を取得する			*/
/*					(年月対応版)										*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date	システム日付						*/
/*	 第２引数	：int		y		年数								*/
/*	 第３引数	：int		m		月数								*/
/*	 第４引数	：int		d		日数								*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL  ZbmlDateAdd(BmlDate *date, int y, int m, int d)
{
    int year, month, day;
    int days;

    if (NULL == date)
	return FALSE;

    year = date->year + y;
    month= date->month+ m;
    day  = date->day;

    if (month > 12){
		year += (month-1)/12;
        month = (month-1)%12+1;
	}
    else if (month < 1){
		year -= (-month)/12+1;
        month = 12-(-month)%12;
	}
	
    days = ZbmlDateDaysOfMonth(year, month);
    if (day > days) {
        day = days;
	}

    day += d;

    if (d > 0){
        while(1){
            int days = ZbmlDateDaysOfMonth(year, month);
            if (day <= days) {
                break;
			}
            day -= days;
            month++;

			if (month > 12) {
               month = 1, year++;
			}
       }
    }
    else if (d < 0){
        while(day <= 0){
            if (month == 1) {
                month = 12, year--;
            }else {
                month--;
			}

            day += ZbmlDateDaysOfMonth(year, month);
        }
    }

    date->year = year;
    date->month= month;
    date->day  = day;

    return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlDateSetHolidays()									*/
/*	機能概要	：年間休日テーブルの取得/変更							*/
/*	入力																*/
/*	 第１引数	：BmlDateHolidayInfo*	array		休日テーブル		*/
/*	 第２引数	：BOOL					append		0：取得				*/
/*													0以外：更新			*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL  ZbmlDateSetHolidays(BmlDateHolidayInfo *array, BOOL append)
{
    int num_new;
    BmlDateHolidayInfo *array_new;

	if (array == NULL){
		if (append) {
			return FALSE;
		}

		if (userHolidays) {
			free(userHolidays);
		}
		userHolidays = NULL;
		return TRUE;
	}

    for (num_new=0; array[num_new].month; num_new++)	;

    if (append){
		int num_old;

        for (num_old=0; userHolidays[num_old].month; num_old++)	;

        array_new = (BmlDateHolidayInfo*)
			calloc(sizeof(BmlDateHolidayInfo),num_old+num_new+1);

        memcpy(array_new, userHolidays, sizeof(BmlDateHolidayInfo)*num_old);
        memcpy(array_new+num_old, array, sizeof(BmlDateHolidayInfo)*num_new);

        num_new += num_old;
    }
    else{
        array_new = (BmlDateHolidayInfo*)
			calloc(sizeof(BmlDateHolidayInfo),num_new+1);

        memcpy(array_new, array, sizeof(BmlDateHolidayInfo)*num_new);
    }

    array_new[num_new].month = 0;

    if (userHolidays) {
        free(userHolidays);
	}

    userHolidays = array_new;

    return TRUE;
}


/************************************************************************/
/*	関数名		：ZbmlDateInRange()										*/
/*	機能概要	：日付が指定した範囲内にあるかどうかをチェックする		*/
/*	入力																*/
/*	 第１引数	：BmlDate*	date		システム日付					*/
/*	 第２引数	：BOOL					append		0：取得				*/
/*													0以外：更新			*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateInRange(BmlDate *date, ULONG begin, ULONG end)
{
	ULONG ndate;

	if (NULL == date) {
		return FALSE;
	}

	if (ZbmlDateAsInteger(date, &ndate) == FALSE) {
		return FALSE;
	}
	
	if (begin != DT_NOLIMIT){
		if (convertIntegerDate(&begin) == FALSE) {
			return FALSE;
		}
		if (ndate < begin) {
			return FALSE;
		}
	}

	if (end != DT_NOLIMIT){
		if (convertIntegerDate(&end) == FALSE) {
			return FALSE;
		}
		if (ndate > end) {
			return FALSE;
		}
	}

	return TRUE;
}


/************************************************************************/
/*	関数名		：convertIntegerDate()                                  */
/*	機能概要	：シンボルを使って指定した日付を実際の日付に変換する。	*/
/*	入力																*/
/*	 第１引数	：ULONG *ndate [IO] YYYYMMDD またはシンボルの日付		*/
/*					変換後の日付もここへ入る。							*/
/* 	出力																*/
/*	 なし																*/
/************************************************************************/
static BOOL convertIntegerDate(ULONG *ndate)
{
	if (NULL == ndate) {
		return FALSE;
	}

	if (*ndate == DT_TODAY || *ndate == DT_YESTERDAY || *ndate == DT_TOMORROW){
		BmlDate date;
		ZbmlDateGetToday(&date);

		if (*ndate == DT_YESTERDAY) {
			ZbmlDateAddDays(&date, -1);
		} else if (*ndate == DT_TOMORROW) {
			ZbmlDateAddDays(&date, 1);
		}

		if (ZbmlDateAsInteger(&date, ndate) == FALSE) {
			return FALSE;
		}
	}

	return TRUE;
}


/************************************************************************/
/*	関数名		：ZbmlDateCalcAge()										*/
/*	機能概要	：比較日付がシステム日付より何年何ヶ月たっているかを	*/
/*					算出する											*/
/*	入力																*/
/*	 第１引数	：BmlDate*	bdate		比較日付						*/
/*	 第２引数	：BmlDate*	date		システム日付					*/
/*	 第３引数	：int*		ageOut		年								*/
/*	 第４引数	：int*		monthOut	月								*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateCalcAge(BmlDate *bdate, BmlDate *date, int *ageOut, int *monthOut)
{
	int age;

	if (NULL == bdate || NULL == date || NULL == ageOut)
		return FALSE;

	age = date->year - bdate->year;
	if (date->month < bdate->month ||
		(date->month == bdate->month && date->day < bdate->day))
		age--;

	*ageOut = age;
	if (monthOut)
		*monthOut = (date->month + 12 - bdate->month) % 12;

	return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlDateDiff()										*/
/*	機能概要	：２つの日付の差を計算する。							*/
/*	入力																*/
/*	 第１引数	：BmlDate 	*bdate		引く側の日付					*/
/*	 第２引数	：BmlDate 	*edate		引かれる側の日付				*/
/*	 第３引数	：long 		*diff		差の日数						*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateDiff(BmlDate *bdate, BmlDate *edate, long *diffOut)
{
	ULONG lday1, lday2;

	if (NULL == bdate || NULL == edate || NULL == diffOut) {
		return FALSE;
	}

	if ((lday1 = ZbmlDateDayNumber(bdate)) == 0L ||
		(lday2 = ZbmlDateDayNumber(edate)) == 0L) {
		return FALSE;
	}

	*diffOut = 	(lday1 < lday2) ? (long)(lday2-lday1) : -(long)(lday1-lday2);
	return TRUE;
}

/************************************************************************/
/*	関数名		：ZbmlIsNullDate()										*/
/*	機能概要	："1000-01-01" と一致するかどうかを返す。				*/
/*	入力																*/
/*	 第１引数   :　char *sdate   チェックする日付文字列					*/
/*	 第２引数   :　BOOL *nullOut 一致するか(TRUE) 否か(FALSE)			*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlIsNullDate(char *sdate, BOOL *nullOut)
{
	if (NULL == sdate || NULL == nullOut) {
		return FALSE;
	}

	*nullOut = (strcmp(sdate, "1000-01-01") == 0);
	return TRUE;
}


/************************************************************************/
/*	関数名		：searchHoliday()										*/
/*	機能概要	：指定された日付が休日情報に含まれるかどうかを返す。	*/
/*	入力																*/
/*	 第１引数   :　BmlDateHolidayInfo *array 休日情報の配列				*/
/*	 第２引数   :　BmlDate *date             チェックする日付			*/
/*	 第３引数   :　BOOL *bAlt              振り替えか否かを返すバッファ	*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
static BOOL searchHoliday(BmlDateHolidayInfo *array, BmlDate *date, BOOL *bAlt)
{
	int i;
	int dow;

    for (i=0; array[i].month; i++){
		BmlDateHolidayInfo *info = array+i;
		if (info->month == date->month && info->day == date->day){
			*bAlt = FALSE;
			return TRUE;
		}
    }

    dow = ZbmlDateDayOfWeek(date);

	// 月曜日の場合
    if (dow == 1){
        for (i=0; array[i].month; i++){
            BmlDateHolidayInfo *info = theHolidays+i;
            if (info->alt && info->month == date->month && info->day == date->day-1){
				*bAlt = TRUE;
				return TRUE;
			}
        }
    }

	return FALSE;
}


/************************************************************************/
/*	関数名		：ZbmlDateGetHolidayType()								*/
/*	機能概要	：指定された日付が国民の休日かどうかを返す。			*/
/*	入力																*/
/*	 第１引数   :　BmlDate *date    チェックする日付					*/
/*	 第２引数   :　BmlDateHolidayType *typeOut							*/
/*						休日の種別を返すためのバッファ。 				*/
/* 	出力																*/
/*	 正常：TRUE															*/
/*	 異常：FALSE														*/
/************************************************************************/
BOOL ZbmlDateGetHolidayType(BmlDate *date, BmlDateHolidayType *typeOut)
{
	BOOL bAlt;

    if (NULL == date || NULL == typeOut) {
		return FALSE;
	}

	if (userHolidays &&  searchHoliday(userHolidays, date, &bAlt)){
		*typeOut = (bAlt) ? HT_AltUserHoliday : HT_UserHoliday;
		return TRUE;
	}

	if (theHolidays &&  searchHoliday(theHolidays, date, &bAlt)){
		*typeOut = (bAlt) ? HT_AltHoliday : HT_Holiday;
		return TRUE;
	}

    *typeOut = HT_NotHoliday;
	return TRUE;
}
/** End of File *********************************************************/
