#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <string>
#include <zmq.hpp>


class client
{
public:
    client();
    void startClient();
    void bet();
    void roll();


    char service[101];
    char keuze[101];
    char naam1[101];
    char naam2[101];
    char kleur[101];
    int nummer;

     std::string sendtpic;

};

#endif // CLIENT_H
