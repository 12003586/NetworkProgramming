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

              //love = calculateNameLove(variable1,variable2);

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

              if ((USERID.length() >=9 or USERID.length() <= 7)  and USERID.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos)
              {
                  USERID = "nicetry!";
                  textParsed = ">1/12/2002>>01/12/2002";
              }

              temp = textParsed.substr(9, textParsed.find(">>"));
              variable1 = temp.substr(0, temp.find(">>"));
              std::cout << "got the numbers " << variable1 << " from user " << USERID << "\n";

              if (checkDates(variable1) && checkDates(variable2))
              {
                  int love = 0;
                  std::cout << "dates are valid, continue\n";
                  //love = calculateDateLove(variable1 , variable2);
                  sendtpic = ( "BoMengels>Roulette!>USER:" + USERID + ":" + std::to_string(love));
                  pusher.send(sendtpic.c_str(), sendtpic.length());

              }
              else{

                  std::cout << "1 or 2 dates are invalid\n";
                  sendtpic = ( "BoMengels>Roulette!>USER:" + USERID + ":InvalidDates");
                  pusher.send(sendtpic.c_str(), sendtpic.length());
              }
            }
            /* more else if clauses */

            else /* default: */
            {
                sendtpic = ( "BoMengels>Roulette!>USER:" + USERID + ":ServiceNotInUse");
                pusher.send(sendtpic.c_str(), sendtpic.length());
            }


            std::cout << "Subscribed : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;

        }
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }

}




bool Server::checkDates(std::string date)
{


    int d;
    int m;
    int y;
    parseDates(date ,  &d ,  &m ,  &y);
    std::cout << "got the dates " << d<<  " and " << m << " and " << y  << "\n";

    const int MAX_VALID_YR = 2300;
    const int MIN_VALID_YR = 1800;



        if (y > MAX_VALID_YR ||
            y < MIN_VALID_YR)
        return false;
        if (m < 1 || m > 12)
        return false;
        if (d < 1 || d > 31)
        return false;

        // Handle February month
        // with leap year
        if (m == 2)
        {
            if (isLeap(y))
            return (d <= 29);
            else
            return (d <= 28);
        }

        // Months of April, June,
        // Sept and Nov must have
        // number of days less than
        // or equal to 30.
        if (m == 4 || m == 6 ||
            m == 9 || m == 11)
            return (d <= 30);

        return true;

}










