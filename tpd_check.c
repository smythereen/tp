/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

u32	TP_prefix(TPD_Check) ( tpd_t * tp, char * file )
{
	return( _tp_Check( (TP_t *)tp, file, TPD_MAX_INTERVALS, ((TPD_MAX_INTERVALS - 1) * TPD_DURATION)));
}
