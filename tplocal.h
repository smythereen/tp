/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	TP (Transactions Per) Local/Private Header File
 ******************************************************************************/
#ifndef	TPLOCAL_H
#define	TPLOCAL_H

#if	defined( __cplusplus )
extern	"C"	{
#endif

#include	<tp.h>
#include	<far.h>
#include	<map.h>
#include	<atomic_32.h>
#include	<mem_io.h>

extern		Mitem		tp_l[ ];
extern		Mitem		tpd_l[ ];
extern		Mitem		tph_l[ ];
extern		Mitem		tpm_l[ ];
extern		Mitem		tps_l[ ];

/*
 *	"C"	Preprocessor Fun!!!
 */

//#define		TP_PREFIX	extern	inline	__attribute__((gnu_inline))
//#define		TP_PREFIX	extern	inline	__attribute__((gnu_inline,always_inline,flatten))

#define		TP_prefix(n)	static inline __attribute__((gnu_inline,always_inline))   _##n

#define		TP_P_prefix(n)	static inline __attribute__((gnu_inline,always_inline)) * _##n

#undef		SCCS_C
#define		SCCS_C( v )

#include	"next_stamp.c"
#include	"initialize.c"
#include	"interval.c"
#include	"check.c"
#include	"add.c"
#include	"bump.c"
#include	"file.c"

#include	"tp_initialize.c"
#include	"tp_interval.c"
#include	"tp_check.c"
#include	"tp_add.c"
#include	"tp_bump.c"
#include	"tp_file.c"

#include	"tpd_initialize.c"
#include	"tpd_interval.c"
#include	"tpd_check.c"
#include	"tpd_add.c"
#include	"tpd_bump.c"

#include	"tph_initialize.c"
#include	"tph_interval.c"
#include	"tph_check.c"
#include	"tph_add.c"
#include	"tph_bump.c"

#include	"tpm_initialize.c"
#include	"tpm_interval.c"
#include	"tpm_check.c"
#include	"tpm_add.c"
#include	"tpm_bump.c"

#include	"tps_initialize.c"
#include	"tps_interval.c"
#include	"tps_check.c"
#include	"tps_add.c"
#include	"tps_bump.c"

//#undef		TP_PREFIX
//#define		TP_PREFIX	__attribute__((flatten))

#undef		TP_prefix
#define		TP_prefix(n)	__attribute__((flatten))   n

#undef		TP_P_prefix
#define		TP_P_prefix(n)	__attribute__((flatten)) * n

#undef		SCCS_C
#define		SCCS_C(v)	static const char __attribute__((section(".sccs"),unused)) _file_c_[ ] = __BASE_FILE__ ",," __DATE__ " " __TIME__ "," v

/*
 *	TP Memory Format Macro
 */

#ifdef	TP_NEW										\

#define	MITEM( x )									\
Mitem		x[ ] =	{								\
	S32(		Count,		"Total Count Since Last Zeroed"		),	\
	S32(		Maximum,	"Maximum Count Seen In Interval Range"	),	\
	S32(		Minimum,	"Minimum Count Seen In Interval Range"	),	\
	U32(		Zeroes,		"Count of Zero Value Intervals"		),	\
	F32(		Average,	"Running Average Across Interval Range"	),	\
	U32(		Interval,	"Current Number Of Intervals"		),	\
	U32(		Duration,	"Interval Duration In Seconds"		),	\
	U32(		Max_Intervals,	"Maximum Number Of Intervals"		),	\
	Stamp32(	Stamp,		"Time Of Last Interval Calculation"	),	\
	S32(		TP,		"Transactions Per"			),	\
	S32(		Total,		"Total TPD For The Current Day"		),	\
	U32(		Index,		"Index Into PerSec Array"		),	\
	U32_(4,		Per,		"Per Count Array"			),	\
	{ END_OF_LIST }									\
}

#else

#define	MITEM( x )									\
Mitem		x[ ] =	{								\
	S32(		Count,		"Total Count Since Last Zeroed"		),	\
	S32(		Maximum,	"Maximum Count Seen In Interval Range"	),	\
	F32(		Average,	"Running Average Across Interval Range"	),	\
	U32(		Interval,	"Current Number Of Intervals"		),	\
	Stamp32(	Stamp,		"Time Of Last Interval Calculation"	),	\
	S32(		TP,		"Transactions Per"			),	\
	S32(		Total,		"Total TPD For The Current Day"		),	\
	U32(		Index,		"Index Into PerSec Array"		),	\
	U32_(4,		Per,		"Per Count Array"			),	\
	{ END_OF_LIST }									\
}

#endif

#if	defined( __cplusplus )
}
#endif

#endif
