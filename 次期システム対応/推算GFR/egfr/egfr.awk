# PG��pawk�p�����[�^�[�t�@�C��
BEGIN {
	cnt = 0
	line = 0
	page = 1
	stamp = strftime("DATE:%Y/%m/%d TIME:%H:%M:%S",systime())
	printf("     ���ZGFR�G���[�`�F�b�N���X�g        ")
	printf("%s  ",stamp)
	printf("Page: %3d\n\n",page)
	printf("      ������      �˗���No.  ����CD   ���ږ�         ����  FLG     ����CD   ���ږ�         ����  FLG\n")
	printf("    ------------------------------------------------------------------------------------------------\n")
}

{
	#���͋@SEQ��0�łȂ����݂̂̂���
	if ($9 != "0") {
		cnt = cnt + 1
		line = line + 1
		printf("    %s %s-%s  %s  %-8.8s %8.8s  %s    %s  %-8.8s %8.8s  %s\n",
					$2,substr($3,3,3),substr($3,6,4),$4,$5,$6,$7,$8,$9,$10,$11)

		if ((line % 5) == 0) {
			printf("\n")
		}

	}
	# 50�����Ƃɉ��y�[�W
	if (line >= 50) {
		printf("\f")
		page = page + 1
		line = 0
		printf("     ���ZGFR�G���[�`�F�b�N���X�g        ")
		printf("%s  ",stamp)
		printf("Page: %3d\n\n",page)
		printf("      ������      �˗���No.  ����CD   ���ږ�         ����  FLG     ����CD   ���ږ�         ����  FLG\n")
		printf("    ------------------------------------------------------------------------------------------------\n")
	}
}

END {
	if (cnt == 0) {
		printf("                        �Ώۃf�[�^�͂���܂���\n")
	}
	printf("    -----------  E  N  D  ---------------------------------------------\n")
}
