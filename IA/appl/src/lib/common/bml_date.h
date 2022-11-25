/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e�����F������V�X�e��									*/
/*		�t�@�C�����Fbml_date.h										*/
/*		�T�v      �F���t�p���ʊ֐��̃w�b�_�[�E�t�@�C��				*/
/********************************************************************/

/********************************************************************/
/*	Ver.	Date			Name			History					*/
/* ----------------------------------------------------------------	*/
/*	1.00	2005/06/14		E.Osada			Create					*/
/********************************************************************/
#ifndef _bml_date_h
#define _bml_date_h

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include "bml_base.h"

#ifdef __cplusplus
extern "C"{
#endif

/********************************************************************/
/*	�\���̒�`														*/
/********************************************************************/
typedef struct{
    int month;
    int day;
    BOOL alt;
}BmlDateHolidayInfo;

typedef enum{
    DT_WeekDay,
    DT_Saturday,
    DT_Sunday,
    DT_Holiday,
    DT_AltHoliday,
    DT_UserDefined
}BmlDateDayType;

typedef enum{
    HT_NotHoliday,
    HT_Holiday,
    HT_AltHoliday,
    HT_UserHoliday,
    HT_AltUserHoliday
}BmlDateHolidayType;

typedef struct HuDate{
    int year;
    int month;
    int day;
}BmlDate;

/********************************************************************/
/*	�v���g�^�C�v�錾												*/
/********************************************************************/
BOOL ZbmlDateGetToday(BmlDate *date);
BOOL ZbmlDateIsValid(BmlDate *date);

BOOL ZbmlDateAsString(BmlDate *date, char*);
BOOL ZbmlDateAsString2(BmlDate *date, char*);
BOOL ZbmlDateAsStringW(BmlDate *date, char*);

BOOL ZbmlDateAsInteger(BmlDate *date, ULONG*);
BOOL ZbmlDateFromString(BmlDate *date, char*);
BOOL ZbmlDateFromInteger(BmlDate *date, ULONG);

int   ZbmlDateDayOfWeek(BmlDate *date);
char *ZbmlDateDayOfWeekName(BmlDate *date);
ULONG ZbmlDateDayOfYear(BmlDate *date);
ULONG ZbmlDateDayNumber(BmlDate *date);
BOOL  ZbmlDateGetDayType(BmlDate *date, BmlDateDayType*);

int   ZbmlDateDaysOfMonth(int year, int month);
int   ZbmlDateDaysOfYear(int year);
BOOL  ZbmlDateIsLeapYear(int year);

BOOL  ZbmlDateAddDays(BmlDate *date, int days);
BOOL  ZbmlDateAdd(BmlDate *date, int years, int months, int days);

BOOL  ZbmlDateSetHolidays(BmlDateHolidayInfo *array, BOOL);

BOOL  ZbmlDateInRange(BmlDate *date, ULONG begin, ULONG end);
BOOL  ZbmlDateCalcAge(BmlDate *bdate, BmlDate *date, int *ageOut, int *monthOut);

BOOL  ZbmlDateDiff(BmlDate*, BmlDate*, long*);
BOOL  ZbmlIsNullDate(char*, BOOL*);

BOOL  ZbmlDateGetHolidayType(BmlDate*, BmlDateHolidayType*);

/********************************************************************/
/*	��������������`												*/
/********************************************************************/
#ifndef DT_NOLIMIT
#define DT_NOLIMIT    0L
#define DT_TODAY      1L
#define DT_YESTERDAY  2L
#define DT_TOMORROW   3L
#endif

#ifdef __cplusplus
}
#endif

#endif
/** End of File *****************************************************/
