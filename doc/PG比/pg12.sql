select 'AAAAAAAA',
k1.utkymd as utkymd,k1.irino as irino,
k1.kmkcd,m1.kmkrs,k1.hjkka,k1.knsflg,case when k1.bskgok = '' then '0' else k1.bskgok end,k1.bskseq,
k2.kmkcd,m2.kmkrs,k2.hjkka,k2.knsflg,case when k2.bskgok = '' then '0' else k2.bskgok end,k2.bskseq,
k3.kmkcd,m3.kmkrs,k3.hjkka,k3.knsflg,case when k3.bskgok = '' then '0' else k3.bskgok end,k3.bskseq,
'0000000' as kmkcd,'XXXXX' as kmkrs,'XXXXXXXX' as kjkka,'Z' as knsflg,'0' as bskgok,'0' as bskseq
from kekka k1,kekka k2,kekka k3,
kmkmst m1,kmkmst m2,kmkmst m3,sysknrmst s
where s.lbcd = '001'
and k1.sriymd = s.kjnsriymd
and k1.kmkcd = '0003734'
and k1.knsflg in ('E','X','S')
and k1.siyflg = '1'
and k2.utkymd = k1.utkymd
and k2.irino = k1.irino
and k2.kmkcd = '0003735'
and k2.knsflg in ('E','X','S')
and k2.siyflg = '1'
and k3.utkymd = k1.utkymd
and k3.irino = k1.irino
and k3.kmkcd = '0003736'
and k3.knsflg in ('E','X','S')
and k3.siyflg = '1'
and (k1.bskseq != k2.bskseq or k2.bskseq != k3.bskseq)
and k1.bskseq > 0
and k2.bskseq > 0
and k3.bskseq > 0
and m1.knsgrp = k1.knsgrp
and m1.kmkcd = k1.kmkcd
and m2.knsgrp = k2.knsgrp
and m2.kmkcd = k2.kmkcd
and m3.knsgrp = k3.knsgrp
and m3.kmkcd = k3.kmkcd
union all
select 'AAAAAAAA',
k1.utkymd as utkymd,k1.irino as irino,
k1.kmkcd,m1.kmkrs,k1.hjkka,k1.knsflg,case when k1.bskgok = '' then '0' else k1.bskgok end,k1.bskseq,
k2.kmkcd,m2.kmkrs,k2.hjkka,k2.knsflg,case when k2.bskgok = '' then '0' else k2.bskgok end,k2.bskseq,
k3.kmkcd,m3.kmkrs,k3.hjkka,k3.knsflg,case when k3.bskgok = '' then '0' else k3.bskgok end,k3.bskseq,
k4.kmkcd,m4.kmkrs,k4.hjkka,k4.knsflg,case when k4.bskgok = '' then '0' else k4.bskgok end,k4.bskseq
from kekka k1,kekka k2,kekka k3,kekka k4,
kmkmst m1,kmkmst m2,kmkmst m3,kmkmst m4,sysknrmst s
where s.lbcd = '001'
and k1.sriymd = s.kjnsriymd
and k1.kmkcd = '0003734'
and k1.knsflg in ('E','X','S')
and k1.siyflg = '1'
and k2.utkymd = k1.utkymd
and k2.irino = k1.irino
and k2.kmkcd = '0003735'
and k2.knsflg in ('E','X','S')
and k2.siyflg = '1'
and k3.utkymd = k1.utkymd
and k3.irino = k1.irino
and k3.kmkcd in ('0021644','0021996','0022672','0022679')
and k3.knsflg in ('E','X','S')
and k3.siyflg = '1'
and k4.utkymd = k1.utkymd
and k4.irino = k1.irino
and k4.kmkcd in ('0021645','0021993','0022669','0022676')
and k4.knsflg in ('E','X','S')
and k4.siyflg = '1'
and (k1.bskseq != k2.bskseq or k2.bskseq != k3.bskseq or k3.bskseq != k4.bskseq)
and k1.bskseq > 0
and k2.bskseq > 0
and k3.bskseq > 0
and k4.bskseq > 0
and m1.knsgrp = k1.knsgrp
and m1.kmkcd = k1.kmkcd
and m2.knsgrp = k2.knsgrp
and m2.kmkcd = k2.kmkcd
and m3.knsgrp = k3.knsgrp
and m3.kmkcd = k3.kmkcd
and m4.knsgrp = k4.knsgrp
and m4.kmkcd = k4.kmkcd
order by utkymd,irino
for read only with ur;
