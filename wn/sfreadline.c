/* sfreadline */

/* Safe-Fast Read Line */


#define	CF_DEBUGS	0		/* compile-time debugging */
#define	CF_SFPOLL	0		/* use 'sfpoll(3ast)' */
#define	CF_SFGETR	1		/* use 'sfgetr(3ast)' */
#define	CF_PEEK		0		/* use 'sfpeek(3ast)' */


/* revision history:

	= 2004-03-01, David A�D� Morano
	This subroutine was originally written.  

*/

/* Copyright � 2004 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

	Name:

	sfreadlinetimed

	Description:

	This subroutine reads a line (while timed) using the SFIO package.

	Synopsis:

	int sfreadlinetimed(fp,rbuf,rlen,to)
	Sfio_t	*fp ;
	char	rbuf[] ;
	int	rlen ;
	int	to ;

	Arguments:

	fp		SFIO file-pointer
	rbuf		supplied buffer to receive result
	rlen		lrngth of supplied buffer
	to		time-out

	Returns:

	<0		error
	>=0		number of bytes read


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<ast.h>			/* configures other stuff also */

#include	<sys/types.h>
#include	<time.h>
#include	<string.h>

#include	<sfio.h>

#include	<localmisc.h>


/* local defines */


/* external subroutines */

extern int	snwcpy(char *,int,const char *,int) ;
extern int	msleep(int) ;

#if	CF_DEBUGS
extern int	debugprintf(const char *,...) ;
extern int	strlinelen(const char *,int,int) ;
#endif

extern char	*strnchr(const char *,int,int) ;


/* exported subroutines */


#if	CF_SFPOLL

#if	CF_PEEK

int sfreadlinetimed(Sfio_t *fp,char *rbuf,int rlen,int to)
{
	Sfio_t		*streams[2] ;
	time_t		daytime = time(NULL) ;
	time_t		stime ;
	int		rl = 0 ;
	const char	*tp ;

#if	CF_DEBUGS
	debugprintf("sfreadline: POLL,PEEK\n") ;
#endif

	if ((fp == NULL) || (rbuf == NULL))
	    return -1 ;

	rbuf[0] = '\0' ;
	if (rlen == 0) goto ret0 ;

	stime = daytime ;
	streams[0] = fp ;
	streams[1] = NULL ;

/* CONSTCOND */
	while (TRUE) {
	    int	r ;

	    r = sfpoll(streams,1,1000) ;

#if	CF_DEBUGS
	    debugprintf("sfreadline: sfpoll() r=%d\n",r) ;
#endif

	    if (r > 0) {
		int	v = sfvalue(fp) ;

#if	CF_DEBUGS
	    debugprintf("sfreadline: sfvalue() v=%04x\n",v) ;
#endif

		if (v & SF_READ) {
		    int		rbl = (rlen-rl) ;
		    int		pl ;
		    int		len ;
		    char	*rbp = (rbuf+rl) ;
	            pl = sfpeek(fp,rbp,rbl) ;

#if	CF_DEBUGS
	    debugprintf("sfreadline: sfpeek() rl=%d\n",pl) ;
		if (pl >= 0)
	    debugprintf("sfreadline: peek=>%t<\n",
		rbp,strlinelen(rbp,pl,60)) ;
#endif

		    if (pl > 0) {
		        if ((tp = strnchr(rbp,pl,'\n')) != NULL) {
#if	CF_DEBUGS
	    debugprintf("sfreadline: got frag=>%t<\n",
		rbp,strlinelen(rbp,(tp-rbp),60)) ;
#endif
			    len = sfread(fp,rbp,(tp+1-rbp)) ;
#if	CF_DEBUGS
	    debugprintf("sfreadline: 1 sfread() len=%d\n",len) ;
#endif
			    if (len >= 0) {
			        rl += len ;
			    } else {
			        rl = -1 ;
			    }
#if	CF_DEBUGS
		if (rl >= 0)
	    debugprintf("sfreadline: got line=>%t<\n",
		rbuf,strlinelen(rbuf,rl,60)) ;
#endif
			    break ;
		        } else {
			    len = sfread(fp,rbp,rbl) ;
#if	CF_DEBUGS
	    debugprintf("sfreadline: 2 sfread() len=%d\n",len) ;
#endif
			    if (len < 0) {
				rl = -1 ;
				break ;
			    } else if (len > 0) {
				rl += len ;
			    } else
				break ;
			}
		    } else if (pl == 0) {
			len = sfread(fp,rbp,rbl) ;
#if	CF_DEBUGS
	    debugprintf("sfreadline: 3 sfread() len=%d\n",len) ;
#endif
			if (len < 0) rl = -1 ;
			break ;
		    }

		} else {
		    msleep(10) ;
		}
	    } /* end if (positive) */

	    if (r < 0) {
		rl = -1 ;
		break ;
	    }

	    daytime = time(NULL) ;

	    if ((r == 0) && (to >= 0) && ((daytime - stime) >= to)) {
		if (rl == 0) rl = -1 ;
		break ;
	    }

	} /* end while */

ret0:

#if	CF_DEBUGS
	    debugprintf("sfreadline: ret rl=%d\n",rl) ;
#endif

	return rl ;
}
/* end subroutine (sfreadlinetimed) */

#else /* CF_PEEK */

