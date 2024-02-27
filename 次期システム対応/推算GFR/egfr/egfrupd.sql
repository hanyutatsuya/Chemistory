update kekka ku
set ku.knsflg =
	CASE
		WHEN ku.kmkcd = '0000413' THEN 'S'
		WHEN ku.kmkcd = '0002480' THEN 'S'
		WHEN ku.kmkcd = '0002780' THEN 'S'
		ELSE 'H'
	END
	,tnyrkflg = '1'
where ku.kmkcd in ('0000538','0000579','0002696','0007959','0007960','0000413','0002480','0002780')
and ku.knsflg = 'A'
and ku.kkajkcd = '3'
and exists (select * from kekka k1,kekka k2,hkhrirai hi,sysknrmst s
where s.lbcd = '001'
and ku.sriymd = s.kjnsriymd
and hi.utkymd = ku.utkymd
and hi.irino = ku.irino
and hi.kmkcd in ('0000538','0000579','0002696','0007959','0007960')
and hi.hkkhrkbn != '0'
--and hi.knsgrp = k2.knsgrp
and hi.utkymd = k2.utkymd
and hi.irino = k2.irino
and hi.kmkcd = k2.kmkcd
and k2.knsflg = 'A'
and k2.kkajkcd = '3'
and k1.utkymd = k2.utkymd
and k1.irino = k2.irino
and k1.knsgrp = k2.knsgrp
and k1.kmkcd in ('0000413','0002480','0002780')
and k1.knsflg = 'A'
and k1.kkajkcd = '3');
