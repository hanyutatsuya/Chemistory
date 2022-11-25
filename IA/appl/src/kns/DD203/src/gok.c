void 
BskgokConv ( pFrom, pTo )
char	*pFrom ;
char	*pTo ;
{
	if( pFrom[0] == 'C' ) {
		if( pFrom[1] == '\0' ) {
			pTo[2] = '0';
			pTo[3] = '1';
			pTo[4] = '0';
			pTo[5] = '1';
		} 
		else if( pFrom[2] == '\0' ) {
			pTo[2] = '0';
			pTo[3] = '1';
			pTo[4] = '0';
			pTo[5] = pFrom[1];
		}
		else {
			pTo[2] = '0';
			pTo[3] = pFrom[1];
			pTo[4] = '0';
			pTo[5] = pFrom[2];
		}
	} else {
		pTo[2] = '0';
		pTo[3] = '0';
		pTo[4] = '0';
		if( pFrom[3] == '\0' ) {
			pTo[5] = '1';
		} else {
			pTo[5] = pFrom[3];
		}
	}
	return ;
}
