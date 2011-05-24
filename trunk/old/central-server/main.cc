#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include "games.hpp"

#include <pthread.h>
#include <signal.h>

game_server teste;

void h(client_ostream &oclient,client_istream &iclient, string &client_addr){
	teste(oclient,iclient,client_addr);
}


int main(int argc, char* argv[])
{
	char *port="50000";
	char *addr="0.0.0.0";
	std::size_t num_threads= 20;

	try
	{
		// Check command line arguments.
		if (argc < 3 && argc != 1 )
		{
			std::cerr << "Usage: "<<argv[0]<<" <address> <port> [<threads>]\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    "<<argv[0]<<" 0.0.0.0 80 [1..n]\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    "<<argv[0]<<" 0::0 80 [1..n]\n" << argc << "\n";
			return 1;
		}else if( argc == 4 ) {
			// Run server in background thread.
			num_threads = boost::lexical_cast<std::size_t>(argv[3]);
		}

		transmission s(addr, port, h, num_threads==0?1:num_threads );

		s.exec();

	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}

