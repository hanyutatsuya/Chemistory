
DD201.c
		for( i=0; i < p->iKekkaNum ;++i ) {
			/* 保留あつかいのフラグは変えない */
			if( p->pKekka[i].knsflg != 'H'){
				p->pKekka[i].knsflg = 'R';
			}
		}
