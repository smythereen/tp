/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per Hour (TPH) Utility
 ******************************************************************************/
#include	<tp.h>
#include	<map.h>
#include	<string.h>

static	tph_t	*	tph;

static	void	add( int ac, char *av[ ] )
{
	if( ac != 1 ) return;
	printf(	"TP=%d\n", TPH_Add( tph, (s32)strtoul( av[ 0 ], 0, 10 ), av[ 1 ] ) );
	exit( 0 );
}

static	void	bump( int ac, char *av[ ] )
{
	printf(	"TP=%d\n", TPH_Bump( tph, av[ 0 ] ) );
	exit( 0 );
}

static	void	check( int ac, char *av[ ] )
{
	printf(	"%u New Day\n", TPH_Check( tph, av[ 0 ] ) );
	exit( 0 );
}

static	void	initialize( int ac, char *av[ ] )
{
	TPH_Initialize( tph );
	printf(	"TP=%u\n", tph->TP );
	exit( 0 );
}

static	void	interval( int ac, char *av[ ] )
{
	printf(	"Old Index=%u\n", tph->Index );
	TPH_Interval( tph, av[ 0 ] );
	printf(	"New Index=%u\n", tph->Index );
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
		 "\n\tTransactions Per Hour (TPH) - Utility Program\n\n"
		 "Usage:\n"
		 "\t%s\ttph.mem a[dd]  #n    [StatisticsFile.csv]\n"
		 "\t  \ttph.mem b[ump]       [StatisticsFile.csv]\n"
		 "\t  \ttph.mem c[heck]      [StatisticsFile.csv]\n"
		 "\t  \ttph.mem i[nitialize]\n"
		 "\t  \ttph.mem int[erval]   [StatisticsFile.csv]\n"
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
		tph = MapFile2Mem( av[1], sizeof( tph_t ), PROT_WRITE );
		if( tph != NULL ) {
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
