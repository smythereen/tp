/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2008-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per (TP) Utility
 ******************************************************************************/
#include	<string.h>
#include	<map.h>
#include	<tp.h>

static	tp_t	*	tp;

static	void	add( int ac, char *av[ ] )
{
	s32	i;

	if( ac != 1 ) return;
	i = (s32)strtol( av[ 0 ], 0, 10 );
	TP_Add( tp, i );
	printf(	"tp->tps.TP=%u\n", tp->tps.TP );
	printf(	"tp->tpd.TP=%u\n", tp->tpd.TP );
	exit( 0 );
}

static	void	bump( int ac, char *av[ ] )
{
	TP_Bump( tp );
	printf(	"tp->tps.TP=%u\n", tp->tps.TP );
	printf(	"tp->tpd.TP=%u\n", tp->tpd.TP );
	exit( 0 );
}

static	void	check( int ac, char *av[ ] )
{
	switch( TP_Check( tp ) ) {
	case 1:
		printf(	"New Second\n" );
		exit( 1 );
	case 2:
		printf(	"New Day\n" );
		exit( 1 );
	}
	printf(	"Old Second & Day\n" );
	exit( 0 );
}

static	void	initialize( int ac, char *av[ ] )
{
	TP_Initialize( tp );
	printf(	"tp->tps.TP=%u\n", tp->tps.TP );
	printf(	"tp->tpd.TP=%u\n", tp->tpd.TP );
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
	{	(char *)0,		(void (*)( int, char ** ))0	}
};

static	void	usage( char * av[ ] )
{
	fprintf( stderr,
		 "\n\tTransactions Per (TP) - Utility Program\n\n"
		 "Usage:\n"
		 "\t%s\ttp.mem a[dd]\n"
		 "\t  \ttp.mem b[ump]\n"
		 "\t  \ttp.mem c[heck]\n"
		 "\t  \ttp.mem i[nitialize]\n"
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

/*	TraceLevel = TP_TRC_LVL;	/* */

	switch( ac ) {
	default:
		tp = MapFile2Mem( av[1], sizeof( tp_t ), PROT_WRITE );
		if( tp != NULL ) {
			len = strlen( av[ 2 ] );
			for( l = list; l->cmd != (char *)0; l++ ) {
				if( strncasecmp( av[ 2 ], l->cmd, len ) ) continue;
				l->func( ( ac - 3 ), &av[ 3 ] );
				exit( 0 );
			}
		} else {
			fprintf( stderr, "\nCannot Map File \"%s\"\n", av[1] );
			fflush( stderr );
		}
		
	case  1:
	case  0:	usage( av );

	case  2:	TP_File_Bump( av[ 1 ] );
			exit( 0 );
	}
}
