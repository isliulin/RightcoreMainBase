/* bfile_pagein */

/* "Basic I/O" package similiar to some other thing whose initials is "stdio" */
/* last modified %G% version %I% */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 1998-07-01, David A�D� Morano
	This subroutine was originally written.

	= 1999-01-10, David A�D� Morano
        Wow, I finally got around to adding memory mapping to this thing! Other
        subroutines of mine have been using memory mapped I/O for years but this
        is one of those routines where it should have been applied a long time
        ago because of its big performance benefits!

*/

/* Copyright � 1998,1999 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

	Internal (BFILE) page management.

*******************************************************************************/

#define	BFILE_MASTER	0

#include	<envstandards.h>

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/mman.h>
#include	<unistd.h>
#include	<fcntl.h>

#include	<vsystem.h>
#include	<localmisc.h>

#include	"bfile.h"


/* local defines */


/* external subroutines */


/* external variables */


/* forward references */


/* exported subroutines */


int bfile_pagein(bfile *fp,offset_t off,int i)
{
	size_t		msize ;
	const int	mprot = PROT_READ ;
	const int	mflags = MAP_SHARED ;
	int		rs ;
	caddr_t		cp ;

	off &= (fp->pagesize - 1) ;
	msize = fp->pagesize ;

	if ((rs = u_mmap(NULL,msize,mprot,mflags,fp->fd,off,&cp)) >= 0) {
	    fp->maps[i].buf = (char *) cp ;
	    fp->maps[i].f.valid = TRUE ;
	    fp->maps[i].offset = off ;
	}

	return rs ;
}
/* end subroutine (bfile_pagein) */


