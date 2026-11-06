/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Calculate Transactions Per Second & Day
 ******************************************************************************/
#include	"tplocal.h"
#include	<map.h>

int	TP_prefix(TP_File_Bump) ( char * file )
{
	int		ret = -1;
	tp_t	*	tp = (tp_t *)_tp_File( file, sizeof( tp_t ) );
	if( tp != NULL ) {
		ret = _TP_Bump( tp );
		UnmapAddress( tp, 0 );
	}
	return( ret );
}
