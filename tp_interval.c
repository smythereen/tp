/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

s32	TP_prefix(TP_Interval) ( tp_t * tp, char * file )
{
	time_t	now;

	if( (u32)time( &now ) < tp->tps.Stamp ) return( 0 );
	if( (u32)now >= tp->tpd.Stamp ) _tp_Interval( (TP_t *)&tp->tpd, (u32)TPD_MAX_INTERVALS, file );
	return( _tp_Interval( (TP_t *)&tp->tps, (u32)TPS_MAX_INTERVALS, NULL ) );
}
