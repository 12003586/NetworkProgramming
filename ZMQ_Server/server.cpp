#include "server.h"


Server::Server()
:context(1),pusher(context, ZMQ_PUSH),subscriber(context,ZMQ_SUB)
{


}

void Server::serverStart()
{
    try
    {


        sendtpic = ( "BoMengels>Roulette!>USER::AAAAAAAAAAAAp");


        pusher.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
        //pusher.connect( "tcp://0.0.0.0:24041" );

        subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
        //subscriber.connect( "tcp://0.0.0.0:24042" );


        subscriber.setsockopt( ZMQ_SUBSCRIBE, topic.c_str(), topic.length()  );

        zmq::message_t * msg = new zmq::message_t();





        while( subscriber.connected() )
        {

            subscriber.recv( msg );

            if (strcmp((char*) msg->data(), "BoMengels>Roulette?>Start") == 0)
            {

              sendtpic =  "BoMengels>Roulette!>Bet on color or number on BoMengels>Roulette?>color or numbers";
              pusher.send(sendtpic.c_str(), sendtpic.length());

            }
            else if (strncmp((char*) msg->data(), "BoMengels>Roulette?>Color>", 44) == 0)
            {
              std::string text;
              std::string textParsed;
              std::string variable1;
              std::string temp;


              text =  std::string( (char*) msg->data(),msg->size() );
              textParsed = text.substr(text.find("?>Color") + 8);
              USERID = textParsed.substr(0, textParsed.find(">"));
              temp = textParsed.substr(9, textParsed.find(">>"));
              variable1 = temp.substr(0, temp.find(">>"));
              std::cout << "got the color " << variable1 << " from user " << USERID << "\n";



              sendtpic = ( "BoMengels>Roulette!>USER:" + USERID + ":" + std::to_string(love)  );
              pusher.send(sendtpic.c_str(), sendtpic.length());

            }
            else if (strncmp((char*) msg->data(), "BoMengels>Roulette?>Numbers>", 44) == 0)
            {
              std::string text;
              std::string textParsed;
              std::string variable1;
              std::string temp;


              text =  std::string( (char*) msg->data(),msg->size() );
              textParsed = text.substr(text.find("?>Numbers") + 8);
              USERID = textParsed.substr(0, textParsed.find(">"));

              temp = textParsed.substr(9, textParsed.find(">>"));
              variable1 = temp.substr(0, temp.find(">>"));
              std::cout << "got the numbers " << variable1 << " from user " << USERID << "\n";


            }
            std::cout << "Subscribed : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;

        }
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }

}














