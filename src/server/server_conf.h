/**
* server_conf.h
*
* Init Created: 2016-07-04
* Last Updated: 2016-07-04
*/
#ifndef SERVER_CONF_H_INCLUDED
#define SERVER_CONF_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

#define SERVER_APP_NAME  "fastsync-server"

#define LOGGER_COLOR_OUTPUT
#define LOGGER_CATEGORY_NAME  SERVER_APP_NAME
#include "../logger.h"

#include "../msgs.h"
#include "../heads.h"
#include "../sockapi.h"

#include "../xmlconf.h"

#define FSYNC_MAGIC_LEN               4
#define FSYNC_PATHPREFIX_LEN        255
#define FSYNC_DEFAULT_BACKLOG        16
#define FSYNC_PKGNAME_LEN            60

#ifndef MAX_FILENAME_LEN
#define MAX_FILENAME_LEN 255
#endif

#define SUCCESS     0
#define ERROR     (-1)


/**
* server_conf_t is static instance in main process.
*   populated with config xml file: server.xml
*/
typedef struct server_conf_t
{
    char ver[10];

    /**
    * authentication
    */
    char magic[FSYNC_MAGIC_LEN + 1];
    int ssl_enabled;
    char pubkey[1];
    char privkey[1];

    /**
    * stash
    */
    char pathprefix[FSYNC_PATHPREFIX_LEN + 1];

    sqlite3 *regdb;

    int backend;
    union {
        /* backend: sqlite3 */
        struct {
            int maxretry;
            int interval;
        };
    };

    /**
    * tcp connection
    */
    int backlog;

    char *iptable_whitelist;
    char *iptable_blacklist;

    unsigned short port;
    int maxclients;
    int bufsize;

    /**
     * all in seconds
     */
    int timeout;
    int keepinterval;
    int keepidle;
    int keepcount;

    int nodelay;

    /**
    *  autoupdate
    */
    int autoupdate;
    char clientpkg_md5sum[MD5SUM_LEN + 1];
    char clientpkg[FSYNC_PKGNAME_LEN + 1];
} server_conf_t;


extern int server_conf_create(const char * cfgfile, server_conf_t **ppOut);

extern void server_conf_free (server_conf_t ** srvconf);

extern int server_conf_setsocketopt (int sockfd, const server_conf_t * srvconf);

extern void server_conf_print (server_conf_t * srvconf);

#if defined(__cplusplus)
}
#endif

#endif /* SERVER_CONF_H_INCLUDED */
