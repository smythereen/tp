/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

u32	TP_prefix(TPS_Check) ( tps_t * tp )
{
	return( _tp_Check( (TP_t *)tp, NULL, TPS_MAX_INTERVALS,  (TPS_MAX_INTERVALS - 1)));
}
