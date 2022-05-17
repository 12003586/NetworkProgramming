#include <stdio.h>
#include "server.h"
#include <iostream>
#include <string.h>

#include <zmq.hpp>


int main( void )
{
    Server * s1 = new Server();
    s1->serverStart();

}
