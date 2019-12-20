#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
        char *if_name = "eth0";
        struct ifreq ifr;
        int tmp=0;
        size_t if_name_len=strlen(if_name);
        if (if_name_len<sizeof(ifr.ifr_name)) {
            memcpy(ifr.ifr_name,if_name,if_name_len);
            ifr.ifr_name[if_name_len]=0;
        } else {
            printf("interface name is too long");
        }
        int fd=socket(AF_UNIX,SOCK_DGRAM,0);
        if (fd==-1) {
            printf("%s",strerror(errno));
        }
        if ((tmp = ioctl(fd,SIOCGIFINDEX,&ifr))==-1) {
            printf("%s",strerror(errno));
        }
        printf("Id for %s interface is %d\n", if_name, ifr.ifr_ifindex);
        tmp = ioctl(fd, SIOCGIFMTU, &ifr);
        if(tmp == -1) {
            printf("%s",strerror(errno));
        }
        printf("MTU for %s interface is %d", if_name, ifr.ifr_mtu);

        return 0;
}
