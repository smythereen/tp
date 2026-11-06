/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

s32	TP_prefix(TPS_Add) ( tps_t * tp, s32 i )
{
	_TPS_Check( tp );
	return( _tp_Add( (TP_t *)tp, i ) );
}
