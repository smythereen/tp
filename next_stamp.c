/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Next Time Stamp Function
 ******************************************************************************/
#include	"tplocal.h"

u32	TP_prefix(tp_Next_Stamp) ( u32 max )
{
	struct	tm	tbuf;
	time_t		stamp = time( 0 );
	switch( max ) {
	case TPD_MAX_INTERVALS:
				localtime_r( &stamp, &tbuf );
				tbuf.tm_mday += 1;
				tbuf.tm_hour = 0;
				tbuf.tm_min = 0;
				break;
	case TPH_MAX_INTERVALS:
				localtime_r( &stamp, &tbuf );
				tbuf.tm_hour += 1;
				tbuf.tm_min = 0;
				break;
	case TPM_MAX_INTERVALS:
				localtime_r( &stamp, &tbuf );
				tbuf.tm_min += 1;
				break;
	default:	
				return( (u32)( stamp + 1 ) );
	}
	tbuf.tm_sec = 0;
	return( (u32)mktime( &tbuf ) );
}
