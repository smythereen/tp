/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

s32	TP_prefix(TPD_Bump) ( tpd_t * tp, char * file )
{
	_TPD_Check( tp, file );
	return( _tp_Bump( (TP_t *)tp ) );
}
