#ifndef SERVER_H
#define SERVER_H
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <zmq.hpp>

class Server
{
public:
    Server();
    void serverStart();
    void randomColor(std::string var);
    int  randomNumber();
    bool checkColor(std::string color);
    bool checkNumber(int number);






    std::string sendtpic;
    std::string USERID;
    std::string topic = ( "BoMengels>Roulette?>" );
    std::string kleur;
private:
    zmq::context_t context;
    zmq::socket_t pusher;
    zmq::socket_t subscriber;


};

#endif // SERVER_H