int sfreadlinetimed(Sfio_t *fp,char *rbuf,int rlen,int to)
{
	Sfio_t		*streams[2] ;
	time_t		ti_start ;
	time_t		ti_now = time(NULL) ;
	int		rl = 0 ;

#if	CF_DEBUGS
	    debugprintf("sfreadline: POLL,GETR\n") ;
#endif

	if ((fp == NULL) || (rbuf == NULL))
	    return -1 ;

	rbuf[0] = '\0' ;
	if (rlen == 0) goto ret0 ;

	ti_start = ti_now ;
	streams[0] = fp ;
	streams[1] = NULL ;

/* CONSTCOND */
	while (TRUE) {
	    int	r ;

	    r = sfpoll(streams,1,1000) ;

#if	CF_DEBUGS
	    debugprintf("sfreadline: sfpoll() r=%d\n",r) ;
#endif

	    if (r > 0) {
		int	v = sfvalue(fp) ;

#if	CF_DEBUGS
	    debugprintf("sfreadline: sfvalue() v=%04x\n",v) ;
#endif

		if (v & SF_READ) {
		    int		rbl = (rlen-rl) ;
		    char	*rbp = (rbuf+rl) ;
		    cchar	*rp = sfgetr(fp,'\n',0) ;
#if	CF_DEBUGS
	    debugprintf("sfreadline: sfgetr() rp=%p\n",rp) ;
#endif
		    if (rp != NULL) {
			v = sfvalue(fp) ;
#if	CF_DEBUGS
	    debugprintf("sfreadline: sfvalue() v=%d\n",v) ;
#endif
			if (v >= 0) {
#if	CF_DEBUGS
	    debugprintf("sfreadline: data=%02x \n",rp[0]) ;
#endif
#ifdef	COMMENT
			    if ((v == 1) && (rp[0] == 4)) {
				rl = 0 ;
				break ;
			    }
#endif

			    rl = snwcpy(rbp,rbl,rp,v) ;
			    break ;
			} else {
			    rl = -1 ;
			}
		    } else {
		        rp = sfgetr(fp,'\n',SF_LASTR) ;
#if	CF_DEBUGS
	    debugprintf("sfreadline: 2 sfgetr() rp=%p\n",rp) ;
#endif
		        if (rp != NULL) {
			    v = sfvalue(fp) ;
#if	CF_DEBUGS
	    debugprintf("sfreadline: 2 sfvalue() v=%d\n",v) ;
#endif
			    if (v >= 0) {
			        rl = snwcpy(rbp,rbl,rp,v) ;
			    } else {
				rl = -1 ;
				break ;
			    }
			} else {
			    rl = 0 ;
			    break ;
			}
		    }
		} else {
		    msleep(10) ;
		}
	    } /* end if (poll says we have some data) */

	    if (r < 0) {
		rl = -1 ;
		break ;
	    }

	    if ((r == 0) && (to >= 0)) {
	        ti_now = time(NULL) ;
	        if ((ti_now - ti_start) >= to) {
		    if (rl == 0) rl = -1 ;
		}
	    }

	    if (rl < 0) break ;

	} /* end while */

ret0:

#if	CF_DEBUGS
	    debugprintf("sfreadline: ret rl=%d\n",rl) ;
#endif

	return rl ;
}
/* end subroutine (sfreadlinetimed) */

#endif /* CF_PEEK */

#else /* CF_SFPOLL */

int sfreadlinetimed(Sfio_t *fp,char *rbuf,int rlen,int to)
{
	int		rl = 0 ;

#if	CF_DEBUGS
	debugprintf("sfreadlinetimed: ent rlen=%d\n",rlen) ;
#endif

	if ((fp == NULL) || (rbuf == NULL))
	    return -1 ;

	rbuf[0] = '\0' ;
	if (rlen == 0) goto ret0 ;

#if	CF_SFGETR
	{
	    cchar	*rp = sfgetr(fp,'\n',0) ;
#if	CF_DEBUGS
	debugprintf("sfreadlinetimed: sfgetr() rp=%p\n",rp) ;
#endif
	    if (rp != NULL) {
	        rl = sfvalue(fp) ;
#if	CF_DEBUGS
		debugprintf("sfreadlinetimed: sfvalue() rl=%d\n",rl) ;
#endif
	    } else {
	        rp = sfgetr(fp,'\n',SF_LASTR) ;
#if	CF_DEBUGS
		debugprintf("sfreadlinetimed: sfgetr(LAST) rp=%p\n",rp) ;
#endif
	        if (rp != NULL) {
	            rl = sfvalue(fp) ;
#if	CF_DEBUGS
		    debugprintf("sfreadlinetimed: sfvalue() rl=%d\n",rl) ;
#endif
		} else {
		    rl = 0 ;
		}
	    } /* end if */
	    if ((rl > 0) && (snwcpy(rbuf,rlen,rp,rl) < 0)) {
		rl = -1 ;
	    }
	}
#else /* CF_SFGETR */
	{
	    int ch = 0 ;
	    while ((rl < rlen) && ((ch = sfgetc(fp)) >= 0)) {
	        rbuf[rl++] = ch ;
	        if (ch == '\n') break ;
	    }
	    if (ch < 0) rl = -1 ;
	}
#endif /* CF_SFGETR */

ret0:

#if	CF_DEBUGS
	debugprintf("sfreadlinetimed: ret rl=%d\n",rl) ;
#endif

	return rl ;
}
/* end subroutine (sfreadlinetimed) */

#endif /* CF_SFPOLL */


int sfreadline(Sfio_t *fp,char *rbuf,int rlen)
{

#if	CF_DEBUGS
	debugprintf("sfreadline: rlen=%d\n",rlen) ;
#endif

	return sfreadlinetimed(fp,rbuf,rlen,-1) ;
}
/* end subroutine (sfreadline) */


