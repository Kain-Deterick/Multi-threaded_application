#ifndef CONN_LINUX_SOCKET_H
#define CONN_LINUX_SOCKET_H

#define PORT 8080

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <iostream>
#include <sstream>
#include <string>

class  SocketClient
{
public:
    void sendMessage(const std::map<char, int>& shared_buffer)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock < 0)
        {
            perror("socket\n");
            return;
        }

        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

        if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
        {
            perror("Error: Connection to server!");
            close(sock);
            return;
        }

        serialize_map(shared_buffer, buffer, size);
        send(sock, buffer, size, 0);

        close(sock);
    }
private:
    void serialize_map(const std::map<char, int> &data, char *buffer, int &size) {
        size = 0;
        for (const auto &[key, value] : data) {
            buffer[size++] = key;
            buffer[size++] = value;
    }
}
private:
    int sock;
    char buffer[1024];
    int size;
};

#endif // CONN_LINUX_SOCKET_H