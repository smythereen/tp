/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2011-2026 John R. Smythe Jr. */
/*******************************************************************************
 *
 *	Transactions Per Minute (TPM) Utility
 ******************************************************************************/
#include	<tp.h>
#include	<map.h>
#include	<string.h>

static	tpm_t	*	tpm;

static	void	add( int ac, char *av[ ] )
{
	if( ac != 1 ) return;
	printf(	"TP=%d\n", TPM_Add( tpm, (s32)strtoul( av[ 0 ], 0, 10 ), av[ 1 ] ) );
	exit( 0 );
}

static	void	bump( int ac, char *av[ ] )
{
	printf(	"TP=%d\n", TPM_Bump( tpm, av[ 0 ] ) );
	exit( 0 );
}

static	void	check( int ac, char *av[ ] )
{
	printf(	"%u New Day\n", TPM_Check( tpm, av[ 0 ] ) );
	exit( 0 );
}

static	void	initialize( int ac, char *av[ ] )
{
	TPM_Initialize( tpm );
	printf(	"TP=%u\n", tpm->TP );
	exit( 0 );
}

static	void	interval( int ac, char *av[ ] )
{
	printf(	"Old Index=%u\n", tpm->Index );
	TPM_Interval( tpm, av[ 0 ] );
	printf(	"New Index=%u\n", tpm->Index );
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
		 "\n\tTransactions Per Minute (TPM) - Utility Program\n\n"
		 "Usage:\n"
		 "\t%s\ttpm.mem a[dd]  #n    [StatisticsFile.csv]\n"
		 "\t  \ttpm.mem b[ump]       [StatisticsFile.csv]\n"
		 "\t  \ttpm.mem c[heck]      [StatisticsFile.csv]\n"
		 "\t  \ttpm.mem i[nitialize]\n"
		 "\t  \ttpm.mem int[erval]   [StatisticsFile.csv]\n"
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
		tpm = MapFile2Mem( av[1], sizeof( tpm_t ), PROT_WRITE );
		if( tpm != NULL ) {
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
