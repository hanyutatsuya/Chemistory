/************************************************************************/
/*																		*/
/*		�a�l�k�l���������V�X�e��										*/
/*																		*/
/*		�V�X�e�����F������												*/
/*		�t�@�C�����Fbml_date.c											*/
/*		�T�v      �F���t���실�ʊ֐�									*/
/*																		*/
/************************************************************************/

/************************************************************************/
/*  Ver.	���t			���O			�C�����e					*/
/* -------------------------------------------------------------------- */
/*	1.00	2005/06/14		E.Osada			Create						*/
/************************************************************************/

/************************************************************************/
/*	�C���N���[�h�錾													*/
/************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bml_date.h"

/************************************************************************/
/*	��������������`													*/
/************************************************************************/
#define IS_LEAP_YEAR(year) ((year)%400 == 0 || ((year)%100 != 0 && (year)%4 == 0))

/************************************************************************/
/*	�O���[�o���錾														*/
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
{"��", "��", "��", "��", "��", "��", "�y"};

static ULONG dayOfYearN[] =
{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static ULONG dayOfYearL[] =
{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

/************************************************************************/
/*	�v���g�^�C�v�錾													*/
/************************************************************************/
static BOOL convertIntegerDate(ULONG*);

/************************************************************************/
/*	�֐���		�FZbmlDateGetToday()									*/
/*	�@�\�T�v	�F�V�X�e�����t���擾����								*/
/* 	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t�̐ݒ��			*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlDateIsValid()										*/
/*	�@�\�T�v	�F���t���̑Ó������`�F�b�N����						*/
/* 	����																*/
/*	 ��P����	�FBmlDate*	date		�`�F�b�N����V�X�e�����t		*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlDateAsString()									*/
/*	�@�\�T�v	�F�V�X�e�����t��"YYYY-MM-DD"�̕�����ɕϊ�����			*/
/* 	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/*	 ��Q����	�Fchar*		str			�ϊ�������ݒ��				*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
/************************************************************************/
BOOL ZbmlDateAsString(BmlDate *date, char *str)
{
    if (NULL == date || NULL == str)
        return FALSE;

    sprintf(str, "%04d-%02d-%02d", date->year, date->month, date->day);
    return TRUE;
}

/************************************************************************/
/*	�֐���		�FZbmlDateAsString2()									*/
/*	�@�\�T�v	�F�V�X�e�����t��"YY-MM-DD"�̕�����ɕϊ�����			*/
/* 	����																*/
/*	 ��P����   :�@BmlDate*	date		�V�X�e�����t					*/
/*	 ��Q����   :�@char*	str			�ϊ�������ݒ��				*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
/************************************************************************/
BOOL ZbmlDateAsString2(BmlDate *date, char *str)
{
    if (NULL == date || NULL == str)
        return FALSE;

    sprintf(str, "%02d-%02d-%02d", date->year%100, date->month, date->day);
    return TRUE;
}

/************************************************************************/
/*	�֐���		�FZbmlDateAsStringW()									*/
/*	�@�\�T�v	�F�V�X�e�����t��a�����ɕϊ�����					*/
/* 	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/*	 ��Q����	�Fchar*		str			�ϊ�������ݒ��				*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlDateAsInteger()									*/
/*	�@�\�T�v	�F�V�X�e�����t����P�ʂɕϊ�����						*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/*	 ��Q����	�FULONG*		valueOut	�ϊ����ݒ��				*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
/************************************************************************/
BOOL ZbmlDateAsInteger(BmlDate *date, ULONG *valueOut)
{
    if (NULL == date || NULL == valueOut)
        return FALSE;

    *valueOut = date->year*10000 + date->month*100 + date->day;

    return TRUE;
}


/************************************************************************/
/*	�֐���		�FZbmlDateFromString()									*/
/*	�@�\�T�v	�F�V�X�e�����t"YYYYMMDD"or"YYMMDD"������ɕϊ�����		*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/*	 ��Q����	�Fchar*		str			�ݒ��							*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlDateFromInteger()									*/
/*	�@�\�T�v	�F���P�ʂ̓��t���V�X�e�����t�ɕϊ�����					*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/*	 ��Q����	�FULONG*	value		��								*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlDateDayOfWeek()									*/
/*	�@�\�T�v	�F�V�X�e�����t�̗j���𐔒l�ŕԂ�						*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/* 	�o��																*/
/*	 ����F1->7															*/
/*	 �ُ�F0															*/
/************************************************************************/
int ZbmlDateDayOfWeek(BmlDate *date)
{
    return (ZbmlDateDayNumber(date)+1)%7;
}


/************************************************************************/
/*	�֐���		�FZbmlDateDayOfWeekName()								*/
/*	�@�\�T�v	�F�V�X�e�����t�̗j���������ŕԂ�						*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/* 	�o��																*/
/*	 ����F�u���v�`�u�y�v												*/
/*	 �ُ�F0															*/
/************************************************************************/
char* ZbmlDateDayOfWeekName(BmlDate *date)
{
    return dayOfWeek[ZbmlDateDayOfWeek(date)];
}


/************************************************************************/
/*	�֐���		�FZbmlDateDayOfYear()									*/
/*	�@�\�T�v	�F�V�X�e�����t���̍ŏI����Ԃ�							*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/* 	�o��																*/
/*	 ����F�V�X�e�����t���̍ŏI��										*/
/*	 �ُ�F0															*/
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
/*	�֐���		�FZbmlDateDayNumber()									*/
/*	�@�\�T�v	�F�V�X�e�����t�̓��P�ʂ�Ԃ�							*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/* 	�o��																*/
/*	 ����F�w�茎�̍ŏI��												*/
/*	 �ُ�F0															*/
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
/*	�֐���		�FZbmlDateGetDayType()									*/
/*	�@�\�T�v	�F�V�X�e�����t����y�����͕������𔻒f����B			*/
/*	����																*/
/*	 ��P����	�FBmlDate*			date		�V�X�e�����t			*/
/*	 ��Q����	�FBmlDateDayType*	typeOut								*/
/* 	�o��																*/
/*	 ����F�y�����͕���													*/
/*	 �ُ�F0															*/
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
/*	�֐���		�FZbmlDateDaysOfMonth()									*/
/*	�@�\�T�v	�F�w�茎�̍ŏI����Ԃ�									*/
/*	����																*/
/*	 ��P����	�Fint	year		�N									*/
/*	 ��Q����	�Fint	month		��									*/
/* 	�o��																*/
/*	 ����F�w�茎�̍ŏI��												*/
/*	 �ُ�F0															*/
/************************************************************************/
int   ZbmlDateDaysOfMonth(int year, int month)
{
    if (month < 1 || month > 12)
	return 0;

    return IS_LEAP_YEAR(year) ? daysOfMonthL[month-1] : daysOfMonthN[month-1];
}


/************************************************************************/
/*	�֐���		�FZbmlDateDaysOfYear()									*/
/*	�@�\�T�v	�F�w��N�̔N�ԓ�����Ԃ�								*/
/*	����																*/
/*	 ��P����	�Fint	year		�N									*/
/* 	�o��																*/
/*	 ����F�w��N�̔N�ԓ���												*/
/*	 �ُ�F0															*/
/************************************************************************/
int   ZbmlDateDaysOfYear(int year)
{
    return IS_LEAP_YEAR(year) ? 366 : 365;
}


/************************************************************************/
/*	�֐���		�FZbmlDateIsLeapYear()									*/
/*	�@�\�T�v	�F�[�N�`�F�b�N											*/
/*	����																*/
/*	 ��P����	�Fint	year		�N									*/
/* 	�o��																*/
/*	 1�F�[�N															*/
/*	 0�F�ʏ�N															*/
/************************************************************************/
BOOL  ZbmlDateIsLeapYear(int year)
{
    return IS_LEAP_YEAR(year);
}


/************************************************************************/
/*	�֐���		�FZbmlDateAddDays()										*/
/*	�@�\�T�v	�F�V�X�e�����t����w������O��̓��t���擾����			*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/*	 ��Q����	�Fint		days		����							*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
/************************************************************************/
BOOL  ZbmlDateAddDays(BmlDate *date, int days)
{
    return ZbmlDateAdd(date, 0, 0, days);
}


/************************************************************************/
/*	�֐���		�FZbmlDateAdd()											*/
/*	�@�\�T�v	�F�V�X�e�����t����w������O��̓��t���擾����			*/
/*					(�N���Ή���)										*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date	�V�X�e�����t						*/
/*	 ��Q����	�Fint		y		�N��								*/
/*	 ��R����	�Fint		m		����								*/
/*	 ��S����	�Fint		d		����								*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlDateSetHolidays()									*/
/*	�@�\�T�v	�F�N�ԋx���e�[�u���̎擾/�ύX							*/
/*	����																*/
/*	 ��P����	�FBmlDateHolidayInfo*	array		�x���e�[�u��		*/
/*	 ��Q����	�FBOOL					append		0�F�擾				*/
/*													0�ȊO�F�X�V			*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlDateInRange()										*/
/*	�@�\�T�v	�F���t���w�肵���͈͓��ɂ��邩�ǂ������`�F�b�N����		*/
/*	����																*/
/*	 ��P����	�FBmlDate*	date		�V�X�e�����t					*/
/*	 ��Q����	�FBOOL					append		0�F�擾				*/
/*													0�ȊO�F�X�V			*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FconvertIntegerDate()                                  */
/*	�@�\�T�v	�F�V���{�����g���Ďw�肵�����t�����ۂ̓��t�ɕϊ�����B	*/
/*	����																*/
/*	 ��P����	�FULONG *ndate [IO] YYYYMMDD �܂��̓V���{���̓��t		*/
/*					�ϊ���̓��t�������֓���B							*/
/* 	�o��																*/
/*	 �Ȃ�																*/
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
/*	�֐���		�FZbmlDateCalcAge()										*/
/*	�@�\�T�v	�F��r���t���V�X�e�����t��艽�N�����������Ă��邩��	*/
/*					�Z�o����											*/
/*	����																*/
/*	 ��P����	�FBmlDate*	bdate		��r���t						*/
/*	 ��Q����	�FBmlDate*	date		�V�X�e�����t					*/
/*	 ��R����	�Fint*		ageOut		�N								*/
/*	 ��S����	�Fint*		monthOut	��								*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlDateDiff()										*/
/*	�@�\�T�v	�F�Q�̓��t�̍����v�Z����B							*/
/*	����																*/
/*	 ��P����	�FBmlDate 	*bdate		�������̓��t					*/
/*	 ��Q����	�FBmlDate 	*edate		������鑤�̓��t				*/
/*	 ��R����	�Flong 		*diff		���̓���						*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FZbmlIsNullDate()										*/
/*	�@�\�T�v	�F"1000-01-01" �ƈ�v���邩�ǂ�����Ԃ��B				*/
/*	����																*/
/*	 ��P����   :�@char *sdate   �`�F�b�N������t������					*/
/*	 ��Q����   :�@BOOL *nullOut ��v���邩(TRUE) �ۂ�(FALSE)			*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
/*	�֐���		�FsearchHoliday()										*/
/*	�@�\�T�v	�F�w�肳�ꂽ���t���x�����Ɋ܂܂�邩�ǂ�����Ԃ��B	*/
/*	����																*/
/*	 ��P����   :�@BmlDateHolidayInfo *array �x�����̔z��				*/
/*	 ��Q����   :�@BmlDate *date             �`�F�b�N������t			*/
/*	 ��R����   :�@BOOL *bAlt              �U��ւ����ۂ���Ԃ��o�b�t�@	*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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

	// ���j���̏ꍇ
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
/*	�֐���		�FZbmlDateGetHolidayType()								*/
/*	�@�\�T�v	�F�w�肳�ꂽ���t�������̋x�����ǂ�����Ԃ��B			*/
/*	����																*/
/*	 ��P����   :�@BmlDate *date    �`�F�b�N������t					*/
/*	 ��Q����   :�@BmlDateHolidayType *typeOut							*/
/*						�x���̎�ʂ�Ԃ����߂̃o�b�t�@�B 				*/
/* 	�o��																*/
/*	 ����FTRUE															*/
/*	 �ُ�FFALSE														*/
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
