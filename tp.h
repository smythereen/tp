/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	TP (Transactions Per) Header File
 *
 *	This file defines common structures, variables, and routines
 *	need for transaction processing
 ******************************************************************************/
#ifndef	TP_H
#define	TP_H

#if	defined( __cplusplus )
extern	"C"	{
#endif

#include	<common.h>

//#define	TP_NEW			1

#define	TPS_DURATION		1		/* Interval = 1 Second */
#define	TPS_MAX_INTERVALS	600		/* 600 Seconds = 10 Minutes */

#define	TPM_DURATION		60		/* Interval = 60 Seconds = 1 Minute */
#define	TPM_MAX_INTERVALS	60		/* 60 Minutes = 1 Hour */

#define	TPH_DURATION		3600		/* Interval = 3600 Seconds = 1 Hour */
#define	TPH_MAX_INTERVALS	168		/* 168 Hours = 1 Week */

#define	TPD_DURATION		86400		/* Interval = 86400 Seconds = 1 Day */
#define	TPD_MAX_INTERVALS	365		/* 365 Days = 1 Year */

#ifdef	TP_NEW

#define	TpProto( max )										\
	struct	{										\
		s32		Count;		/* Total Count Since Last Zeroed */		\
		s32		Maximum;	/* Maximum Count Seen In Interval Range */	\
		s32		Minimum;	/* Minimum Count Seen In Interval Range */	\
		u32		Zeroes;		/* Count of Zero Intervals */			\
		f32		Average;	/* Running Average Across Interval Range */	\
		u32		Duration;	/* Interval Duration In Seconds */		\
		u32		Max_Intervals;	/* Maximum Number Of Intervals */		\
		u32		Interval;	/* Current Number Of Intervals */		\
		u32		Stamp;		/* Index Into Interval Count Array */		\
		s32		TP;		/* Transaction Count Current Interval */	\
		s32		Total;		/* Total Count For Entire Interval Range */	\
		u32		Index;		/* Index Into Interval Count Array */		\
		s32		Per[ max ];	/* Per Interval Count Array */			\
	}

#else

#define	TpProto( max )										\
	struct	{										\
		s32		Count;		/* Total Count Since Last Zeroed */		\
		s32		Maximum;	/* Maximum Count Seen In Interval Range */	\
		f32		Average;	/* Running Average Across Interval Range */	\
		u32		Interval;	/* Current Number Of Intervals */		\
		u32		Stamp;		/* Index Into Interval Count Array */		\
		s32		TP;		/* Transaction Count Current Interval */	\
		s32		Total;		/* Total Count For Entire Interval Range */	\
		u32		Index;		/* Index Into Interval Count Array */		\
		s32		Per[ max ];	/* Per Interval Count Array */			\
	}

#endif

typedef	TpProto( 0 )			TP_t;

typedef	TpProto( TPS_MAX_INTERVALS )	tps_t;

typedef	TpProto( TPM_MAX_INTERVALS )	tpm_t;

typedef	TpProto( TPH_MAX_INTERVALS )	tph_t;

typedef	TpProto( TPD_MAX_INTERVALS )	tpd_t;

typedef	struct	tp_s	{
	tps_t		tps;			/* Messages Per Second			*/
	tpd_t		tpd;			/* Messages Per Day			*/
	char		tpd_file[ 64 ];		/* Transaction Per Day Data File	*/
}	tp_t;

typedef	tp_t	*	tp_p;

#ifndef TPLOCAL_H

/*
 *	Transaction Per - TIMESTAMP Routine
 */

extern	u32	tp_Next_Stamp( u32 max );

/*
 *	Transaction Per - INTERVAL Routines
 */

extern	s32	tp_Interval(	TP_t  * tp, u32 limit, char * file );
extern	s32	TP_Interval(	tp_t  * tp, char * file );
extern	s32	TPD_Interval(	tpd_t * tp, char * file );
extern	s32	TPH_Interval(	tph_t * tp, char * file );
extern	s32	TPM_Interval(	tpm_t * tp, char * file );
extern	s32	TPS_Interval(	tps_t * tp );

/*
 *	Transaction Per - INITIALIZATION Routines
 */

extern	void	tp_Initialize(	TP_t  * tp, u32 max );
extern	void	TP_Initialize(	tp_t  * tp );
extern	void	TPD_Initialize(	tpd_t * tp );
extern	void	TPH_Initialize(	tph_t * tp );
extern	void	TPM_Initialize(	tpm_t * tp );
extern	void	TPS_Initialize(	tps_t * tp );

/*
 *	Transaction Per - CHECK Routines
 */

extern	u32	tp_Check(	TP_t  * tp, char * file, u32 max_i, u32 max_d );
extern	int	TP_Check(	tp_t  * tp );
extern	u32	TPD_Check(	tpd_t * tp, char * file );
extern	u32	TPH_Check(	tph_t * tp, char * file );
extern	u32	TPM_Check(	tpm_t * tp, char * file );
extern	u32	TPS_Check(	tps_t * tp );

/*
 *	Transaction BUMP Routines
 */

extern	s32	tp_Bump(	TP_t  * tp );
extern	int	TP_Bump(	tp_t  * tp );
extern	s32	TPD_Bump(	tpd_t * tp, char * file );
extern	s32	TPH_Bump(	tph_t * tp, char * file );
extern	s32	TPM_Bump(	tpm_t * tp, char * file );
extern	s32	TPS_Bump(	tps_t * tp );

/*
 *	Transaction ADD Routines
 */

extern	s32	tp_Add(		TP_t  * tp, s32 i );
extern	int	TP_Add(		tp_t  * tp, s32 i );
extern	s32	TPD_Add(	tpd_t * tp, s32 i, char * file );
extern	s32	TPH_Add(	tph_t * tp, s32 i, char * file );
extern	s32	TPM_Add(	tpm_t * tp, s32 i, char * file );
extern	s32	TPS_Add(	tps_t * tp, s32 i );

/*
 *	Transaction FILE Routines
 */

extern	TP_t    *       tp_File( char * file, u32 max );

extern	void		TP_File_Bump( char * file );

#endif

#if	defined( __cplusplus )
}
#endif

#endif
