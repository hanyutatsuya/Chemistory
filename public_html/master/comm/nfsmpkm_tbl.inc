<?php
function nfsmpkm_table($conn,$wscode)
{
if  (!is_numeric($wscode))
	{
	if  (strlen($wscode) == 0)
		{
		return 0;
		}
	else
		{
		printf("<center>\n");
		printf("<h2>�T���v�����O�R�[�h���̓G���[</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
		return -1;
		}
	}
else
	{
	$wscd = sprintf("%04d",$wscode);

	printf("<table align=left  border=0>\n");
	printf("<tr valign=top>\n");

	printf("<td>\n");
	printf("<table bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>����</th>\n");
	printf("<th nowrap>���e</th>\n");
	printf("<th nowrap>���l</th>\n");
	printf("</tr>\n");

	$sql = "select * from nfsmpmst where smpcd = '$wscd' and ukflg = '1' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch();
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�T���v�����O�R�[�h',$row['SMPCD'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�d�����於��',$row['SMPCDNM'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�h�s�d�l�R�[�h',$row['ITMCD'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�h�s�d�l�R�[�h�QNo.',$row['ITMCDGNO'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�T�e���C�g�h�c',$row['STID'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�d����敪',$row['SWKKBN'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�d�������b�N�h�c',$row['SWKLCKID'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�d������h�c',$row['SWKSKID'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�����敪',$row['BCKBN'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�Z���敪',$row['SELKBN'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'���W���[���敪',$row['MDLKBN'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�ʏ�MAX�l',$row['TJMAXVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�ʏ�MIN�l',$row['TJMINVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�ʏ�BASE�l',$row['TJBSEVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'����MAX�l',$row['SRMAXVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'����MIN�l',$row['SRMINVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'����BASE�l',$row['SRBSEVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'����MAX�l',$row['SNMAXVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'����MIN�l',$row['SNMINVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'����BASE�l',$row['SNBSEVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�r�����e',$row['SUPURUZTKFLG'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�J�n��',$row['STYMD'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�I����',$row['EDYMD'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�쐬����',$row['SAKHM'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'�X�V����',$row['KOUHM'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'��Ǝ҂h�c',$row['SAGYOID'],' ');
	$pdst->closeCursor();
	printf("</table>\n");
	printf("</td>\n");

	printf("<td>\n");
	printf("<table bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>�e�R�[�h</th>\n");
	printf("<th nowrap>���ڃR�[�h</th>\n");
	printf("<th nowrap>���ږ�</th>\n");
	printf("<th nowrap>TBF</th>\n");
	printf("<th nowrap>�ʏ��</th>\n");
	printf("<th nowrap>���ʗ�</th>\n");
	printf("<th nowrap>������</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select oyakmkcd,kmkcd,kmknmr,bkfkkbn,tjbncryo,srbncryo,snbncryo ";
	$sql = $sql . "from nfkmkmst where smpcd = '$wscd' and ukflg = '1' ";
	$sql = $sql . "order by oyakmkcd,kmkcd for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap><A href=kmkmst.php?KMKCD=%s>%s</A></td>\n",$row[0],$row[0]);
		printf("<td nowrap><A href=kmkmst.php?KMKCD=%s>%s</A></td>\n",$row[1],$row[1]);
		printf("<td nowrap>%s</td>\n",$row[2]);
		printf("<td nowrap>%s</td>\n",$row[3]);
		printf("<td nowrap>%s</td>\n",$row[4]);
		printf("<td nowrap>%s</td>\n",$row[5]);
		printf("<td nowrap>%s</td>\n",$row[6]);
		printf("</tr>\n");
		}
	printf("</table>\n");
	printf("</td>\n");

	printf("</table>\n");
	}
	return 0;
}
?>