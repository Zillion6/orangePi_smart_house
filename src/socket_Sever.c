#include "socket_Sever.h"

int socket_init()
{
    int s_fd;
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(struct sockaddr_in));

    s_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(s_fd == -1)
    {
        perror("socket");
        close(s_fd);
        exit(-1);
    }

    // int opt = 1;
    // if (setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    // {
    //     perror("setsockopt SO_REUSEADDR");
    //     close(s_fd);
    //     exit(EXIT_FAILURE);
    // }

    // #ifdef SO_REUSEPORT
    // if (setsockopt(s_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    // {
    //     perror("setsockopt SO_REUSEPORT");
    //     close(s_fd);
    //     exit(EXIT_FAILURE);
    // }
    // #endif

    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(atoi(MY_PORT));
    inet_aton(MY_IP_ADDRESS, &s_addr.sin_addr);
    //2.bind
    int result_bind = bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in));
    if (-1 == result_bind)
    {
        printf("%s|%s|%d: bind error!\n", __FILE__, __FUNCTION__, __LINE__);
        perror("bind");
        close(s_fd);
        return -1;
    }
    //3.listen
    int result_listen = listen(s_fd, 8);
    if (-1 == result_listen)
    {
        perror("listen");
        close(s_fd);
        return -1;
    }

    return s_fd;
}