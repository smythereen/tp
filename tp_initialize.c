/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

void	TP_prefix(TP_Initialize) ( tp_t * tp )
{
	_tp_Initialize( (TP_t *)&tp->tps, TPS_MAX_INTERVALS );
	_tp_Initialize( (TP_t *)&tp->tpd, TPD_MAX_INTERVALS );
}
