select 'AAAAAAAA',
k1.utkymd as utkymd,k1.irino as irino,
k1.kmkcd,m1.kmkrs,k1.hjkka,k1.knsflg,
k2.kmkcd,m2.kmkrs,k2.hjkka,k2.knsflg
from kekka k1,kekka k2,hkhrirai hi,
kmkmst m1,kmkmst m2,sysknrmst s
where s.lbcd = '001'
and k2.sriymd = s.kjnsriymd
and hi.utkymd = k2.utkymd
and hi.irino = k2.irino
and hi.kmkcd in ('0000538','0000579','0002696','0007959','0007960')
and hi.hkkhrkbn != '0'
--and hi.knsgrp = k2.knsgrp
and hi.kmkcd = k2.kmkcd
and k2.knsflg = 'A'
and k2.kkajkcd = '3'
and k1.utkymd = k2.utkymd
and k1.irino = k2.irino
and k1.knsgrp = k2.knsgrp
and k1.kmkcd in ('0000413','0002480','0002780')
and k1.knsflg = 'A'
and k1.kkajkcd = '3'
and m1.knsgrp = k1.knsgrp
and m1.kmkcd = k1.kmkcd
and m2.knsgrp = k2.knsgrp
and m2.kmkcd = k2.kmkcd
order by utkymd,irino
for read only with ur;
