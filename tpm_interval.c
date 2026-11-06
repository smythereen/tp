/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Process Function
 ******************************************************************************/
#include	"tplocal.h"

s32	TP_prefix(TPM_Interval) ( tpm_t * tp, char * file )
{
	return( _tp_Interval( (TP_t *)tp, (u32)TPM_MAX_INTERVALS, file ) );
}
