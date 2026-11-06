/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per Map File Routine
 ******************************************************************************/
#include	"tplocal.h"

TP_t	TP_P_prefix(tp_File) ( char * file, u32 max )
{
	tp_t	*	tp;

	switch( max ) {
	case sizeof( tpd_t ):
	case TPD_MAX_INTERVALS: return( (TP_t *)MapFile2Mem( file, sizeof( tpd_t ), PROT_WRITE ) );
	case sizeof( tph_t ):
	case TPH_MAX_INTERVALS: return( (TP_t *)MapFile2Mem( file, sizeof( tph_t ), PROT_WRITE ) );
	case sizeof( tpm_t ):
	case TPM_MAX_INTERVALS: return( (TP_t *)MapFile2Mem( file, sizeof( tpm_t ), PROT_WRITE ) );
	case sizeof( tps_t ):
	case TPS_MAX_INTERVALS: return( (TP_t *)MapFile2Mem( file, sizeof( tps_t ), PROT_WRITE ) );

	case sizeof( tp_t ):
		tp = (tp_t *)MapFile2Mem( file, sizeof( tp_t ), PROT_WRITE );
		if( tp != NULL && tp->tpd_file[ 0 ] == 0 ) {
			char *	dp;
			strncpy( tp->tpd_file, file, sizeof( tp->tpd_file ) );
			dp = strrchr( tp->tpd_file, '.' );
			if( dp != NULL ) *dp = 0;
			strncat( tp->tpd_file, ".csv", sizeof( tp->tpd_file ) - strlen( tp->tpd_file ) );
		}
		return( (TP_t *)tp );
	}
	return( NULL );
}
