<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
	require_once("../comm/labo_html.inc");
	require_once("../comm/labo_db.inc");

	if (isset($_COOKIE["LBCODE"])){
		$lbcode = $_COOKIE["LBCODE"];
	} else {
		$lbcode = -1;
	}

	$message = $_REQUEST['MESSAGE'];
	$yukou   = $_REQUEST['YUKOU'];
	$btn     = $_REQUEST['SUBMIT'];

	if ($yukou == NULL) {
		$yukou = 30;
	}

	if (($btn == "submit") && ($message != NULL)) {

		$sa = sprintf("+%d day",$yukou);
		$tt = strtotime($sa);  // ２時間後
		$tt = $tt + (9 * 60 * 60); // JST調整
		$lim = date("Y-m-d 00:00:00",$tt);

		try {
			$conn = GetDBConn();
			if ($conn) {

				$conn->beginTransaction();

				$sql = "";
				$sql = $sql . "insert into dat_inform values (";
				$sql = $sql . "'" . $lbcode . "'," . CURRENT_TIMESTAMP . ",";
				$sql = $sql . "'" . $lim . "',0,'" . $message . "')" ;
				$pdst = $conn->prepare($sql);
				$res = $pdst->execute();
				if  ($res != TRUE) {
					throw new Exception('DB Insert Error');
				}

				$conn->commit();
			} else {
				printf("Connection failed\n");
			}
	
		}
		catch (PDOException $PDOex) {
			LaboLogOut(sprintf("SQLMSG  [%s]",$PDOex->getMessage()));
			LaboLogOut(sprintf("SQLCODE  [%s]",$PDOex->getCode()));
			$conn->rollBack();
			printf("Insert error\n");
		}
		catch (PDOException $ex) {
			LaboLogOut(sprintf("ERRMSG  [%s]",$ex->getMessage()));
			LaboLogOut(sprintf("ERRCODE  [%s]",$ex->getCode()));
			$conn->rollBack();
			printf("Insert error\n");
		}
		catch (Exception $e) {
			LaboLogOut(sprintf("ERRMSG  [%s]",$e->getMessage()));
			$conn->rollBack();
			printf("Insert error\n");
		}
		$message = "";
		$conn = null;
	}

	LaboHeadOutput("お知らせ情報設定");
	LaboLogOut("お知らせ情報設定");
?>

<BODY background="../img/blue_p8b.gif">

<?php
	LaboTimeStamp();
?>

<center><h2>お知らせ情報設定</h2></center>

<?php
	try {
		$conn = GetDBConn();
		if ($conn) {

			$meisho = GetLaboName($conn,$lbcode);
			printf("<center><P>ラボ名称：%s</P></center>\n",$meisho);

			$sql = "";
			$sql = $sql . "select lbcode,toroku,yukou,delflg,contents";
			$sql = $sql . " from Dat_Inform";
			$sql = $sql . " where lbcode = '" . $lbcode . "'";
			$sql = $sql . " and delflg = 0";
			$sql = $sql . " order by toroku desc";

			printf("<table align=\"center\" bgcolor = \"white\" border>\n");
			printf("<tr>\n");
			printf("<th width=80>ラボコード</th>\n");
			printf("<th width=180>登録日時</th>\n");
			printf("<th width=180>有効年月日</th>\n");
			printf("<th width=50>削除F</th>\n");
			printf("<th width=450>内容</th>\n");
			printf("</tr>\n");
			foreach ($conn->query($sql) as $row) {
				printf("<tr>\n");
				printf("<td width=80 align=\"center\">%s</td>\n",$row['lbcode']);
				printf("<td width=180>%s</td>\n",substr($row['toroku'],0,19));
				printf("<td width=180>%s</td>\n",substr($row['yukou'],0,19));
				printf("<td width=50 align=\"center\">%d</td>\n",$row['delflg']);
				printf("<td width=450>%s</td>\n",$row['contents']);
				printf("</tr>\n");
			}
			printf("</table>\n");
		} else {
			printf("Connection failed\n");
		}
	
	}
	catch (PDOException $PDOex) {
		LaboLogOut(sprintf("SQLMSG  [%s]",$PDOex->getMessage()));
		LaboLogOut(sprintf("SQLCODE  [%s]",$PDOex->getCode()));
	}
	catch (PDOException $ex) {
		LaboLogOut(sprintf("ERRMSG  [%s]",$ex->getMessage()));
		LaboLogOut(sprintf("ERRCODE  [%s]",$ex->getCode()));
	}

	$conn = null;

print <<<__INTEXT__
<HR>

<FORM ACTION="mnt_info.php" METHOD=POST>

<div>
	<div style="float:left; width:20%;">
		<BR>
	</div>

	<div style="float:right; width:80%;">
		<div align="left">
			お知らせ　
			<INPUT TYPE=text align="left" NAME=MESSAGE SIZE=64 MAXLENGTH=64 value=$message>
		</div>
		<br>
		<div alien="left">
			掲示日数　
			<INPUT TYPE=text align="left" NAME=YUKOU SIZE=4 MAXLENGTH=2 value=$yukou>
		</div>
		<BR>
	</div>

</div>
<div>
	<div align="center" style="clear:right;">
		<BUTTON type=submit name=SUBMIT value="submit">登　録</BUTTON>
	</div>
</div>

</FORM>
<HR>
__INTEXT__;


	MenteTailOut();
?>

<HR>
</BODY>
</HTML>
