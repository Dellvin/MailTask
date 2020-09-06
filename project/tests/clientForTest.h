//
// Created by dellvin on 9/6/20.
//

#ifndef IZ2_CLIENTFORTEST_H
#define IZ2_CLIENTFORTEST_H

#include <utility>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

class clientForTest {
public:

    clientForTest(std::string &&serverIP, int serverPort);

    int start();

    void send(std::string message);

    std::string recv();
private:
    uint32_t port;
    std::string ip;
    int sock;
};

clientForTest::clientForTest(std::string &&serverIP, int serverPort) : ip(serverIP), port(serverPort) {}

int clientForTest::start() {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (!inet_aton(ip.c_str(), &(addr.sin_addr))) {
        std::cerr << "Invalid Ip address" << std::endl;
        return (1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Socket error" << std::endl;
        return (2);
    }
    if (connect(sock, (sockaddr *) &addr, sizeof(addr))) {
        std::cerr << "Connection error" << std::endl;
        return (3);
    }
    std::cout << "You successfully connected to server!" << std::endl;
    return 0;
}

void clientForTest::send(std::string message) {
    write(sock, message.c_str(), message.size());
}

std::string clientForTest::recv() {
    char buff[256];
    read(sock, buff, 256);
    return buff;
}


#endif //IZ2_CLIENTFORTEST_H
