/* u_getmsg */

/* UNIX� 'getmsg(2)' system call subroutine */
/* translation layer interface for UNIX� equivalents */


#define	CF_DEBUGS	0		/* compile-time */
#define	CF_UPOLL	0		/* call 'u_poll(2u)' */


/* revision history:

	= 1998-03-26, David A�D� Morano
        This subroutine was originally written to get around some stupid UNIX�
        sematics of their stupid system calls!


*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */


#include	<envstandards.h>

#include	<sys/types.h>
#include	<stropts.h>
#include	<unistd.h>
#include	<poll.h>
#include	<errno.h>

#include	<vsystem.h>
#include	<localmisc.h>


/* local defines */

#define	TO_NOSR		(10 * 60)
#define	TO_NOSPC	(10 * 60)
#define	TO_NOLCK	10
#define	TO_AGAIN	2


/* external subroutines */

extern int	msleep(int) ;


/* external variables */


/* local structures */

#if	defined(DARWIN)
typedef unsigned long		nfds_t ;
#endif


/* forward references */


/* local variables */


/* exported subroutines */


int u_getmsg(int fd,struct strbuf *cmp, struct strbuf *dmp,int *fp)
{
	struct pollfd	fds[2] ;
	int		rs ;
	int		rs1 ;
	int		nfds = 0 ;
	int		to_nosr = TO_NOSR ;
	int		to_nospc = TO_NOSPC ;
	int		to_nolck = TO_NOLCK ;
	int		to_again = TO_AGAIN ;
	int		f_exit = FALSE ;

#if	CF_DEBUGS
	debugprintf("u_getmsg: ent FD=%d\n",fd) ;
#endif

	repeat {
	    if ((rs = getmsg(fd,cmp,dmp,fp)) < 0) rs = (- errno) ;
	    if (rs < 0) {
	        switch (rs) {
#if	defined(SYSHAS_STREAMS) && (SYSHAS_STREAMS > 0)
	        case SR_NOSR:
	            if (to_nosr-- > 0) {
			msleep(1000) ;
		    } else {
			f_exit = TRUE ;
		    }
	            break ;
#endif /* defined(SYSHAS_STREAMS) && (SYSHAS_STREAMS > 0) */
	        case SR_NOSPC:
	            if (to_nospc-- > 0) {
			msleep(1000) ;
		    } else {
			f_exit = TRUE ;
		    }
	            break ;
	        case SR_NOLCK:
	            if (to_nolck-- > 0) {
			msleep(1000) ;
		    } else {
			f_exit = TRUE ;
		    }
	            break ;
	        case SR_AGAIN:
	            if (to_again-- > 0) {
			msleep(1000) ;
		    } else {
			f_exit = TRUE ;
		    }
	            break ;
	        case SR_INTR:
		    rs = SR_OK ;
	            if (nfds == 0) {
	                fds[nfds].fd = fd ;
	                fds[nfds].events = 0 ;
	                fds[nfds].revents = 0 ;
	                nfds += 1 ;
	            } /* end if */
#if	CF_UPOLL
	            rs1 = u_poll(fds,nfds,0) ;
#else
		    {
		        nfds_t n = nfds ;
	                if ((rs1 = poll(fds,n,0)) < 0) rs1 = (- errno) ;
		    }
#endif /* CF_UPOLL */
	            if (rs1 > 0) {
	                const int	re = fds[0].revents ;
	                if (re & POLLHUP) {
	                    rs = SR_HANGUP ;
	                } else if (re & POLLERR) {
	                    rs = SR_POLLERR ;
	                } else if (re & POLLNVAL) {
	                    rs = SR_NOTOPEN ;
		        }
			f_exit = (rs < 0) ;
	            } /* end if (we had some poll results) */
		    break ;
	        } /* end switch */
	    } /* end if (some kind of error) */
	} until ((rs >= 0) || f_exit) ;

#if	CF_DEBUGS
	debugprintf("u_getmsg: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (u_getmsg) */


