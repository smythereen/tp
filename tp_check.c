/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

int	TP_prefix(TP_Check) ( tp_t * tp )
{
	if( !_tp_Check( (TP_t *)&tp->tps,         NULL, TPS_MAX_INTERVALS,  (TPS_MAX_INTERVALS - 1))) return( 0 );
	if( !_tp_Check( (TP_t *)&tp->tpd, tp->tpd_file, TPD_MAX_INTERVALS, ((TPD_MAX_INTERVALS - 1) * TPD_DURATION))) return( 1 );
	return( 2 );
}
