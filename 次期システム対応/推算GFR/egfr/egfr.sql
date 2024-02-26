select 'AAAAAAAA',
k1.utkymd as utkymd,k1.irino as irino,
k1.kmkcd,m1.kmkrs,k1.hjkka,k1.knsflg,
k2.kmkcd,m2.kmkrs,k2.hjkka,k2.knsflg
from kekka k1,kekka k2,
kmkmst m1,kmkmst m2,sysknrmst s
where s.lbcd = '001'
and k1.sriymd = s.kjnsriymd
and k1.kmkcd = '0000413'
--and k1.knsflg in ('H','X','S')
--and k1.siyflg = '1'
and k2.utkymd = k1.utkymd
and k2.irino = k1.irino
and k2.kmkcd in ('0000538','0000579','0002696')
and k2.knsflg in ('H')
and k2.siyflg = '1'
and m1.knsgrp = k1.knsgrp
and m1.kmkcd = k1.kmkcd
and m2.knsgrp = k2.knsgrp
and m2.kmkcd = k2.kmkcd
union all
select 'AAAAAAAA',
k1.utkymd as utkymd,k1.irino as irino,
k1.kmkcd,m1.kmkrs,k1.hjkka,k1.knsflg,
k2.kmkcd,m2.kmkrs,k2.hjkka,k2.knsflg
from kekka k1,kekka k2,
kmkmst m1,kmkmst m2,sysknrmst s
where s.lbcd = '001'
and k1.sriymd = s.kjnsriymd
and k1.kmkcd = '0002480'
--and k1.knsflg in ('E','X','S')
--and k1.siyflg = '1'
and k2.utkymd = k1.utkymd
and k2.irino = k1.irino
and k2.kmkcd = '0007959'
and k2.knsflg in ('H')
and k2.siyflg = '1'
and m1.knsgrp = k1.knsgrp
and m1.kmkcd = k1.kmkcd
and m2.knsgrp = k2.knsgrp
and m2.kmkcd = k2.kmkcd
union all
select 'AAAAAAAA',
k1.utkymd as utkymd,k1.irino as irino,
k1.kmkcd,m1.kmkrs,k1.hjkka,k1.knsflg,
k2.kmkcd,m2.kmkrs,k2.hjkka,k2.knsflg
from kekka k1,kekka k2,
kmkmst m1,kmkmst m2,sysknrmst s
where s.lbcd = '001'
and k1.sriymd = s.kjnsriymd
and k1.kmkcd = '0002780'
--and k1.knsflg in ('E','X','S')
--and k1.siyflg = '1'
and k2.utkymd = k1.utkymd
and k2.irino = k1.irino
and k2.kmkcd = '0007960'
and k2.knsflg in ('H')
and k2.siyflg = '1'
and m1.knsgrp = k1.knsgrp
and m1.kmkcd = k1.kmkcd
and m2.knsgrp = k2.knsgrp
and m2.kmkcd = k2.kmkcd
order by utkymd,irino
for read only with ur;
