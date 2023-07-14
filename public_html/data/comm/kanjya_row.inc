<?php
function kanjya_row($conn,$utkymd,$irino)
{
	if (!is_numeric($utkymd)) {
		printf("<center>\n");
		printf("<h2>受付日入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
		return -1;
		}
	} else {
		if (strlen($utkymd) != 8) {
			printf("<center>\n");
			printf("<h2>受付日入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
			return -1;
		} else {
			if (ymd_check($utkymd) == false) {
				printf("<center>\n");
				printf("<h2>受付日フォーマットエラー</h2>\n");
				printf("</center>\n");
				printf("<HR>\n");
				return -1;
			} else {
				$udate ymd_edit($utkymd);
			}
		}
	}

	if (!is_numeric($irino)) {
		if (strlen($irino) == 0) {
			return 0;
		} else {
			printf("<center>\n");
			printf("<h2>依頼書№入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
			return -1;
		}
	} else {
		$ino = sprintf("00%07d00",$irino);
	}

	printf("<table align=\"left\" bgcolor = \"white\" border>\n");
		printf("<tr>\n");

			printf("<th nowrap>ＢＭＬ受付年月日</th>\n");
			printf("<th nowrap>依頼書No</th>\n");
			printf("<th nowrap>依頼書No桁数フラグ</th>\n");
			printf("<th nowrap>属性世代Ｎｏ</th>\n");
			printf("<th nowrap>施設コード</th>\n");
			printf("<th nowrap>サブ施設コード</th>\n");
			printf("<th nowrap>カード区分1</th>\n");
			printf("<th nowrap>カード区分2</th>\n");
			printf("<th nowrap>依頼元キー</th>\n");
			printf("<th nowrap>診療科コード</th>\n");
			printf("<th nowrap>診療科名</th>\n");
			printf("<th nowrap>担当医コード</th>\n");
			printf("<th nowrap>担当医名</th>\n");
			printf("<th nowrap>主治医コード</th>\n");
			printf("<th nowrap>主治医名</th>\n");
			printf("<th nowrap>紹介医コード</th>\n");
			printf("<th nowrap>紹介医名</th>\n");
			printf("<th nowrap>カルテＮｏ</th>\n");
			printf("<th nowrap>患者ＩＤ</th>\n");
			printf("<th nowrap>患者名(カナ)</th>\n");
			printf("<th nowrap>患者名(漢字)</th>\n");
			printf("<th nowrap>患者名キー</th>\n");
			printf("<th nowrap>身長</th>\n");
			printf("<th nowrap>体重</th>\n");
			printf("<th nowrap>体重区分</th>\n");
			printf("<th nowrap>性別区分</th>\n");
			printf("<th nowrap>生年月日</th>\n");
			printf("<th nowrap>生年月日区分</th>\n");
			printf("<th nowrap>年齢</th>\n");
			printf("<th nowrap>年齢区分</th>\n");
			printf("<th nowrap>病棟コード</th>\n");
			printf("<th nowrap>病棟名</th>\n");
			printf("<th nowrap>受付コメント1</th>\n");
			printf("<th nowrap>受付コメント2</th>\n");
			printf("<th nowrap>受付コメント3</th>\n");
			printf("<th nowrap>受付コメントフリー1</th>\n");
			printf("<th nowrap>受付コメントフリー2</th>\n");
			printf("<th nowrap>受付コメントフリーフラグ</th>\n");
			printf("<th nowrap>入院外来区分</th>\n");
			printf("<th nowrap>妊娠週数</th>\n");
			printf("<th nowrap>保険コード</th>\n");
			printf("<th nowrap>検体総本数</th>\n");
			printf("<th nowrap>院内依頼日</th>\n");
			printf("<th nowrap>属性修正フラグ</th>\n");
			printf("<th nowrap>緊急依頼フラグ</th>\n");
			printf("<th nowrap>非検査区分</th>\n");
			printf("<th nowrap>受付区分</th>\n");
			printf("<th nowrap>ＮＥ区分</th>\n");
			printf("<th nowrap>院内検査区分</th>\n");
			printf("<th nowrap>受付状態区分</th>\n");
			printf("<th nowrap>完了フラグ</th>\n");
			printf("<th nowrap>ＦＤ非報告フラグ</th>\n");
			printf("<th nowrap>受付時刻</th>\n");
			printf("<th nowrap>元ＢＭＬ受付日</th>\n");
			printf("<th nowrap>元依頼書Ｎｏ</th>\n");
			printf("<th nowrap>検査実施ラボコード１</th>\n");
			printf("<th nowrap>検査実施ラボコード２</th>\n");
			printf("<th nowrap>検査実施ラボコード３</th>\n");
			printf("<th nowrap>検査実施ラボコード４</th>\n");
			printf("<th nowrap>翌日未報告フラグ</th>\n");
			printf("<th nowrap>翌日未報告フラグ</th>\n");
			printf("<th nowrap>営業所コード</th>\n");
			printf("<th nowrap>集配コード</th>\n");
			printf("<th nowrap>施設名正式名称</th>\n");
			printf("<th nowrap>施設名正式名称(カナ)</th>\n");
			printf("<th nowrap>施設名略称</th>\n");
			printf("<th nowrap>施設名略称(カナ)</th>\n");
			printf("<th nowrap>施設種別</th>\n");
			printf("<th nowrap>特定施設フラグ</th>\n");
			printf("<th nowrap>理由コード</th>\n");
			printf("<th nowrap>依頼項目数</th>\n");
			printf("<th nowrap>病名及び所見</th>\n");
			printf("<th nowrap>依頼入力種別</th>\n");
			printf("<th nowrap>依頼発生元区分</th>\n");
			printf("<th nowrap>特別注意施設フラグ</th>\n");
			printf("<th nowrap>治験拡張フラグ</th>\n");
			printf("<th nowrap>AUTO-P検体Ｎｏ</th>\n");
			printf("<th nowrap>診断名</th>\n");
			printf("<th nowrap>備考１</th>\n");
			printf("<th nowrap>備考２</th>\n");
			printf("<th nowrap>備考３</th>\n");
			printf("<th nowrap>属性登録日時</th>\n");
			printf("<th nowrap>属性修正日時</th>\n");
			printf("<th nowrap>サテライト内属性修正日時</th>\n");
			printf("<th nowrap>サテライト内属性修正端末IP</th>\n");
			printf("<th nowrap>サテライト内属性修正入力者</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
			printf("<th nowrap>親施設コード</th>\n");
			printf("<th nowrap>情報登録日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from kanjya where ";
		$sql = $sql . "utkymd = '$udate' and ";
		$sql = $sql . "irino = '$ino' ";
		$sql = $sql . "for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZSSDINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SUBSSTCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CDKBN1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CDKBN2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIMKEY']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SRKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SRKNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TTICD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TTINM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['GPCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['GPNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKICD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKINM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KRTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNJID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNJNMN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNJNMK']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNJNMKEY']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SC']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TJTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SBTKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BIRTHDAY']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BIRTHDAYKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['AGE']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['AGEKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BTCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BTNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKCMTCD1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKCMTCD2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKCMTCD3']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKCMTFR1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKCMTFR2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKCMTFRFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NGKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NSSSU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HKNCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KTSHSU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['INIRIYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZSSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKIRIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HKNSKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NEKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['INKNSKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKJKKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KRFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FDHHKKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['MUTKYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['MIRINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSJSLBCD1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSJSLBCD2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSJSLBCD3']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSJSLBCD4']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YMHKKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HKKKBDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ECD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SHCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTSSNMJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTSSNMN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTRSJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTRSN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTSBT']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TTSSTFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['RUCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKMKSU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BMSKN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRINRSBT']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIHSMKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CARESSTFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TKTYFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['APKNTINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SDNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BKO1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BKO2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BKO3']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['ZSTRDH']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['ZSSSDH']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['STLZSSSDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['STLZSSSIP']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['STLZSSSSYAID']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['KSNDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['OYASSTCD']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['TRKDH']));
			printf("</tr>\n");
		}
		printf("</table>\n");
	}
	catch (Exception $ex) {
		GetDBErrMsg($ex);
	}

	return 0;
}

?>
