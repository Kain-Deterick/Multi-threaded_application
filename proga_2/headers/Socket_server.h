#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#define PORT 8080

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

class Socket_server
{
public:
void Read()
{
    listener = socket(AF_INET, SOCK_STREAM, 0);

    if(listener < 0)
    {
        perror("Error: socket");
        return;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Error: bind");
        return;
    }

    listen(listener, 3);
    
    std::cout << "Wait connection..." << std::endl;

    get_and_print_message();

    close(listener);
    close(sock);
}


private:
    void get_and_print_message()
    {
        while (true)
        {
            sock = accept(listener, (struct sockaddr *)&addr, &addrlen);
    
            int valread = recv(sock, buffer, 1024, 0);

            if(valread <= 0) break;
    
            deserialize_map(buffer, valread, received_map);
            
            sort_and_print_map();
        }
    }
    void deserialize_map(char *buffer, int size, std::map<char, int> &data) 
    {
        data.clear();
        for (int i = 0; i < size; i += 2) {
            char key = buffer[i];
           int value = buffer[i + 1];
           data[key] = value;
       }
    }

    void sort_and_print_map()
    {
        std::vector<std::pair<char, int>> vec(received_map.begin(), received_map.end());

        std::sort(vec.begin(), vec.end(), [](const auto &a, const auto &b) {
            return a.second > b.second;
        });

        std::cout << "Sorted map:\n";
        for (const auto &[key, value] : vec) 
        {
            std::cout << "'" << key << "' occurs " << value << " times\n";
        }
    }

private:
    int sock, listener;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char buffer[1024] = {0}; 
    std::map<char, int> received_map;

};

#endif SOCKET_SERVER_H