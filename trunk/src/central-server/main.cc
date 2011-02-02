#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include "games.hpp"

#include <pthread.h>
#include <signal.h>

//void h(client_stream &client){
//	int x;
//	client >> x ;
//	client << "Ola " << x << " \n" ;
//}

game_server teste;

void h(client_ostream &oclient,client_istream &iclient, string &client_addr){
	teste(oclient,iclient,client_addr);
}


int main(int argc, char* argv[])
{
	try
	{
		// Check command line arguments.
		if (argc < 3 )
		{
			std::cerr << "Usage: "<<argv[0]<<" <address> <port> [<threads>]\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    "<<argv[0]<<" 0.0.0.0 80 [1..n]\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    "<<argv[0]<<" 0::0 80 [1..n]\n";
			return 1;
		}

		// Run server in background thread.
		std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);

		transmission s(argv[1], argv[2], h, num_threads==0?1:num_threads );

		s.exec();

	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}

