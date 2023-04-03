#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpncalc.h"

int		main()
{
	int		nRet;
	char	fomula[RPN_BUFF_MAX];
	char	rpnfomulaz[RPN_BUFF_MAX];
	char	rpnfomulag[RPN_BUFF_MAX];
	RPNKEKKATBL	tbl[4];

#ifdef	AAAAAAA
	strcpy(fomula,"aaa = 1 + 2 + 3 + 4 + 5");
	nRet = RpnConv(fomula,rpnfomula);
	printf("[%s]\n",fomula);
	printf("[%d][%s]\n",nRet,rpnfomula);

	strcpy(fomula,"aaa  =  -1 + 2 - 3 * 4 + 5 / 6 - 7");
	nRet = RpnConv(fomula,rpnfomula);
	printf("[%s]\n",fomula);
	printf("[%d][%s]\n",nRet,rpnfomula);

	strcpy(fomula,"xxx =  ( 2.3 * LN 20.5 ) + ( 0.4 * LN 17.2 ) - 25.3");
	nRet = RpnConv(fomula,rpnfomula);
	printf("[%s]\n",fomula);
	printf("[%d][%s]\n",nRet,rpnfomula);

	strcpy(fomula,"xxx  = ( 2.3 * LN [CA125] ) + ( 0.4 * LN [HE4] ) - 25.3");
	nRet = RpnConv(fomula,rpnfomula);
	printf("[%s]\n",fomula);
	printf("[%d][%s]\n",nRet,rpnfomula);
#endif
	tbl[0].kcode = 11593;
	tbl[1].kcode = 453;
	tbl[2].kcode = 454;
	tbl[3].kcode = 460;
	tbl[0].point = 1;
	tbl[1].point = 0;
	tbl[2].point = 0;
	tbl[3].point = 0;
	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"65.5");
	strcpy(tbl[3].inprst,"14.5");

	strcpy(fomula,"[0011593] = (([0000453]-([0000460]+([0000454]/5)))/[0000460])");
	strcpy(fomula,"[11593] = (([453]-([460]+([454]/5)))/[460])");
	nRet = RpnConv(fomula,rpnfomulaz);
	printf("[%s]\n",fomula);
	printf("[%d][%s]\n",nRet,rpnfomulaz);

	strcpy(fomula,"[0011593] = (ROUND(([0000453]-([0000460]+([0000454]/5))),1)/[0000460])");
	nRet = RpnConv(fomula,rpnfomulag);
	printf("[%s]\n",fomula);
	printf("[%d][%s]\n",nRet,rpnfomulag);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"202");
	strcpy(tbl[2].inprst,"137");
	strcpy(tbl[3].inprst,"52");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("2.4[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[0].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"202");
	strcpy(tbl[2].inprst,"138");
	strcpy(tbl[3].inprst,"52");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("2.3[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[0].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"202");
	strcpy(tbl[2].inprst,"139");
	strcpy(tbl[3].inprst,"52");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("2.3[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[0].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"202");
	strcpy(tbl[2].inprst,"140");
	strcpy(tbl[3].inprst,"52");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("2.3[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[0].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"202");
	strcpy(tbl[2].inprst,"165");
	strcpy(tbl[3].inprst,"52");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("2.3[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[0].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"202");
	strcpy(tbl[2].inprst,"166");
	strcpy(tbl[3].inprst,"52");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("2.3[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[0].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"202");
	strcpy(tbl[2].inprst,"167");
	strcpy(tbl[3].inprst,"52");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("2.3[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[0].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"202");
	strcpy(tbl[2].inprst,"168");
	strcpy(tbl[3].inprst,"52");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("2.2[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[0].inprst);

	return 0;
}

