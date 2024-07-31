#include <libc.h>

void main(int ac, char **av) {

    // server init with sockets using ip4net domain
    int descriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockadrr_in addr = {
        AF_INET,
        0x1f90,
        0
    };
    bind(descriptor, &addr, sizeof(addr));
    //recieving data from socket client 
    int client_fd = accept(descriptor, 0, 0);
    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    // GET /file.html ..........
    // in this case we're just gonna keep the file name by skipping five char in GET request

    char *file = buffer + 5;
    *strchr(file, ' ') = 0;
    int open_fd = open(file, O_RDONLY);
    sendfile(client_fd, open_fd, 0, 256);
    close(open_fd);
    close(client_fd);
    close(descriptor);
}