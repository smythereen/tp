/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Interval Processing Function
 ******************************************************************************/
#include	"tplocal.h"

s32	TP_prefix(tp_Interval) ( TP_t * tp, u32 limit, char * file )
{
	time_t		stamp;
	s32		hold;
	s32		I;
	s32		i;
	s32		max;
#ifdef	TP_NEW
	s32		min;
	u32		zeroes;
#endif
	char	*	fmt;
	struct	tm	tbuf;
	char		buf[ 64 ];

	tp->Stamp = _tp_Next_Stamp( limit );

	switch( limit ) {
	case TPD_MAX_INTERVALS:
#ifdef	TP_NEW
		tp->Duration = TPD_DURATION;
#endif
		stamp = tp->Stamp - ( 2 * TPD_DURATION );
		fmt = "%F";
		break;

	case TPH_MAX_INTERVALS:
#ifdef	TP_NEW
		tp->Duration = TPH_DURATION;
#endif
		stamp = tp->Stamp - ( 2 * TPH_DURATION );
		fmt = "%F-%H";
		break;

	case TPM_MAX_INTERVALS:
#ifdef	TP_NEW
		tp->Duration = TPM_DURATION;
#endif
		stamp = tp->Stamp - ( 2 * TPM_DURATION );
		fmt = "%F-%H-%M";
		break;

	case TPS_MAX_INTERVALS:
#ifdef	TP_NEW
		tp->Duration = TPS_DURATION;
#endif
		stamp = tp->Stamp - 2;
		fmt = "%F-%H-%M-%S";
		break;

	default:
		return( 0 );
	}

#ifdef	TP_NEW
	tp->Max_Intervals = limit;
#endif

	/*
	 *	Bump the Interval Index
	 */
	if( ( I = S32_Inc_Return( &tp->Index ) ) >= limit ) tp->Index = 0;
	I -= 1;

	if( I > tp->Interval ) {
		/*
		 *	Bump the Intervals Until It Equals limit - 1;
		 */
		tp->Interval = I;
	} else if( tp->Interval > 0 ) {
		/*
		 *	Subtract Oldest Value From Running Total
		 */
		S32_Sub( tp->Per[ I ], &tp->Total );
	}
	i = tp->Interval;

	if( ( hold = tp->Per[ I ] = tp->TP ) > 0 ) {
		tp->TP = 0; 			// Reset Counter

		/*
		 *	Add Newest Value To Running Total
		 */
		S32_Add( hold, &tp->Total );
	}

	/*
	 *	ReCalculate the Running Average
	 */
	tp->Average = (f32)tp->Total / ( (f32)i + (f32)1 );

	/*
	 *	Find A New Maximum Value
	 *	Find A New Minimum Value
	 *	Count Zero Interval Values
	 */
#ifdef	TP_NEW
	min = 0x7fffffff;
	zeroes = 0;
#endif
	for( max = 0x80000001; i >= 0; i-- ) {
		if( ( I -= 1 ) < 0 ) I = limit - 1;
		if( max < tp->Per[ I ] ) max = tp->Per[ I ];
#ifdef	TP_NEW
		if( min > tp->Per[ I ] ) min = tp->Per[ I ];
		if( tp->Per[ I ] == 0 ) zeroes += 1;
#endif
	}
	tp->Maximum = max;
#ifdef	TP_NEW
	tp->Minimum = min;
	tp->Zeroes = zeroes;
#endif

	/*
	 *	Add Daily Data to file
	 */
	if( file == NULL || *file == 0 ) return( hold );

	strftime( buf, sizeof( buf ), fmt, localtime_r( &stamp, &tbuf ) );
#ifdef	TP_NEW
	Write_Line(
		file,
		"%s,%d,%d,%d,%d,%10.2f,%u,%u,%s\n",
		buf,
		hold,
		max,
		min,
		zeroes,
		tp->Average,
		tp->Count,
		tp->Interval,
		file
	);
#else
	Write_Line(
		file,
		"%s,%d,%d,%10.2f,%u,%u,%s\n",
		buf,
		hold,
		max,
		tp->Average,
		tp->Count,
		tp->Interval,
		file
	);
#endif
	return( hold );
}
