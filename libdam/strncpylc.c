/* strncpylc */

/* copy a string to to *lower* case */


#define	CF_CHAR		1		/* use 'char(3dam)' */


/* revision history:

	= 1998-11-01, David A�D� Morano
	This subroutine was originally written.

*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

        This subroutine is like 'strncpy()' (with its non-NUL terminating
        behavior) except that the case of the characters are converted as
        desired.

	Synopsis:

	char *strncpylc(dst,src,n)
	char		*dst ;
	const char	*src ;
	int		n ;

	Arguments:

	dst		destination buffer
	src		source string
	n		length to copy

	Returns:

	last		pointer to one character past the end of destination


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<string.h>
#include	<char.h>
#include	<localmisc.h>


/* local defines */

#if	defined(CF_CHAR) && (CF_CHAR == 1)
#define	CF_CHAREXTERN	0
#define	tolc(c)		CHAR_TOLC(c)
#define	touc(c)		CHAR_TOUC(c)
#define	tofc(c)		CHAR_TOFC(c)
#else
#define	CF_CHAREXTERN	1
#endif


/* external subroutines */

extern char	*strcpylc(char *,const char *) ;
extern char	*strcpyuc(char *,const char *) ;
extern char	*strcpyfc(char *,const char *) ;

#if	CF_CHAREXTERN
extern int	tolc(int) ;
extern int	touc(int) ;
extern int	tofc(int) ;
#endif


/* local variables */


/* exported subroutines */


char *strncpylc(char *dst,cchar *src,int n)
{
	if (n >= 0) {
	    while (n && *src) {
	        *dst++ = tolc(*src) ;
	        src += 1 ;
		n -= 1 ;
	    } /* end while */
	    if (n > 0)
	        memset(dst,0,n) ;
	} else {
	    dst = strcpylc(dst,src) ;
	}
	return dst ;
}
/* end subroutine (strncpylc) */


