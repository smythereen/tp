/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Initialization Function
 ******************************************************************************/
#include	"tplocal.h"

void	TP_prefix(tp_Initialize) ( TP_t * tp, u32 max )
{
	u32	Count = tp->Count;
	memset( tp, 0, sizeof( TP_t ) + ( sizeof( s32 ) * max ) );
	tp->Stamp = _tp_Next_Stamp( max );
	tp->Count = Count;

#ifdef	TP_NEW
	tp->Max_Intervals = max;
	switch( max ) {
	case TPD_MAX_INTERVALS:	tp->Duration = TPD_DURATION;
				break;
	case TPH_MAX_INTERVALS:	tp->Duration = TPH_DURATION;
				break;
	case TPM_MAX_INTERVALS:	tp->Duration = TPM_DURATION;
				break;
	default:		tp->Duration = TPS_DURATION;
				break;
	}
#endif

}
