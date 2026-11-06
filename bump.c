/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Bump Function
 ******************************************************************************/
#include	"tplocal.h"

s32	TP_prefix(tp_Bump) ( TP_t * tp )
{
	s32	c = S32_Inc_Return( &tp->TP );
	if( c > tp->Maximum ) tp->Maximum = c; 
#ifdef	TP_NEW
	if( c < tp->Minimum ) tp->Minimum = c; 
#endif
	S32_Inc( &tp->Count );
	return( c );
}
