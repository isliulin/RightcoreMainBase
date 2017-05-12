/* ipow */

/* return integer-power */
/* last modified %G% version %I% */


#define	CF_DEBUGS	0		/* non-switchable debug print-outs */


/* revision history:

	= 2004-03-01, David A�D� Morano
	This subroutine was originally written.  

*/

/* Copyright � 2004 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

        This subroutine calculates and returns an integer power for a given
        base.

	Synopsis:

	int ipow(b,p)
	int	b, p ;

	Arguments:

	b	base
	p	power

	Returns:

	-	result (b**p)


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<stdlib.h>
#include	<string.h>

#include	<vsystem.h>
#include	<localmisc.h>


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported subroutines */


int ipow(int b,int p)
{
	int		i ;
	int		r = 1 ;
	for (i = 0 ; i < p ; i += 1) {
	    r *= b ;
	}
	return r ;
}
/* end subroutine (ipow) */

