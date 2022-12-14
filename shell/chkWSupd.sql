
SELECT *
FROM IRAI I,KENORDER K
WHERE   I.ODRSSFLG = '1'
    AND I.IRINO = K.IRINO
    AND I.KMKCD = K.KMKCD
    AND I.KNSSU = K.KNSSU
    AND I.KNSGRP = '0054' 
;

SELECT I.IRINO,I.KMKCD
	,I.KNSSU AS IRAI更新前
	,'→'
	,K.MAX_SU AS 更新すべき検査回数
FROM IRAI I,
    (SELECT SRIYMD,IRINO,KMKCD,MAX(KNSSU)+1 AS MAX_SU 
        FROM KENORDER
        WHERE SRIYMD = '2006-09-25'
        AND IRINO = '$IRINO'
        AND KMKCD = '$KMKCD'
        GROUP BY SRIYMD,IRINO,KMKCD
        ) K
WHERE I.ODRSSFLG = '1'
AND I.SRIYMD = K.SRIYMD
AND I.IRINO = K.IRINO
AND I.KMKCD = K.KMKCD
ORDER BY KMKCD
;

UPDATE SET KNSSU = 4
FROM IRAI
WHERE SRIYMD = '2006-09-15'
AND IRINO = '00006073200'
AND KMKCD = '0000423'
;
