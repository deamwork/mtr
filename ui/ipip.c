#include "config.h"
#include "mtr.h"
#include "../ipip/ipip.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

const char *ipip_get_location(struct mtr_ctl *ctl, ip_t *ip) {
    ipipdb_init("/usr/local/share/17monipdb.dat");
    static char buf[256];
    buf[0] = '\0';
    uint32_t res_ip;
#ifdef ENABLE_IPV6
#define ip6 ip->s6_addr
    if (ctl->af == AF_INET) {
        uint32_t be_ip = *(uint32_t *)ip6;
        res_ip = htonl(be_ip);
    } else {
        return buf;
    }
#else
    res_ip = ntohl(ip->s_addr);
#endif
    strcpy(buf, "[");
    ipipdb_find(res_ip, buf + 1);
    strcat(buf, "]");
    return buf;
}
