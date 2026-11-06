/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

int	TP_prefix(TP_Add) ( tp_t * tp, s32 i )
{
	int	r = _TP_Check( tp );
	_tp_Add( (TP_t *)&tp->tpd, i );
	_tp_Add( (TP_t *)&tp->tps, i );
	return( r );
}
