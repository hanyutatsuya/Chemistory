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
	tbl[0].kcode = 18102;
	tbl[1].kcode = 18103;
	tbl[2].kcode = 13065;
	tbl[3].kcode = 69363;
	tbl[0].point = 1;
	tbl[1].point = 1;
	tbl[2].point = 1;
	tbl[3].point = 1;
	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"65.5");
	strcpy(tbl[3].inprst,"14.5");

//	strcpy(fomula,"[1234] = EXP ( ( 2.38 * LOG [1236] ) + ( 0.0626 * LOG [1237] ) - 12.0 )");
//	strcat(fomula," / ( EXP ( ( 2.38 * LOG [1236] ) + ( 0.0626 * LOG [1237] ) - 12.0 ) + 1 )");
//	strcat(fomula," * 100.0");
//	strcpy(fomula,"[1234] = LN [1236]");
//	strcpy(fomula,"[18102] = ( ( EXP ( ( 2.38 * LOG [13065] ) + ( 0.0626 * LOG [69363] ) - 12.0 ) )");
//	strcat(fomula," / ( EXP ( ( 2.38 * LOG [13065] ) + ( 0.0626 * LOG [69363] ) - 12.0 ) + 1 ) )");
//	strcat(fomula," * 100.0");
//	nRet = RpnConv(fomula,rpnfomula);
//	printf("[%s]\n",fomula);
//	printf("[%d][%s]\n",nRet,rpnfomula);

	strcpy(fomula,"[18102] = ((EXP((2.38*LOG[13065])+(0.0626*LOG[69363])-12.0))");
	strcat(fomula,"/(EXP((2.38*LOG[13065])+(0.0626*LOG[69363])-12.0)+1))");
	strcat(fomula,"*100.0");
	nRet = RpnConv(fomula,rpnfomulaz);
	printf("[%s]\n",fomula);
	printf("[%d][%s]\n",nRet,rpnfomulaz);

	strcpy(fomula,"[18103] = ((EXP((1.04*LOG[13065])+(0.732*LOG[69363])-8.09))");
	strcat(fomula,"/(EXP((1.04*LOG[13065])+(0.732*LOG[69363])-8.09)+1))");
	strcat(fomula,"*100.0");
	nRet = RpnConv(fomula,rpnfomulag);
	printf("[%s]\n",fomula);
	printf("[%d][%s]\n",nRet,rpnfomulag);

	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"51.7");
	strcpy(tbl[3].inprst,"14.7");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"47.0");
	strcpy(tbl[3].inprst,"12.3");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"28.4");
	strcpy(tbl[3].inprst,"11.7");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"38.0");
	strcpy(tbl[3].inprst,"11.4");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"25.2");
	strcpy(tbl[3].inprst,"6.2");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"37.3");
	strcpy(tbl[3].inprst,"6.4");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"26.2");
	strcpy(tbl[3].inprst,"66.9");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"66.1");
	strcpy(tbl[3].inprst,"671.4");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"29.7");
	strcpy(tbl[3].inprst,"5.3");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"35.9");
	strcpy(tbl[3].inprst,"7.5");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"39.0");
	strcpy(tbl[3].inprst,"7.2");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"41.6");
	strcpy(tbl[3].inprst,"21.5");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"22.5");
	strcpy(tbl[3].inprst,"59.0");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"53.8");
	strcpy(tbl[3].inprst,"20.2");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"39.8");
	strcpy(tbl[3].inprst,"12.9");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"44.8");
	strcpy(tbl[3].inprst,"25.0");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	strcpy(tbl[0].inprst,"");
	strcpy(tbl[1].inprst,"");
	strcpy(tbl[2].inprst,"31.2");
	strcpy(tbl[3].inprst,"74.4");
	nRet = RpnCalc(rpnfomulaz,&tbl[0],4);
	printf("[%d][%s] ",nRet,tbl[0].inprst);
	nRet = RpnCalc(rpnfomulag,&tbl[0],4);
	printf("[%d][%s]\n",nRet,tbl[1].inprst);

	return 0;
}

