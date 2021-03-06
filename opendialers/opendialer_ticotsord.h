/* config */


#define	VERSION		"0"
#define	WHATINFO	"@(#)opendialerticotsord "
#define	BANNER		"Open-Dialer TICOTSORD"
#define	SEARCHNAME	"opendialerticotsord"
#define	VARPRNAME	"EXTRA"

#define	VARPROGRAMROOT1	"OPENDIALERTICOTSORD_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"OPENDIALERTICOTSORD_BANNER"
#define	VARSEARCHNAME	"OPENDIALERTICOTSORD_NAME"
#define	VARFILEROOT	"OPENDIALERTICOTSORD_FILEROOT"
#define	VARLOGTAB	"OPENDIALERTICOTSORD_LOGTAB"
#define	VARMSFNAME	"OPENDIALERTICOTSORD_MSFILE"
#define	VARUTFNAME	"OPENDIALERTICOTSORD_UTFILE"
#define	VARERRORFNAME	"OPENDIALERTICOTSORD_ERRORFILE"

#define	VARDEBUGFNAME	"OPENDIALERTICOTSORD_DEBUGFILE"
#define	VARDEBUGFD1	"OPENDIALERTICOTSORD_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARNODE		"NODE"
#define	VARSYSNAME	"SYSNAME"
#define	VARRELEASE	"RELEASE"
#define	VARMACHINE	"MACHINE"
#define	VARARCHITECTURE	"ARCHITECTURE"
#define	VARCLUSTER	"CLUSTER"
#define	VARSYSTEM	"SYSTEM"
#define	VARNISDOMAIN	"NISDOMAIN"
#define	VARPRINTER	"PRINTER"

#define	VARTMPDNAME	"TMPDIR"

#define	VARPRLOCAL	"LOCAL"
#define	VARPRPCS	"PCS"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/local"
#endif

#define	TMPDNAME	"/tmp"
#define	WORKDNAME	"/tmp"

#define	DEFINITFNAME	"/etc/default/init"
#define	DEFLOGFNAME	"/etc/default/login"
#define	NISDOMAINNAME	"/etc/defaultdomain"

#define	CONFIGFNAME	"conf"
#define	ENVFNAME	"environ"
#define	PATHSFNAME	"paths"
#define	HELPFNAME	"help"

#define	PIDFNAME	"run/opendialerticotsord"
#define	LOGFNAME	"var/log/opendialerticotsord"
#define	LOCKFNAME	"spool/locks/opendialerticotsord"
#define	MSFNAME		"ms"

#define	LOGSIZE		(80*1024)

#define	DEFRUNINT	60
#define	DEFPOLLINT	8
#define	DEFNODES	50

#define	TO_CACHE	2



