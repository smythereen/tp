/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per Second (TPS) Utility
 ******************************************************************************/
#include	<tp.h>
#include	<map.h>
#include	<string.h>

static	tps_t	*	tps;

static	void	add( int ac, char *av[ ] )
{
	if( ac != 1 ) return;
	printf(	"TP=%d\n", TPS_Add( tps, (s32)strtoul( av[ 0 ], 0, 10 ) ) );
	exit( 0 );
}

static	void	bump( int ac, char *av[ ] )
{
	printf(	"TP=%d\n", TPS_Bump( tps ) );
	exit( 0 );
}

static	void	check( int ac, char *av[ ] )
{
	printf(	"%u New Day\n", TPS_Check( tps ) );
	exit( 0 );
}

static	void	initialize( int ac, char *av[ ] )
{
	TPS_Initialize( tps );
	printf(	"TP=%u\n", tps->TP );
	exit( 0 );
}

static	void	interval( int ac, char *av[ ] )
{
	printf(	"Old Index=%u\n", tps->Index );
	TPS_Interval( tps );
	printf(	"New Index=%u\n", tps->Index );
	exit( 0 );
}

static	struct	list_s	{
	char *	cmd;
	void (*func)( int ac, char *av[ ] );
}	list[ ]	=	{
	{	"add",			add		},
	{	"bump",			bump		},
	{	"check",		check		},
	{	"initialize",		initialize	},
	{	"interval",		interval	},
	{	(char *)0,		(void (*)( int, char *[ ] ))0	}
};

static	void	usage( char * av[ ] )
{
	fprintf( stderr,
		 "\n\tTransactions Per Second (TPS) - Utility Program\n\n"
		 "Usage:\n"
		 "\t%s\ttps.mem a[dd]  #n\n"
		 "\t  \ttps.mem b[ump]\n"
		 "\t  \ttps.mem c[heck]\n"
		 "\t  \ttps.mem i[nitialize]\n"
		 "\t  \ttps.mem int[erval]\n"
		 "\n",
		 av[ 0 ]
	);
	fflush( stderr );
	exit( 2 );
}

main( int ac, char * av[ ] )
{
struct	list_s	*	l;
	int		len;

	LocalName = av[ 0 ];

	switch( ac ) {
	default:
		tps = MapFile2Mem( av[1], sizeof( tps_t ), PROT_WRITE );
		if( tps != NULL ) {
			len = strlen( av[ 2 ] );
			for( l = list; l->cmd != (char *)0; l++ ) {
				if( strncasecmp( av[ 2 ], l->cmd, len ) ) continue;
				l->func( ( ac - 3 ), &av[ 3 ] );
			}
		} else {
			fprintf( stderr, "\nCannot Map File \"%s\"\n", av[1] );
			fflush( stderr );
		}
	case  2:
	case  1:
	case  0:	usage( av );
	}
}
