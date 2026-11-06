/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Memory Format
 ******************************************************************************/
#include	"tplocal.h"

/*
 *	tp_l
 */

#define	STRUCT	tp_t
	Mitem		tp_l[ ] =	{
	Struct(		tps_t,		tps,		tps_l			),
	Struct(		tpd_t,		tpd,		tpd_l			),
	String(		tpd_file,	"TPD Statistics CSV File"		),
	{ END_OF_LIST }
};
#undef	STRUCT
