/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Check Function
 ******************************************************************************/
#include	"tplocal.h"

u32	TP_prefix(tp_Check) ( TP_t * tp, char * file, u32 max_i, u32 max_d )
{
	u32	i;
	time_t	now;

	if( (u32)time( &now ) < tp->Stamp ) return( 0 );

	if( ( (u32)now - tp->Stamp ) >= max_d ) {
		_tp_Initialize( tp, max_i );
		return( max_i );
	}
	for( i = 0; tp->Stamp < (u32)now ; i++ ) _tp_Interval( tp, max_i, file );
	return( i );
}
