#include "client.h"

client::client()
{

}

void client::startClient()
{
    try
    {

        std::string topic( "BoMengels>Roulette!>" );
        std::string sendtpic( "BoMengels>Roulette?>Start");


        //Incoming messages come in here


            zmq::context_t context(1);
            zmq::socket_t pusher( context, ZMQ_PUSH );
            zmq::socket_t subscriber( context, ZMQ_SUB );



        //pusher.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
        pusher.connect( "tcp://localhost:24041" );
        subscriber.connect( "tcp://localhost::24042" );

        //subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );

        subscriber.setsockopt( ZMQ_SUBSCRIBE, topic.c_str(), topic.length()  );

        zmq::message_t * msg = new zmq::message_t();



       // pusher.send( "example>quest?>Bo Mengels>", 38 );





        while( subscriber.connected() )
        {
            char service[101];
            printf("what service do you want? (Roulette) \n\r");
            sendtpic = "BoMengels>Roulette?>Start";
            pusher.send(sendtpic.c_str(), sendtpic.length());
            scanf("%100s", service);


            if (!strcmp(service, "Roulette"))
            {

                printf("want to bet on color or numbers?\n\r");
                scanf("%100s", keuze);
                if (!strcmp(keuze, "color"))
                {
                    printf("pick a color: black or red\n\r");
                    scanf("%100s \n\r", kleur);
                    sendtpic = "BoMengels>Roulette?>Color>";
                    std::string var = sendtpic + kleur;
                    std::cout << "Follow this command: " << var;
                    pusher.send(var.c_str(), var.length());

                }
                else if (!strcmp(keuze, "numbers"))
                {
                    bet();
                }
           }



        }
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }


}



void client::bet()
{
    printf("Give a number\n\r");
    scanf("%d \n\r", nummer);
    sendtpic = "BoMengels>Roulette?>Numbers>";

    printf("place your bet\n\r");
    scanf("%d \n\r", geld);
    sendtpic = "BoMengels>Roulette?>Geld>";
}

void client::roll()
{

}

int randomNumber()
{
    int randomGetal =  (rand() % 100);

    return randomGetal;
}
