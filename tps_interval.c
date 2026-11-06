/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

s32	TP_prefix(TPS_Interval) ( tps_t * tp )
{
	return( _tp_Interval( (TP_t *)tp, (u32)TPS_MAX_INTERVALS, NULL ) );
}
