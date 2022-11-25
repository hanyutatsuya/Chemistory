#!/bin/bash
############################################################
#
# プロセス監視停止
#
# 2016-04-07 Create H.Sekiya
#
# 作業等でプロセス監視を一時的に停止する場合に使用。
# 監視停止ファイルを作成する。
# 監視を再開するには、コレで作成したファイルを削除すればよい。
# 長時間監視を停止していると、警告メールが来るので注意。
############################################################

# 監視対象の設定
CHK_DIR_Z="/home/kea00sys/shell/cron"

IA_CNT="4"
CHK_IA=(KEA00IAW21.bml.co.jp KEA00IAW22.bml.co.jp KEA00IAW23.bml.co.jp KEA00IAW24.bml.co.jp)
CHK_DIR_IA="/home/kea00sys/shell"

STOP_FILE_NAME="STOP"

touch ${CHK_DIR_Z}/${STOP_FILE_NAME}

for i in `seq 0 $((${IA_CNT} - 1))`;
do
	rsh ${CHK_IA[$i]} touch ${CHK_DIR_IA}/${STOP_FILE_NAME}
done

exit 0
