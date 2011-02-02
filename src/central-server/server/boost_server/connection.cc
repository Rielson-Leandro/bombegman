/* para escolher a implementacao */
#include "../../server.hpp"
#ifdef SERVER_USE_BOOST


#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <iostream>
#include <exception>

namespace boomberman {
	namespace server {
		namespace boost_impl {

/*		connection::connection(boost::asio::io_service& io_service,
			Handle_function handle )
			: strand_(io_service),
			socket_(io_service),
			timer_(io_service)
		{
			this->connection_handle=handle;
		}
*/
		boost::asio::ip::tcp::socket& connection::socket()
		{
			return socket_;
		}

		void connection::start()
		{
			socket_.async_read_some(boost::asio::buffer(buffer_),
					strand_.wrap(
						boost::bind(&connection::handle_read, shared_from_this())));
		}

		void connection::close( const boost::system::error_code& error )
//		void connection::close()
		{
			// Initiate graceful connection closure.
			if( ! error ){
				std::cout << "saiu close\n" ;
//				client << std::endl;
//				socket_.cancel();
				std::cout << "saiu close 1\n" ;
				std::cout << "saiu close 2\n" ;
//				client.exceptions( );
//				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				std::cout << "saiu close 3\n" ;

				client.rdbuf()->cancel();
//				socket_.cancel();
				std::cout << "saiu close 4\n" ;
				client.flush();
				client.close();
				client.flush();
//				socket_.cancel();
//				socket_.close();
				std::cout << "saiu close 5\n" ;
				boost::system::error_code ignored_ec;
				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
				client.rdbuf()->io_service().stop();
				client.rdbuf()->io_service().reset();
				client.rdbuf()->io_service().run_one();
//				socket_.close();
				std::cout << "saiu close fim\n" ;
//				client << std::endl;
//				client.exceptions( std::ios::badbit | std::ios::failbit | std::ios::eofbit );
			}else{
				std::cout << " Timeout canceled\n";
			}
		}

		void connection::handle_read()
		{
////			timer_.expires_from_now(boost::posix_time::seconds(5));
////			timer_.async_wait(boost::bind(&connection::close, shared_from_this(),_1)); //shared_from_this() ));
			client.exceptions( std::ios::badbit | std::ios::failbit | std::ios::eofbit );
			client.rdbuf()->pubsetbuf(0, 0);
			try{
				string client_addr=client.rdbuf()->remote_endpoint().address().to_string();
				connection_handle(client, client, client_addr);
			}catch( std::exception &e){
				std::cout << e.what() << std::endl ;
			}catch(...){
				std::clog << "Connection handle worst exception\n" ;
			}
			client.exceptions();
////			timer_.cancel();
		}

		void connection::handle_write(const boost::system::error_code& e)
		{
			if (!e)
			{
				// Initiate graceful connection closure.
				boost::system::error_code ignored_ec;
				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
			}

			// No new asynchronous operations are started. This means that all shared_ptr
			// references to the connection object will disappear and the object will be
			// destroyed automatically after this handler returns. The connection class's
			// destructor closes the socket.
		}

		} // namespace boost_impl
	} // namespace server
} // namespace boomberman

#endif // SERVER_USE_BOOST

